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
struct sk_buff {int dummy; } ;
struct hci_dev {int /*<<< orphan*/  cmd_q; scalar_t__ cmd_last_tx; int /*<<< orphan*/  cmd_cnt; int /*<<< orphan*/  sent_cmd; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  BT_ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hci_sched_cmd (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_send_frame (struct sk_buff*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 scalar_t__ time_after (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void hci_cmd_task(unsigned long arg)
{
	struct hci_dev *hdev = (struct hci_dev *) arg;
	struct sk_buff *skb;

	BT_DBG("%s cmd %d", hdev->name, atomic_read(&hdev->cmd_cnt));

	if (!atomic_read(&hdev->cmd_cnt) && time_after(jiffies, hdev->cmd_last_tx + HZ)) {
		BT_ERR("%s command tx timeout", hdev->name);
		atomic_set(&hdev->cmd_cnt, 1);
	}

	/* Send queued commands */
	if (atomic_read(&hdev->cmd_cnt) && (skb = skb_dequeue(&hdev->cmd_q))) {
		kfree_skb(hdev->sent_cmd);

		if ((hdev->sent_cmd = skb_clone(skb, GFP_ATOMIC))) {
			atomic_dec(&hdev->cmd_cnt);
			hci_send_frame(skb);
			hdev->cmd_last_tx = jiffies;
		} else {
			skb_queue_head(&hdev->cmd_q, skb);
			hci_sched_cmd(hdev);
		}
	}
}