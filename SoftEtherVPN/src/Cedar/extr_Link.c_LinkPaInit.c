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
struct TYPE_7__ {scalar_t__ CurrentSendPacketQueueSize; scalar_t__ LastServerConnectionReceivedBlocksNum; int /*<<< orphan*/  SendPacketQueue; scalar_t__* StopAllLinkFlag; scalar_t__ Halting; } ;
struct TYPE_6__ {TYPE_1__* PacketAdapter; } ;
struct TYPE_5__ {scalar_t__ Param; } ;
typedef  int /*<<< orphan*/  THREAD ;
typedef  TYPE_2__ SESSION ;
typedef  TYPE_3__ LINK ;

/* Variables and functions */
 int /*<<< orphan*/  LinkServerSessionThread ; 
 int /*<<< orphan*/  NewQueue () ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WaitThreadInit (int /*<<< orphan*/ *) ; 

bool LinkPaInit(SESSION *s)
{
	LINK *k;
	THREAD *t;
	// Validate arguments
	if (s == NULL || (k = (LINK *)s->PacketAdapter->Param) == NULL)
	{
		return false;
	}

	if (k->Halting || (*k->StopAllLinkFlag))
	{
		return false;
	}

	// Create a transmission packet queue
	k->SendPacketQueue = NewQueue();

	// Creat a link server thread
	t = NewThread(LinkServerSessionThread, (void *)k);
	WaitThreadInit(t);

	k->LastServerConnectionReceivedBlocksNum = 0;
	k->CurrentSendPacketQueueSize = 0;

	ReleaseThread(t);

	return true;
}