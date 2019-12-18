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
struct hci_dev {scalar_t__ flags; int /*<<< orphan*/  (* close ) (struct hci_dev*) ;int /*<<< orphan*/ * sent_cmd; int /*<<< orphan*/  (* flush ) (struct hci_dev*) ;int /*<<< orphan*/  rx_q; int /*<<< orphan*/  cmd_q; int /*<<< orphan*/  cmd_task; int /*<<< orphan*/  tx_task; int /*<<< orphan*/  rx_task; int /*<<< orphan*/  cmd_cnt; scalar_t__ (* open ) (struct hci_dev*) ;scalar_t__ quirks; scalar_t__ rfkill; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,struct hci_dev*) ; 
 int EALREADY ; 
 int EIO ; 
 int ENODEV ; 
 int ERFKILL ; 
 int /*<<< orphan*/  HCI_DEV_UP ; 
 int /*<<< orphan*/  HCI_INIT ; 
 int /*<<< orphan*/  HCI_INIT_TIMEOUT ; 
 int /*<<< orphan*/  HCI_QUIRK_RAW_DEVICE ; 
 int /*<<< orphan*/  HCI_RAW ; 
 int /*<<< orphan*/  HCI_UP ; 
 int __hci_request (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 struct hci_dev* hci_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_hold (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_put (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_init_req ; 
 int /*<<< orphan*/  hci_notify (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_req_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 scalar_t__ rfkill_blocked (scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct hci_dev*) ; 
 int /*<<< orphan*/  stub2 (struct hci_dev*) ; 
 int /*<<< orphan*/  stub3 (struct hci_dev*) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,scalar_t__*) ; 

int hci_dev_open(__u16 dev)
{
	struct hci_dev *hdev;
	int ret = 0;

	if (!(hdev = hci_dev_get(dev)))
		return -ENODEV;

	BT_DBG("%s %p", hdev->name, hdev);

	hci_req_lock(hdev);

	if (hdev->rfkill && rfkill_blocked(hdev->rfkill)) {
		ret = -ERFKILL;
		goto done;
	}

	if (test_bit(HCI_UP, &hdev->flags)) {
		ret = -EALREADY;
		goto done;
	}

	if (test_bit(HCI_QUIRK_RAW_DEVICE, &hdev->quirks))
		set_bit(HCI_RAW, &hdev->flags);

	if (hdev->open(hdev)) {
		ret = -EIO;
		goto done;
	}

	if (!test_bit(HCI_RAW, &hdev->flags)) {
		atomic_set(&hdev->cmd_cnt, 1);
		set_bit(HCI_INIT, &hdev->flags);

		//__hci_request(hdev, hci_reset_req, 0, HZ);
		ret = __hci_request(hdev, hci_init_req, 0,
					msecs_to_jiffies(HCI_INIT_TIMEOUT));

		clear_bit(HCI_INIT, &hdev->flags);
	}

	if (!ret) {
		hci_dev_hold(hdev);
		set_bit(HCI_UP, &hdev->flags);
		hci_notify(hdev, HCI_DEV_UP);
	} else {
		/* Init failed, cleanup */
		tasklet_kill(&hdev->rx_task);
		tasklet_kill(&hdev->tx_task);
		tasklet_kill(&hdev->cmd_task);

		skb_queue_purge(&hdev->cmd_q);
		skb_queue_purge(&hdev->rx_q);

		if (hdev->flush)
			hdev->flush(hdev);

		if (hdev->sent_cmd) {
			kfree_skb(hdev->sent_cmd);
			hdev->sent_cmd = NULL;
		}

		hdev->close(hdev);
		hdev->flags = 0;
	}

done:
	hci_req_unlock(hdev);
	hci_dev_put(hdev);
	return ret;
}