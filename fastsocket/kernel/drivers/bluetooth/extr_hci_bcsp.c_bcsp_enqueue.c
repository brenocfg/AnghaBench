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
struct sk_buff {int len; } ;
struct hci_uart {struct bcsp_struct* priv; } ;
struct bcsp_struct {int /*<<< orphan*/  unrel; int /*<<< orphan*/  rel; } ;
struct TYPE_2__ {int pkt_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_ERR (char*) ; 
#define  HCI_ACLDATA_PKT 130 
#define  HCI_COMMAND_PKT 129 
#define  HCI_SCODATA_PKT 128 
 TYPE_1__* bt_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static int bcsp_enqueue(struct hci_uart *hu, struct sk_buff *skb)
{
	struct bcsp_struct *bcsp = hu->priv;

	if (skb->len > 0xFFF) {
		BT_ERR("Packet too long");
		kfree_skb(skb);
		return 0;
	}

	switch (bt_cb(skb)->pkt_type) {
	case HCI_ACLDATA_PKT:
	case HCI_COMMAND_PKT:
		skb_queue_tail(&bcsp->rel, skb);
		break;

	case HCI_SCODATA_PKT:
		skb_queue_tail(&bcsp->unrel, skb);
		break;

	default:
		BT_ERR("Unknown packet type");
		kfree_skb(skb);
		break;
	}

	return 0;
}