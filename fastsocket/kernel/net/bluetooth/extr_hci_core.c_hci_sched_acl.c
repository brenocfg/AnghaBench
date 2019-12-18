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
struct sk_buff {int /*<<< orphan*/  len; } ;
struct hci_dev {scalar_t__ acl_cnt; scalar_t__ acl_last_tx; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;
struct hci_conn {int /*<<< orphan*/  sent; int /*<<< orphan*/  data_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LINK ; 
 int /*<<< orphan*/  BT_DBG (char*,struct sk_buff*,...) ; 
 int /*<<< orphan*/  HCI_RAW ; 
 int HZ ; 
 int /*<<< orphan*/  hci_acl_tx_to (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_conn_enter_active_mode (struct hci_conn*) ; 
 struct hci_conn* hci_low_sent (struct hci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  hci_send_frame (struct sk_buff*) ; 
 scalar_t__ jiffies ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void hci_sched_acl(struct hci_dev *hdev)
{
	struct hci_conn *conn;
	struct sk_buff *skb;
	int quote;

	BT_DBG("%s", hdev->name);

	if (!test_bit(HCI_RAW, &hdev->flags)) {
		/* ACL tx timeout must be longer than maximum
		 * link supervision timeout (40.9 seconds) */
		if (!hdev->acl_cnt && time_after(jiffies, hdev->acl_last_tx + HZ * 45))
			hci_acl_tx_to(hdev);
	}

	while (hdev->acl_cnt && (conn = hci_low_sent(hdev, ACL_LINK, &quote))) {
		while (quote-- && (skb = skb_dequeue(&conn->data_q))) {
			BT_DBG("skb %p len %d", skb, skb->len);

			hci_conn_enter_active_mode(conn);

			hci_send_frame(skb);
			hdev->acl_last_tx = jiffies;

			hdev->acl_cnt--;
			conn->sent++;
		}
	}
}