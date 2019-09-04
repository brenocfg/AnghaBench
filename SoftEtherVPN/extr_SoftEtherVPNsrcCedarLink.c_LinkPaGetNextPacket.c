#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_11__ {scalar_t__ Size; void* Buf; } ;
struct TYPE_10__ {int /*<<< orphan*/  SendPacketQueue; int /*<<< orphan*/  CurrentSendPacketQueueSize; scalar_t__* StopAllLinkFlag; scalar_t__ Halting; } ;
struct TYPE_9__ {TYPE_1__* PacketAdapter; } ;
struct TYPE_8__ {scalar_t__ Param; } ;
typedef  TYPE_2__ SESSION ;
typedef  TYPE_3__ LINK ;
typedef  TYPE_4__ BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_4__*) ; 
 TYPE_4__* GetNext (int /*<<< orphan*/ ) ; 
 scalar_t__ INFINITE ; 
 int /*<<< orphan*/  LockQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockQueue (int /*<<< orphan*/ ) ; 

UINT LinkPaGetNextPacket(SESSION *s, void **data)
{
	LINK *k;
	UINT ret = 0;
	// Validate arguments
	if (s == NULL || data == NULL || (k = (LINK *)s->PacketAdapter->Param) == NULL)
	{
		return INFINITE;
	}

	if (k->Halting || (*k->StopAllLinkFlag))
	{
		return INFINITE;
	}
	// Examine whether there are packets in the queue
	LockQueue(k->SendPacketQueue);
	{
		BLOCK *block = GetNext(k->SendPacketQueue);

		if (block != NULL)
		{
			// There was a packet
			*data = block->Buf;
			ret = block->Size;

			k->CurrentSendPacketQueueSize -= block->Size;

			// Discard the memory for the structure
			Free(block);
		}
	}
	UnlockQueue(k->SendPacketQueue);

	return ret;
}