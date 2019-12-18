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
struct TYPE_5__ {int /*<<< orphan*/ * Tail; TYPE_1__* PacketQueue; int /*<<< orphan*/  NumPacketQueue; } ;
struct TYPE_4__ {struct TYPE_4__* Next; } ;
typedef  TYPE_1__ NEO_QUEUE ;

/* Variables and functions */
 TYPE_2__* ctx ; 

NEO_QUEUE *NeoGetNextQueue()
{
	NEO_QUEUE *q;
	if (ctx->PacketQueue == NULL)
	{
		// No item queued
		return NULL;
	}

	// Get the next queued item
	q = ctx->PacketQueue;
	ctx->PacketQueue = ctx->PacketQueue->Next;
	q->Next = NULL;
	ctx->NumPacketQueue--;

	if (ctx->PacketQueue == NULL)
	{
		ctx->Tail = NULL;
	}

	return q;
}