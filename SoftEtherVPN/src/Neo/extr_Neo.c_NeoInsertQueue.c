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
typedef  scalar_t__ UINT ;
struct TYPE_5__ {scalar_t__ NumPacketQueue; TYPE_1__* Tail; TYPE_1__* PacketQueue; } ;
struct TYPE_4__ {struct TYPE_4__* Next; void* Buf; scalar_t__ Size; } ;
typedef  TYPE_1__ NEO_QUEUE ;

/* Variables and functions */
 scalar_t__ NEO_MAX_PACKET_QUEUED ; 
 int /*<<< orphan*/  NeoFree (void*) ; 
 TYPE_1__* NeoMalloc (int) ; 
 TYPE_2__* ctx ; 

void NeoInsertQueue(void *buf, UINT size)
{
	NEO_QUEUE *p;
	// Validate arguments
	if (buf == NULL || size == 0)
	{
		return;
	}

	// Prevent the packet accumulation in large quantities in the queue
	if (ctx->NumPacketQueue > NEO_MAX_PACKET_QUEUED)
	{
		NeoFree(buf);
		return;
	}

	// Create a queue
	p = NeoMalloc(sizeof(NEO_QUEUE));
	p->Next = NULL;
	p->Size = size;
	p->Buf = buf;

	// Append to the queue
	if (ctx->PacketQueue == NULL)
	{
		ctx->PacketQueue = p;
	}
	else
	{
		NEO_QUEUE *q = ctx->Tail;
		q->Next = p;
	}

	ctx->Tail = p;

	ctx->NumPacketQueue++;
}