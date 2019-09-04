#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_12__ {scalar_t__ num_item; } ;
struct TYPE_11__ {TYPE_3__* SendQueue; } ;
struct TYPE_10__ {scalar_t__ PacketSize; void* PacketData; } ;
typedef  TYPE_1__ PKT ;
typedef  TYPE_2__ L3IF ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 TYPE_1__* GetNext (TYPE_3__*) ; 
 int /*<<< orphan*/  L3Polling (TYPE_2__*) ; 
 int /*<<< orphan*/  LockQueue (TYPE_3__*) ; 
 int /*<<< orphan*/  UnlockQueue (TYPE_3__*) ; 

UINT L3GetNextPacket(L3IF *f, void **data)
{
	UINT ret = 0;
	// Validate arguments
	if (f == NULL || data == NULL)
	{
		return 0;
	}

START:
	// Examine the send queue
	LockQueue(f->SendQueue);
	{
		PKT *p = GetNext(f->SendQueue);

		if (p != NULL)
		{
			// There is a packet
			ret = p->PacketSize;
			*data = p->PacketData;
			// Packet structure may be discarded
			Free(p);
		}
	}
	UnlockQueue(f->SendQueue);

	if (ret == 0)
	{
		// Polling process
		L3Polling(f);

        // Examine whether a new packet is queued for results of the polling process
		if (f->SendQueue->num_item != 0)
		{
			// Get the packet immediately if it's in the queue
			goto START;
		}
	}

	return ret;
}