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
typedef  scalar_t__ uint32_t ;
struct list_head {int dummy; } ;
struct TYPE_7__ {struct list_head* next; } ;
struct TYPE_5__ {scalar_t__ nBusySend; TYPE_2__* CurrSendHead; int /*<<< orphan*/ * CurrSendTail; scalar_t__ nWaitSend; TYPE_3__ SendWaitQueue; } ;
struct et131x_adapter {TYPE_1__ TxRing; int /*<<< orphan*/  TCBSendQLock; int /*<<< orphan*/  SendWaitLock; } ;
struct TYPE_6__ {struct TYPE_6__* Next; } ;
typedef  TYPE_2__* PMP_TCB ;

/* Variables and functions */
 scalar_t__ NUM_TCB ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  et131x_free_send_packet (struct et131x_adapter*,TYPE_2__*) ; 
 int /*<<< orphan*/  list_empty (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void et131x_free_busy_send_packets(struct et131x_adapter *etdev)
{
	PMP_TCB pMpTcb;
	struct list_head *entry;
	unsigned long flags;
	uint32_t FreeCounter = 0;

	while (!list_empty(&etdev->TxRing.SendWaitQueue)) {
		spin_lock_irqsave(&etdev->SendWaitLock, flags);

		etdev->TxRing.nWaitSend--;
		spin_unlock_irqrestore(&etdev->SendWaitLock, flags);

		entry = etdev->TxRing.SendWaitQueue.next;
	}

	etdev->TxRing.nWaitSend = 0;

	/* Any packets being sent? Check the first TCB on the send list */
	spin_lock_irqsave(&etdev->TCBSendQLock, flags);

	pMpTcb = etdev->TxRing.CurrSendHead;

	while ((pMpTcb != NULL) && (FreeCounter < NUM_TCB)) {
		PMP_TCB pNext = pMpTcb->Next;

		etdev->TxRing.CurrSendHead = pNext;

		if (pNext == NULL)
			etdev->TxRing.CurrSendTail = NULL;

		etdev->TxRing.nBusySend--;

		spin_unlock_irqrestore(&etdev->TCBSendQLock, flags);

		FreeCounter++;
		et131x_free_send_packet(etdev, pMpTcb);

		spin_lock_irqsave(&etdev->TCBSendQLock, flags);

		pMpTcb = etdev->TxRing.CurrSendHead;
	}

	WARN_ON(FreeCounter == NUM_TCB);

	spin_unlock_irqrestore(&etdev->TCBSendQLock, flags);

	etdev->TxRing.nBusySend = 0;
}