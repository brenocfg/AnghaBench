#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* firstPtr; } ;
struct TYPE_7__ {void* datum; struct TYPE_7__* nextPtr; } ;
typedef  TYPE_1__* LstNode ;
typedef  TYPE_2__* Lst ;
typedef  TYPE_1__* ListNode ;
typedef  TYPE_2__* List ;

/* Variables and functions */

LstNode
Lst_Member(Lst l, void *d)
{
    List    	  	list = l;
    ListNode	lNode;

    if (list == NULL) {
	return NULL;
    }
    lNode = list->firstPtr;
    if (lNode == NULL) {
	return NULL;
    }

    do {
	if (lNode->datum == d) {
	    return lNode;
	}
	lNode = lNode->nextPtr;
    } while (lNode != NULL && lNode != list->firstPtr);

    return NULL;
}