#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_6__* SendQueue; int /*<<< orphan*/  Now; } ;
typedef  TYPE_1__ VH ;
typedef  scalar_t__ UINT ;
struct TYPE_14__ {scalar_t__ num_item; } ;
struct TYPE_13__ {scalar_t__ Size; void* Buf; } ;
typedef  TYPE_2__ BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_2__*) ; 
 TYPE_2__* GetNext (TYPE_6__*) ; 
 int /*<<< orphan*/  LockQueue (TYPE_6__*) ; 
 int /*<<< orphan*/  LockVirtual (TYPE_1__*) ; 
 int /*<<< orphan*/  Tick64 () ; 
 int /*<<< orphan*/  UnlockQueue (TYPE_6__*) ; 
 int /*<<< orphan*/  UnlockVirtual (TYPE_1__*) ; 
 int /*<<< orphan*/  VirtualPolling (TYPE_1__*) ; 

UINT VirtualGetNextPacket(VH *v, void **data)
{
	UINT ret = 0;

START:
	// Examine the transmission queue
	LockQueue(v->SendQueue);
	{
		BLOCK *block = GetNext(v->SendQueue);

		if (block != NULL)
		{
			// There is a packet
			ret = block->Size;
			*data = block->Buf;
			// Discard the structure
			Free(block);
		}
	}
	UnlockQueue(v->SendQueue);

	if (ret == 0)
	{
		LockVirtual(v);
		{
			v->Now = Tick64();
			// Polling process
			VirtualPolling(v);
		}
		UnlockVirtual(v);
		if (v->SendQueue->num_item != 0)
		{
			goto START;
		}
	}

	return ret;
}