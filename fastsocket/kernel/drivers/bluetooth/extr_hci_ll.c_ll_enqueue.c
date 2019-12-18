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
struct sk_buff {int dummy; } ;
struct ll_struct {int hcill_state; int /*<<< orphan*/  hcill_lock; int /*<<< orphan*/  tx_wait_q; int /*<<< orphan*/  txq; } ;
struct hci_uart {struct ll_struct* priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  pkt_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,...) ; 
 int /*<<< orphan*/  BT_ERR (char*,...) ; 
#define  HCILL_ASLEEP 130 
#define  HCILL_ASLEEP_TO_AWAKE 129 
#define  HCILL_AWAKE 128 
 int /*<<< orphan*/  HCILL_WAKE_UP_IND ; 
 TYPE_1__* bt_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  send_hcill_cmd (int /*<<< orphan*/ ,struct hci_uart*) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ll_enqueue(struct hci_uart *hu, struct sk_buff *skb)
{
	unsigned long flags = 0;
	struct ll_struct *ll = hu->priv;

	BT_DBG("hu %p skb %p", hu, skb);

	/* Prepend skb with frame type */
	memcpy(skb_push(skb, 1), &bt_cb(skb)->pkt_type, 1);

	/* lock hcill state */
	spin_lock_irqsave(&ll->hcill_lock, flags);

	/* act according to current state */
	switch (ll->hcill_state) {
	case HCILL_AWAKE:
		BT_DBG("device awake, sending normally");
		skb_queue_tail(&ll->txq, skb);
		break;
	case HCILL_ASLEEP:
		BT_DBG("device asleep, waking up and queueing packet");
		/* save packet for later */
		skb_queue_tail(&ll->tx_wait_q, skb);
		/* awake device */
		if (send_hcill_cmd(HCILL_WAKE_UP_IND, hu) < 0) {
			BT_ERR("cannot wake up device");
			break;
		}
		ll->hcill_state = HCILL_ASLEEP_TO_AWAKE;
		break;
	case HCILL_ASLEEP_TO_AWAKE:
		BT_DBG("device waking up, queueing packet");
		/* transient state; just keep packet for later */
		skb_queue_tail(&ll->tx_wait_q, skb);
		break;
	default:
		BT_ERR("illegal hcill state: %ld (losing packet)", ll->hcill_state);
		kfree_skb(skb);
		break;
	}

	spin_unlock_irqrestore(&ll->hcill_lock, flags);

	return 0;
}