#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/ * cb; scalar_t__ data; } ;
struct nes_vnic {int /*<<< orphan*/  mgt_skb_list; int /*<<< orphan*/  max_frame_size; TYPE_1__* nesdev; int /*<<< orphan*/  mgt_wait_queue; } ;
struct nes_rskb_cb {TYPE_2__* nesqp; scalar_t__ data_start; int /*<<< orphan*/  busaddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  cm_node; } ;
struct TYPE_3__ {int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  PCI_DMA_TODEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  nes_rem_ref_cm_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_map_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_fpdus (struct sk_buff*,struct nes_vnic*,TYPE_2__*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_interruptible (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mgt_thread(void *context)
{
	struct nes_vnic *nesvnic = context;
	struct sk_buff *skb;
	struct nes_rskb_cb *cb;

	while (!kthread_should_stop()) {
		wait_event_interruptible(nesvnic->mgt_wait_queue,
					 skb_queue_len(&nesvnic->mgt_skb_list) || kthread_should_stop());
		while ((skb_queue_len(&nesvnic->mgt_skb_list)) && !kthread_should_stop()) {
			skb = skb_dequeue(&nesvnic->mgt_skb_list);
			cb = (struct nes_rskb_cb *)&skb->cb[0];
			cb->data_start = skb->data - ETH_HLEN;
			cb->busaddr = pci_map_single(nesvnic->nesdev->pcidev, cb->data_start,
						     nesvnic->max_frame_size, PCI_DMA_TODEVICE);
			queue_fpdus(skb, nesvnic, cb->nesqp);
		}
	}

	/* Closing down so delete any entries on the queue */
	while (skb_queue_len(&nesvnic->mgt_skb_list)) {
		skb = skb_dequeue(&nesvnic->mgt_skb_list);
		cb = (struct nes_rskb_cb *)&skb->cb[0];
		nes_rem_ref_cm_node(cb->nesqp->cm_node);
		dev_kfree_skb_any(skb);
	}
	return 0;
}