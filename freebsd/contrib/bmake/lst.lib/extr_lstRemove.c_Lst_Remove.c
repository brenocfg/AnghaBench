#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_1__* firstPtr; int /*<<< orphan*/  atEnd; TYPE_1__* curPtr; TYPE_1__* prevPtr; scalar_t__ isOpen; TYPE_1__* lastPtr; } ;
struct TYPE_11__ {scalar_t__ useCount; int /*<<< orphan*/  flags; struct TYPE_11__* prevPtr; struct TYPE_11__* nextPtr; } ;
typedef  int /*<<< orphan*/  ReturnStatus ;
typedef  TYPE_1__* LstNode ;
typedef  TYPE_2__* Lst ;
typedef  TYPE_1__* ListNode ;
typedef  TYPE_2__* List ;

/* Variables and functions */
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  LN_DELETED ; 
 int /*<<< orphan*/  LstNodeValid (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  LstValid (TYPE_2__*) ; 
 int /*<<< orphan*/  SUCCESS ; 
 int /*<<< orphan*/  Unknown ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

ReturnStatus
Lst_Remove(Lst l, LstNode ln)
{
    List 	list = l;
    ListNode	lNode = ln;

    if (!LstValid (l) ||
	!LstNodeValid (ln, l)) {
	    return (FAILURE);
    }

    /*
     * unlink it from the list
     */
    if (lNode->nextPtr != NULL) {
	lNode->nextPtr->prevPtr = lNode->prevPtr;
    }
    if (lNode->prevPtr != NULL) {
	lNode->prevPtr->nextPtr = lNode->nextPtr;
    }

    /*
     * if either the firstPtr or lastPtr of the list point to this node,
     * adjust them accordingly
     */
    if (list->firstPtr == lNode) {
	list->firstPtr = lNode->nextPtr;
    }
    if (list->lastPtr == lNode) {
	list->lastPtr = lNode->prevPtr;
    }

    /*
     * Sequential access stuff. If the node we're removing is the current
     * node in the list, reset the current node to the previous one. If the
     * previous one was non-existent (prevPtr == NULL), we set the
     * end to be Unknown, since it is.
     */
    if (list->isOpen && (list->curPtr == lNode)) {
	list->curPtr = list->prevPtr;
	if (list->curPtr == NULL) {
	    list->atEnd = Unknown;
	}
    }

    /*
     * the only way firstPtr can still point to ln is if ln is the last
     * node on the list (the list is circular, so lNode->nextptr == lNode in
     * this case). The list is, therefore, empty and is marked as such
     */
    if (list->firstPtr == lNode) {
	list->firstPtr = NULL;
    }

    /*
     * note that the datum is unmolested. The caller must free it as
     * necessary and as expected.
     */
    if (lNode->useCount == 0) {
	free(ln);
    } else {
	lNode->flags |= LN_DELETED;
    }

    return (SUCCESS);
}