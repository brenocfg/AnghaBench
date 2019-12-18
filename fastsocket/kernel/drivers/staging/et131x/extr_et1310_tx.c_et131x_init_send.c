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
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  SendWaitQueue; TYPE_2__* CurrSendTail; TYPE_2__* CurrSendHead; TYPE_2__* TCBReadyQueueTail; TYPE_2__* TCBReadyQueueHead; TYPE_2__* MpTcbMem; } ;
struct et131x_adapter {TYPE_1__ TxRing; } ;
struct TYPE_5__ {struct TYPE_5__* Next; } ;
typedef  TYPE_1__ TX_RING_t ;
typedef  TYPE_2__* PMP_TCB ;
typedef  int /*<<< orphan*/  MP_TCB ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int NUM_TCB ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void et131x_init_send(struct et131x_adapter *adapter)
{
	PMP_TCB pMpTcb;
	uint32_t TcbCount;
	TX_RING_t *tx_ring;

	/* Setup some convenience pointers */
	tx_ring = &adapter->TxRing;
	pMpTcb = adapter->TxRing.MpTcbMem;

	tx_ring->TCBReadyQueueHead = pMpTcb;

	/* Go through and set up each TCB */
	for (TcbCount = 0; TcbCount < NUM_TCB; TcbCount++) {
		memset(pMpTcb, 0, sizeof(MP_TCB));

		/* Set the link pointer in HW TCB to the next TCB in the
		 * chain.  If this is the last TCB in the chain, also set the
		 * tail pointer.
		 */
		if (TcbCount < NUM_TCB - 1) {
			pMpTcb->Next = pMpTcb + 1;
		} else {
			tx_ring->TCBReadyQueueTail = pMpTcb;
			pMpTcb->Next = (PMP_TCB) NULL;
		}

		pMpTcb++;
	}

	/* Curr send queue should now be empty */
	tx_ring->CurrSendHead = (PMP_TCB) NULL;
	tx_ring->CurrSendTail = (PMP_TCB) NULL;

	INIT_LIST_HEAD(&adapter->TxRing.SendWaitQueue);
}