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
struct hci_dev {scalar_t__ flags; int /*<<< orphan*/  (* close ) (struct hci_dev*) ;int /*<<< orphan*/ * sent_cmd; int /*<<< orphan*/  raw_q; int /*<<< orphan*/  cmd_q; int /*<<< orphan*/  rx_q; int /*<<< orphan*/  cmd_task; int /*<<< orphan*/  cmd_cnt; int /*<<< orphan*/  (* flush ) (struct hci_dev*) ;int /*<<< orphan*/  tx_task; int /*<<< orphan*/  rx_task; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,struct hci_dev*) ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  HCI_DEV_DOWN ; 
 int /*<<< orphan*/  HCI_INIT ; 
 int /*<<< orphan*/  HCI_RAW ; 
 int /*<<< orphan*/  HCI_UP ; 
 int /*<<< orphan*/  __hci_request (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  hci_conn_hash_flush (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_lock_bh (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_put (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock_bh (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_notify (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_cancel (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_reset_req ; 
 int /*<<< orphan*/  inquiry_cache_flush (struct hci_dev*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct hci_dev*) ; 
 int /*<<< orphan*/  stub2 (struct hci_dev*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int hci_dev_do_close(struct hci_dev *hdev)
{
	BT_DBG("%s %p", hdev->name, hdev);

	hci_req_cancel(hdev, ENODEV);
	hci_req_lock(hdev);

	if (!test_and_clear_bit(HCI_UP, &hdev->flags)) {
		hci_req_unlock(hdev);
		return 0;
	}

	/* Kill RX and TX tasks */
	tasklet_kill(&hdev->rx_task);
	tasklet_kill(&hdev->tx_task);

	hci_dev_lock_bh(hdev);
	inquiry_cache_flush(hdev);
	hci_conn_hash_flush(hdev);
	hci_dev_unlock_bh(hdev);

	hci_notify(hdev, HCI_DEV_DOWN);

	if (hdev->flush)
		hdev->flush(hdev);

	/* Reset device */
	skb_queue_purge(&hdev->cmd_q);
	atomic_set(&hdev->cmd_cnt, 1);
	if (!test_bit(HCI_RAW, &hdev->flags)) {
		set_bit(HCI_INIT, &hdev->flags);
		__hci_request(hdev, hci_reset_req, 0,
					msecs_to_jiffies(250));
		clear_bit(HCI_INIT, &hdev->flags);
	}

	/* Kill cmd task */
	tasklet_kill(&hdev->cmd_task);

	/* Drop queues */
	skb_queue_purge(&hdev->rx_q);
	skb_queue_purge(&hdev->cmd_q);
	skb_queue_purge(&hdev->raw_q);

	/* Drop last sent command */
	if (hdev->sent_cmd) {
		kfree_skb(hdev->sent_cmd);
		hdev->sent_cmd = NULL;
	}

	/* After this point our queues are empty
	 * and no tasks are scheduled. */
	hdev->close(hdev);

	/* Clear flags */
	hdev->flags = 0;

	hci_req_unlock(hdev);

	hci_dev_put(hdev);
	return 0;
}