
/**
 * @file LinkedListExercises.h
 * University of Illinois CS 400, MOOC 2, Week 1: Linked List
 * Spring 2019
 *                        STUDENT STARTER FILE
 *
 * @author Eric Huber - University of Illinois staff
 *
**/

/********************************************************************
  Week 1: Linked List and Merge Sort Exercises

  There are two exercises in this file. Please read the code comments
  below and see the provided instructions PDF before you begin. The
  other provided code files in the starter zip also contain important
  comments and hints about how to approach this.

  This is the only file you can edit for the sake of grading! You can
  edit the other provided starter files for testing purposes, but the
  autograder will assume that this is the only file that has been edited
  by you, and the others will be replaced with the original intended
  versions at grading time.
 ********************************************************************/

// Prevent the header from being included more than once per cpp file
#pragma once

// It's good to put system headers first, so that if your own libraries
// cause conflicts, the compiler will most likely identify the problem
// as being in your own source code files, where it arises later.
#include <iostream>
#include <string>

#include "LinkedList.h"

/********************************************************************
  Exercise 1: insertOrdered

  This LinkedList member function assumes that the current contents
  of the list are already sorted in increasing order. The function
  takes as input a new data item to be inserted to the same list.
  The new data item should be inserted to the list in the correct
  position, so that you preserve the overall sorted state of the list.

  For example, if your LinkedList<int> contains:
  [1, 2, 8, 9]
  And the input is 7, then the list should be updated to contain:
  [1, 2, 7, 8, 9]

  To be more precise, a new node should be created on the heap, and
  it should be inserted in front of the earliest node in the list that
  contains a greater data element. If no such other node exists, then
  the new item should be placed at the end (the back of the list).

  Also, be sure to update the size_ member of the list appropriately.

  Your implementation of this function should not change the memory
  locations of the existing nodes. That is, you should not push or pop
  the existing elements of the list if it would change their address.
  (The member functions for push and pop will add a new node or delete
  one, so these operations would not leave the original node in place
  even if you recreated the node with equivalent data.) You should use
  pointers to connect your new node at the correct insertion location,
  being sure to adjust the list's head and tail pointers if necessary,
  as well as any prev or next pointers of adjacent nodes in the list.
  Remember: LinkedList is a doubly-linked list. That means each node
  also refers to the previous item in the list, not just the next item.

  A correct implementation of this function has O(n) time complexity
  for a list of length n. That is, in the worst case, you would
  traverse each element of the list some constant number of times.

  You can use "make test" followed by "./test" to check the correctness
  of your implementation, and then you can use "./test [bench]" to run
  some interesting benchmarks on the speed of your code.

 ********************************************************************/

template <typename T>
void LinkedList<T>::insertOrdered(const T& newData) {

 Node *newDataNode = new Node(newData);

  // If empty, set newData to head and tail
  if ( !size_ ) {
    head_ = newDataNode;
    tail_ = newDataNode;
  }
  // If new data is smaller than head, make head
  else if (newData < head_ -> data) {
    Node *oldHead = head_;
    oldHead -> prev = newDataNode;
    newDataNode -> next = oldHead;
    head_ = newDataNode;
  }
  
  // If new data is greater than tail, make tail
  else if (newData > tail_ -> data) {
    Node *oldTail = tail_;
    oldTail -> next = newDataNode;
    newDataNode -> prev = oldTail;
    tail_ = newDataNode;
  }

  // else fit inbetween two notes
  else {
    
    Node *curretNode = head_ -> next;

    // while current node is less than new data, go to next note
    while (curretNode && newData > curretNode -> data) {
      curretNode = curretNode -> next;
    }

  // set newDataNode next and prev to equal oldNode and oldNode prev
    newDataNode -> next = curretNode;
    newDataNode -> prev = curretNode -> prev;

  // update oldNotes prev attributes
    curretNode -> prev -> next = newDataNode;
    curretNode -> prev = newDataNode;

  // set currentNode to equal newData
    curretNode = newDataNode;
  }

  // update size
  size_ += 1;

}



/********************************************************************
  Exercise 2: Linear-time Merge

  This LinkedList member function is intended to perform the classic
  "merge" operation from the mergesort algorithm. It combines two sorted
  lists into a single sorted list. This algorithm is intended to run
  in linear time (that is, O(n) where n is the total number of elements
  in the input lists), so it is not appropriate to simply concatenate
  the two lists and then apply a sorting algorithm. Instead, the merge
  algorithm relies on the fact that the two input lists are already sorted
  separately in order to create the merged, sorted list in linear time.

  One of the implied input lists is the "*this" LinkedList instance that
  is calling the function, and the other input list is explicitly specified
  as the function argument "other". The function does NOT change either
  of the original lists directly, as the inputs are marked const.
  Instead, this function makes a new list containing the merged result,
  and it returns a copy of the new list. For example, one usage might
  look like this (OUTSIDE of this function, where we are making the call):

  LinkedList<int> leftList;
  // [... Add some sorted contents to leftList here. ...]
  LinkedList<int> rightList;
  // [... Add some sorted contents to rightList here. ...]
  LinkedList<int> mergedList = leftList.merge(rightList);

  You may assume that the two input lists have already been sorted.
  However, the lists may be empty, and they may contain repeated or
  overlapping elements. The lists may also have different lengths.
  For example, it's possible that these are the two input lists:

  Left list: [1, 2, 2, 3, 5, 5, 5, 6]
  Right list: [1, 3, 5, 7]

  And the result of merging those two sorted lists will contain all
  of the same elements, including the correct number of any duplicates,
  in sorted order:
  [1, 1, 2, 2, 3, 3, 5, 5, 5, 5, 6, 7]

  Because your implementation of this function operates on const inputs
  and returns a newly created list, you do not need to maintain the
  previous memory locations of any nodes as required in Exercise 1.
  You may need to make non-const "working copies" of the const input lists
  if you wish. You may approach this problem either iteratively or
  recursively, and you may use the member functions of the LinkedList class
  to make it simpler (such as push and pop), or you may edit the contents
  of lists explicitly by changing the pointers of a list or of its nodes
  (such as head_, tail_, next, and prev).

  Be sure that the size_ member of the resulting list is correct.

  A correct implementation of this function has O(n) time complexity
  for a list of length n. That is, in the worst case, you would
  traverse each element of the list some constant number of times.
  
  Important notes for getting the correct running time:

  1. Since both lists being merged are already sorted themselves, there
     is a way to merge them together into a single sorted list in a single
     traversal pass down the lists. This can run in O(n) time.
  2. You SHOULD NOT call any sorting function in your merge function.
  3. You SHOULD NOT call the insertOrdered function in merge. That would
     result in a very slow running time. (The insertOrdered function was
     part of the insertion sort exercise. It has nothing to do with merge
     or merge sort.)

  You can use "make test" followed by "./test" to check the correctness
  of your implementation, and then you can use "./test [bench]" to run
  some interesting benchmarks on the speed of your code.

 ********************************************************************/

template <typename T>
LinkedList<T> LinkedList<T>::merge(const LinkedList<T>& other) const {

  // You can't edit the original instance of LinkedList that is calling
  // merge because the function is marked const, and the "other" input
  // list is also marked const. However, here we'll make some convenient
  // "working copies" of the two lists: "*this" refers to the current
  // list object instance that is calling the merge member function, and
  // "other" refers to the list that was passed as an argument:
  LinkedList<T> left = *this;
  LinkedList<T> right = other;

  // So if this function was called as "A.merge(B)", then now, "left"
  // is a temporary copy of the "A" and "right" is a temporary copy
  // of the "B".
  
  // We will also create an empty list called "merged" where we can build
  // the final result we want. This is what we will return at the end of
  // the function.
  LinkedList<T> merged;

  while (!left.empty() && !right.empty())
  {
    if (left.front() < right.front())
    {
      merged.pushBack(left.front());
      left.popFront();
    }
    else
    {
      merged.pushBack(right.front());
      right.popFront();
    }
  }

  if (left.empty()) {
    while( !right.empty() )
    {
      merged.pushBack( right.front() );
      right.popFront();
    }
  }

  if (right.empty()) {
    while( !left.empty() )
    {
      merged.pushBack( left.front() );
      left.popFront();
    }
  }

  
  return merged;
}

