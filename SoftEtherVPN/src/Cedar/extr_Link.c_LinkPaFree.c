#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ CurrentSendPacketQueueSize; int /*<<< orphan*/  SendPacketQueue; int /*<<< orphan*/  ServerSession; scalar_t__ LastServerConnectionReceivedBlocksNum; int /*<<< orphan*/  Cedar; } ;
struct TYPE_6__ {TYPE_1__* PacketAdapter; } ;
struct TYPE_5__ {scalar_t__ Param; } ;
typedef  TYPE_2__ SESSION ;
typedef  TYPE_3__ LINK ;
typedef  int /*<<< orphan*/  BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  CedarAddQueueBudget (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FreeBlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetNext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseQueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSession (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StopSession (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockQueue (int /*<<< orphan*/ ) ; 

void LinkPaFree(SESSION *s)
{
	LINK *k;
	// Validate arguments
	if (s == NULL || (k = (LINK *)s->PacketAdapter->Param) == NULL)
	{
		return;
	}

	CedarAddQueueBudget(k->Cedar, -((int)k->LastServerConnectionReceivedBlocksNum));
	k->LastServerConnectionReceivedBlocksNum = 0;

	// Stop the server session
	StopSession(k->ServerSession);
	ReleaseSession(k->ServerSession);

	// Release the transmission packet queue
	LockQueue(k->SendPacketQueue);
	{
		BLOCK *block;
		while (block = GetNext(k->SendPacketQueue))
		{
			FreeBlock(block);
		}
	}
	UnlockQueue(k->SendPacketQueue);

	ReleaseQueue(k->SendPacketQueue);

	k->CurrentSendPacketQueueSize = 0;
}