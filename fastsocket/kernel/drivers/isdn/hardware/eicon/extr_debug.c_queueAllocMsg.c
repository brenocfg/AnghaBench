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
typedef  scalar_t__ word ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_5__ {scalar_t__ Size; } ;
struct TYPE_4__ {scalar_t__ Tail; scalar_t__ Head; scalar_t__ Wrap; scalar_t__ Size; scalar_t__ High; scalar_t__ Base; scalar_t__ Count; } ;
typedef  TYPE_1__ MSG_QUEUE ;
typedef  TYPE_2__ MSG_HEAD ;

/* Variables and functions */
 scalar_t__ MSG_INCOMPLETE ; 
 scalar_t__ MSG_NEED (scalar_t__) ; 

__attribute__((used)) static byte *queueAllocMsg (MSG_QUEUE *Q, word size) {
	/* Allocate 'size' bytes at tail of queue which will be filled later
   * directly with callers own message header info and/or message.
   * An 'alloced' message is marked incomplete by oring the 'Size' field
   * with MSG_INCOMPLETE.
   * This must be reset via queueCompleteMsg() after the message is filled.
   * As long as a message is marked incomplete queuePeekMsg() will return
   * a 'queue empty' condition when it reaches such a message.  */

	MSG_HEAD *Msg;
	word need = MSG_NEED(size);

	if (Q->Tail == Q->Head) {
		if (Q->Wrap || need > Q->Size) {
			return NULL; /* full */
		}
		goto alloc; /* empty */
	}
	
	if (Q->Tail > Q->Head) {
		if (Q->Tail + need <= Q->High) goto alloc; /* append */
		if (Q->Base + need > Q->Head) {
			return NULL; /* too much */
		}
		/* wraparound the queue (but not the message) */
		Q->Wrap = Q->Tail;
		Q->Tail = Q->Base;
		goto alloc;
	}

	if (Q->Tail + need > Q->Head) {
		return NULL; /* too much */
	}

alloc:
	Msg = (MSG_HEAD *)Q->Tail;

	Msg->Size = size | MSG_INCOMPLETE;

	Q->Tail	 += need;
	Q->Count += size;



	return ((byte*)(Msg + 1));
}