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
struct TYPE_5__ {int /*<<< orphan*/  PacketQueueLock; scalar_t__ NumPacketQueue; int /*<<< orphan*/ * Tail; TYPE_1__* PacketQueue; } ;
struct TYPE_4__ {struct TYPE_4__* Buf; struct TYPE_4__* Next; } ;
typedef  TYPE_1__ NEO_QUEUE ;

/* Variables and functions */
 int /*<<< orphan*/  NeoFree (TYPE_1__*) ; 
 int /*<<< orphan*/  NeoLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NeoUnlock (int /*<<< orphan*/ ) ; 
 TYPE_2__* ctx ; 

void NeoClearPacketQueue(bool no_lock)
{
	// Release the memory of the packet queue
	if (no_lock == false)
	{
		NeoLock(ctx->PacketQueueLock);
	}
	if (true)
	{
		NEO_QUEUE *q = ctx->PacketQueue;
		NEO_QUEUE *qn;
		while (q != NULL)
		{
			qn = q->Next;
			NeoFree(q->Buf);
			NeoFree(q);
			q = qn;
		}
		ctx->PacketQueue = NULL;
		ctx->Tail = NULL;
		ctx->NumPacketQueue = 0;
	}
	if (no_lock == false)
	{
		NeoUnlock(ctx->PacketQueueLock);
	}
}