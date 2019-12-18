#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {int /*<<< orphan*/ * cb; } ;
struct nes_vnic {int /*<<< orphan*/  mgt_wait_queue; int /*<<< orphan*/  mgt_skb_list; } ;
struct nes_rskb_cb {struct nes_qp* nesqp; } ;
struct nes_qp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void nes_queue_mgt_skbs(struct sk_buff *skb, struct nes_vnic *nesvnic, struct nes_qp *nesqp)
{
	struct nes_rskb_cb *cb;

	cb = (struct nes_rskb_cb *)&skb->cb[0];
	cb->nesqp = nesqp;
	skb_queue_tail(&nesvnic->mgt_skb_list, skb);
	wake_up_interruptible(&nesvnic->mgt_wait_queue);
}