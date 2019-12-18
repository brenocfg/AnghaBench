#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* firstPtr; } ;
struct TYPE_9__ {void* datum; int flags; struct TYPE_9__* nextPtr; int /*<<< orphan*/  useCount; } ;
typedef  TYPE_1__* LstNode ;
typedef  TYPE_2__* Lst ;
typedef  TYPE_1__* ListNode ;
typedef  TYPE_2__* List ;
typedef  int Boolean ;

/* Variables and functions */
 int LN_DELETED ; 
 scalar_t__ LstIsEmpty (TYPE_2__*) ; 
 int /*<<< orphan*/  LstValid (TYPE_2__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int stub1 (void*,void*) ; 

int
Lst_ForEachFrom(Lst l, LstNode ln, int (*proc)(void *, void *),
		void *d)
{
    ListNode	tln = ln;
    List 	list = l;
    ListNode	next;
    Boolean 	    	done;
    int     	    	result;

    if (!LstValid (list) || LstIsEmpty (list)) {
	return 0;
    }

    do {
	/*
	 * Take care of having the current element deleted out from under
	 * us.
	 */

	next = tln->nextPtr;

	/*
	 * We're done with the traversal if
	 *  - the next node to examine is the first in the queue or
	 *    doesn't exist and
	 *  - nothing's been added after the current node (check this
	 *    after proc() has been called).
	 */
	done = (next == NULL || next == list->firstPtr);

	(void) tln->useCount++;
	result = (*proc) (tln->datum, d);
	(void) tln->useCount--;

	/*
	 * Now check whether a node has been added.
	 * Note: this doesn't work if this node was deleted before
	 *       the new node was added.
	 */
	if (next != tln->nextPtr) {
		next = tln->nextPtr;
		done = 0;
	}

	if (tln->flags & LN_DELETED) {
	    free((char *)tln);
	}
	tln = next;
    } while (!result && !LstIsEmpty(list) && !done);

    return result;
}