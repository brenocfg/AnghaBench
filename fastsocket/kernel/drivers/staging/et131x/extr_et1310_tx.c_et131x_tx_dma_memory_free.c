#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  MpTcbMem; int /*<<< orphan*/ * pTxDummyBlkVa; int /*<<< orphan*/  pTxDummyBlkPa; int /*<<< orphan*/ * pTxStatusVa; int /*<<< orphan*/  pTxStatusPa; int /*<<< orphan*/ * pTxDescRingVa; int /*<<< orphan*/  pTxDescRingPa; scalar_t__ TxDescOffset; } ;
struct et131x_adapter {TYPE_1__ TxRing; int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  TX_STATUS_BLOCK_t ;
typedef  int /*<<< orphan*/  TX_DESC_ENTRY_t ;

/* Variables and functions */
 int NIC_MIN_PACKET_SIZE ; 
 int NUM_DESC_PER_RING_TX ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void et131x_tx_dma_memory_free(struct et131x_adapter *adapter)
{
	int desc_size = 0;

	if (adapter->TxRing.pTxDescRingVa) {
		/* Free memory relating to Tx rings here */
		adapter->TxRing.pTxDescRingVa -= adapter->TxRing.TxDescOffset;

		desc_size =
		    (sizeof(TX_DESC_ENTRY_t) * NUM_DESC_PER_RING_TX) + 4096 - 1;

		pci_free_consistent(adapter->pdev,
				    desc_size,
				    adapter->TxRing.pTxDescRingVa,
				    adapter->TxRing.pTxDescRingPa);

		adapter->TxRing.pTxDescRingVa = NULL;
	}

	/* Free memory for the Tx status block */
	if (adapter->TxRing.pTxStatusVa) {
		pci_free_consistent(adapter->pdev,
				    sizeof(TX_STATUS_BLOCK_t),
				    adapter->TxRing.pTxStatusVa,
				    adapter->TxRing.pTxStatusPa);

		adapter->TxRing.pTxStatusVa = NULL;
	}

	/* Free memory for the dummy buffer */
	if (adapter->TxRing.pTxDummyBlkVa) {
		pci_free_consistent(adapter->pdev,
				    NIC_MIN_PACKET_SIZE,
				    adapter->TxRing.pTxDummyBlkVa,
				    adapter->TxRing.pTxDummyBlkPa);

		adapter->TxRing.pTxDummyBlkVa = NULL;
	}

	/* Free the memory for MP_TCB structures */
	kfree(adapter->TxRing.MpTcbMem);
}