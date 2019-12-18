#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ isOpen; scalar_t__ atEnd; TYPE_1__* firstPtr; TYPE_1__* curPtr; TYPE_1__* prevPtr; } ;
struct TYPE_8__ {struct TYPE_8__* nextPtr; } ;
typedef  TYPE_1__* LstNode ;
typedef  TYPE_2__* Lst ;
typedef  TYPE_1__* ListNode ;
typedef  TYPE_2__* List ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ LstValid (TYPE_2__*) ; 
 void* Middle ; 
 void* Tail ; 
 scalar_t__ Unknown ; 

LstNode
Lst_Next(Lst l)
{
    ListNode	tln;
    List 	list = l;

    if ((LstValid (l) == FALSE) ||
	(list->isOpen == FALSE)) {
	    return NULL;
    }

    list->prevPtr = list->curPtr;

    if (list->curPtr == NULL) {
	if (list->atEnd == Unknown) {
	    /*
	     * If we're just starting out, atEnd will be Unknown.
	     * Then we want to start this thing off in the right
	     * direction -- at the start with atEnd being Middle.
	     */
	    list->curPtr = tln = list->firstPtr;
	    list->atEnd = Middle;
	} else {
	    tln = NULL;
	    list->atEnd = Tail;
	}
    } else {
	tln = list->curPtr->nextPtr;
	list->curPtr = tln;

	if (tln == list->firstPtr || tln == NULL) {
	    /*
	     * If back at the front, then we've hit the end...
	     */
	    list->atEnd = Tail;
	} else {
	    /*
	     * Reset to Middle if gone past first.
	     */
	    list->atEnd = Middle;
	}
    }

    return (tln);
}