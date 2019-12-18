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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
struct hci_uart {struct bcsp_struct* priv; } ;
struct TYPE_4__ {scalar_t__ qlen; int /*<<< orphan*/  lock; } ;
struct bcsp_struct {scalar_t__ txack_req; TYPE_2__ unack; int /*<<< orphan*/  rel; int /*<<< orphan*/  tbcsp; int /*<<< orphan*/  unrel; } ;
struct TYPE_3__ {int /*<<< orphan*/  pkt_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCSP_ACK_PKT ; 
 scalar_t__ BCSP_TXWINSIZE ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int HZ ; 
 int /*<<< orphan*/  SINGLE_DEPTH_NESTING ; 
 int /*<<< orphan*/  __skb_queue_tail (TYPE_2__*,struct sk_buff*) ; 
 struct sk_buff* bcsp_prepare_pkt (struct bcsp_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* bt_cb (struct sk_buff*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave_nested (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct sk_buff *bcsp_dequeue(struct hci_uart *hu)
{
	struct bcsp_struct *bcsp = hu->priv;
	unsigned long flags;
	struct sk_buff *skb;
	
	/* First of all, check for unreliable messages in the queue,
	   since they have priority */

	if ((skb = skb_dequeue(&bcsp->unrel)) != NULL) {
		struct sk_buff *nskb = bcsp_prepare_pkt(bcsp, skb->data, skb->len, bt_cb(skb)->pkt_type);
		if (nskb) {
			kfree_skb(skb);
			return nskb;
		} else {
			skb_queue_head(&bcsp->unrel, skb);
			BT_ERR("Could not dequeue pkt because alloc_skb failed");
		}
	}

	/* Now, try to send a reliable pkt. We can only send a
	   reliable packet if the number of packets sent but not yet ack'ed
	   is < than the winsize */

	spin_lock_irqsave_nested(&bcsp->unack.lock, flags, SINGLE_DEPTH_NESTING);

	if (bcsp->unack.qlen < BCSP_TXWINSIZE && (skb = skb_dequeue(&bcsp->rel)) != NULL) {
		struct sk_buff *nskb = bcsp_prepare_pkt(bcsp, skb->data, skb->len, bt_cb(skb)->pkt_type);
		if (nskb) {
			__skb_queue_tail(&bcsp->unack, skb);
			mod_timer(&bcsp->tbcsp, jiffies + HZ / 4);
			spin_unlock_irqrestore(&bcsp->unack.lock, flags);
			return nskb;
		} else {
			skb_queue_head(&bcsp->rel, skb);
			BT_ERR("Could not dequeue pkt because alloc_skb failed");
		}
	}

	spin_unlock_irqrestore(&bcsp->unack.lock, flags);

	/* We could not send a reliable packet, either because there are
	   none or because there are too many unack'ed pkts. Did we receive
	   any packets we have not acknowledged yet ? */

	if (bcsp->txack_req) {
		/* if so, craft an empty ACK pkt and send it on BCSP unreliable
		   channel 0 */
		struct sk_buff *nskb = bcsp_prepare_pkt(bcsp, NULL, 0, BCSP_ACK_PKT);
		return nskb;
	}

	/* We have nothing to send */
	return NULL;
}