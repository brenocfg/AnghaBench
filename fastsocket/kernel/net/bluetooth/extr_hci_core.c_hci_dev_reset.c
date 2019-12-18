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
struct hci_dev {int /*<<< orphan*/  tx_task; int /*<<< orphan*/  flags; scalar_t__ sco_cnt; scalar_t__ acl_cnt; int /*<<< orphan*/  cmd_cnt; int /*<<< orphan*/  (* flush ) (struct hci_dev*) ;int /*<<< orphan*/  cmd_q; int /*<<< orphan*/  rx_q; } ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  HCI_INIT_TIMEOUT ; 
 int /*<<< orphan*/  HCI_RAW ; 
 int /*<<< orphan*/  HCI_UP ; 
 int __hci_request (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hci_conn_hash_flush (struct hci_dev*) ; 
 struct hci_dev* hci_dev_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock_bh (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_put (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock_bh (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_req_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_reset_req ; 
 int /*<<< orphan*/  inquiry_cache_flush (struct hci_dev*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct hci_dev*) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int hci_dev_reset(__u16 dev)
{
	struct hci_dev *hdev;
	int ret = 0;

	if (!(hdev = hci_dev_get(dev)))
		return -ENODEV;

	hci_req_lock(hdev);
	tasklet_disable(&hdev->tx_task);

	if (!test_bit(HCI_UP, &hdev->flags))
		goto done;

	/* Drop queues */
	skb_queue_purge(&hdev->rx_q);
	skb_queue_purge(&hdev->cmd_q);

	hci_dev_lock_bh(hdev);
	inquiry_cache_flush(hdev);
	hci_conn_hash_flush(hdev);
	hci_dev_unlock_bh(hdev);

	if (hdev->flush)
		hdev->flush(hdev);

	atomic_set(&hdev->cmd_cnt, 1);
	hdev->acl_cnt = 0; hdev->sco_cnt = 0;

	if (!test_bit(HCI_RAW, &hdev->flags))
		ret = __hci_request(hdev, hci_reset_req, 0,
					msecs_to_jiffies(HCI_INIT_TIMEOUT));

done:
	tasklet_enable(&hdev->tx_task);
	hci_req_unlock(hdev);
	hci_dev_put(hdev);
	return ret;
}