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
struct hci_dev {int /*<<< orphan*/  name; int /*<<< orphan*/  flags; int /*<<< orphan*/  promisc; int /*<<< orphan*/  rx_q; } ;
struct TYPE_2__ {int pkt_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
#define  HCI_ACLDATA_PKT 130 
#define  HCI_EVENT_PKT 129 
 int /*<<< orphan*/  HCI_INIT ; 
 int /*<<< orphan*/  HCI_RAW ; 
#define  HCI_SCODATA_PKT 128 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__* bt_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  hci_acldata_packet (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_event_packet (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_scodata_packet (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_send_to_sock (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_task_lock ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_rx_task(unsigned long arg)
{
	struct hci_dev *hdev = (struct hci_dev *) arg;
	struct sk_buff *skb;

	BT_DBG("%s", hdev->name);

	read_lock(&hci_task_lock);

	while ((skb = skb_dequeue(&hdev->rx_q))) {
		if (atomic_read(&hdev->promisc)) {
			/* Send copy to the sockets */
			hci_send_to_sock(hdev, skb);
		}

		if (test_bit(HCI_RAW, &hdev->flags)) {
			kfree_skb(skb);
			continue;
		}

		if (test_bit(HCI_INIT, &hdev->flags)) {
			/* Don't process data packets in this states. */
			switch (bt_cb(skb)->pkt_type) {
			case HCI_ACLDATA_PKT:
			case HCI_SCODATA_PKT:
				kfree_skb(skb);
				continue;
			}
		}

		/* Process frame */
		switch (bt_cb(skb)->pkt_type) {
		case HCI_EVENT_PKT:
			hci_event_packet(hdev, skb);
			break;

		case HCI_ACLDATA_PKT:
			BT_DBG("%s ACL data packet", hdev->name);
			hci_acldata_packet(hdev, skb);
			break;

		case HCI_SCODATA_PKT:
			BT_DBG("%s SCO data packet", hdev->name);
			hci_scodata_packet(hdev, skb);
			break;

		default:
			kfree_skb(skb);
			break;
		}
	}

	read_unlock(&hci_task_lock);
}