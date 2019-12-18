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
typedef  int u8 ;
typedef  size_t u32 ;
struct iwl_rxq {size_t read; size_t write_actual; struct iwl_rx_mem_buffer** queue; TYPE_1__* rb_stts; } ;
struct iwl_trans_pcie {struct iwl_rxq rxq; } ;
struct iwl_trans {int dummy; } ;
struct iwl_rx_mem_buffer {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  closed_rb_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWL_DEBUG_RX (struct iwl_trans*,char*,size_t,...) ; 
 struct iwl_trans_pcie* IWL_TRANS_GET_PCIE_TRANS (struct iwl_trans*) ; 
 size_t RX_QUEUE_MASK ; 
 int RX_QUEUE_SIZE ; 
 int /*<<< orphan*/  iwl_pcie_rx_handle_rb (struct iwl_trans*,struct iwl_rx_mem_buffer*) ; 
 int /*<<< orphan*/  iwl_pcie_rx_replenish_now (struct iwl_trans*) ; 
 int /*<<< orphan*/  iwl_pcie_rxq_restock (struct iwl_trans*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void iwl_pcie_rx_handle(struct iwl_trans *trans)
{
	struct iwl_trans_pcie *trans_pcie = IWL_TRANS_GET_PCIE_TRANS(trans);
	struct iwl_rxq *rxq = &trans_pcie->rxq;
	u32 r, i;
	u8 fill_rx = 0;
	u32 count = 8;
	int total_empty;

	/* uCode's read index (stored in shared DRAM) indicates the last Rx
	 * buffer that the driver may process (last buffer filled by ucode). */
	r = le16_to_cpu(ACCESS_ONCE(rxq->rb_stts->closed_rb_num)) & 0x0FFF;
	i = rxq->read;

	/* Rx interrupt, but nothing sent from uCode */
	if (i == r)
		IWL_DEBUG_RX(trans, "HW = SW = %d\n", r);

	/* calculate total frames need to be restock after handling RX */
	total_empty = r - rxq->write_actual;
	if (total_empty < 0)
		total_empty += RX_QUEUE_SIZE;

	if (total_empty > (RX_QUEUE_SIZE / 2))
		fill_rx = 1;

	while (i != r) {
		struct iwl_rx_mem_buffer *rxb;

		rxb = rxq->queue[i];
		rxq->queue[i] = NULL;

		IWL_DEBUG_RX(trans, "rxbuf: HW = %d, SW = %d (%p)\n",
			     r, i, rxb);
		iwl_pcie_rx_handle_rb(trans, rxb);

		i = (i + 1) & RX_QUEUE_MASK;
		/* If there are a lot of unused frames,
		 * restock the Rx queue so ucode wont assert. */
		if (fill_rx) {
			count++;
			if (count >= 8) {
				rxq->read = i;
				iwl_pcie_rx_replenish_now(trans);
				count = 0;
			}
		}
	}

	/* Backtrack one entry */
	rxq->read = i;
	if (fill_rx)
		iwl_pcie_rx_replenish_now(trans);
	else
		iwl_pcie_rxq_restock(trans);
}