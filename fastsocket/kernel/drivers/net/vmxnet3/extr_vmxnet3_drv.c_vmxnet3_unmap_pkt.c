#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_6__ {size_t next2comp; int /*<<< orphan*/  size; TYPE_1__* base; } ;
struct vmxnet3_tx_queue {TYPE_3__ tx_ring; TYPE_2__* buf_info; } ;
struct vmxnet3_adapter {int dummy; } ;
struct sk_buff {int dummy; } ;
struct pci_dev {int dummy; } ;
struct TYPE_5__ {size_t sop_idx; struct sk_buff* skb; } ;
struct TYPE_4__ {int /*<<< orphan*/  txd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  VMXNET3_INC_RING_IDX_ONLY (size_t,int /*<<< orphan*/ ) ; 
 int VMXNET3_TXDESC_GET_EOP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  vmxnet3_cmd_ring_adv_next2comp (TYPE_3__*) ; 
 int /*<<< orphan*/  vmxnet3_unmap_tx_buf (TYPE_2__*,struct pci_dev*) ; 

__attribute__((used)) static int
vmxnet3_unmap_pkt(u32 eop_idx, struct vmxnet3_tx_queue *tq,
		  struct pci_dev *pdev,	struct vmxnet3_adapter *adapter)
{
	struct sk_buff *skb;
	int entries = 0;

	/* no out of order completion */
	BUG_ON(tq->buf_info[eop_idx].sop_idx != tq->tx_ring.next2comp);
	BUG_ON(VMXNET3_TXDESC_GET_EOP(&(tq->tx_ring.base[eop_idx].txd)) != 1);

	skb = tq->buf_info[eop_idx].skb;
	BUG_ON(skb == NULL);
	tq->buf_info[eop_idx].skb = NULL;

	VMXNET3_INC_RING_IDX_ONLY(eop_idx, tq->tx_ring.size);

	while (tq->tx_ring.next2comp != eop_idx) {
		vmxnet3_unmap_tx_buf(tq->buf_info + tq->tx_ring.next2comp,
				     pdev);

		/* update next2comp w/o tx_lock. Since we are marking more,
		 * instead of less, tx ring entries avail, the worst case is
		 * that the tx routine incorrectly re-queues a pkt due to
		 * insufficient tx ring entries.
		 */
		vmxnet3_cmd_ring_adv_next2comp(&tq->tx_ring);
		entries++;
	}

	dev_kfree_skb_any(skb);
	return entries;
}