#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int word ;
struct TYPE_5__ {int Size; } ;
struct TYPE_4__ {scalar_t__ Head; scalar_t__ Wrap; scalar_t__ Base; scalar_t__ Tail; int /*<<< orphan*/  Count; } ;
typedef  TYPE_1__ MSG_QUEUE ;
typedef  TYPE_2__ MSG_HEAD ;

/* Variables and functions */
 int MSG_INCOMPLETE ; 
 scalar_t__ MSG_NEED (int) ; 

__attribute__((used)) static void queueFreeMsg (MSG_QUEUE *Q) {
/* Free the message at head of queue */

	word size = ((MSG_HEAD *)Q->Head)->Size & ~MSG_INCOMPLETE;

	Q->Head  += MSG_NEED(size);
	Q->Count -= size;

	if (Q->Wrap) {
		if (Q->Head >= Q->Wrap) {
			Q->Head = Q->Base;
			Q->Wrap = NULL;
		}
	} else if (Q->Head >= Q->Tail) {
		Q->Head = Q->Tail = Q->Base;
	}
}