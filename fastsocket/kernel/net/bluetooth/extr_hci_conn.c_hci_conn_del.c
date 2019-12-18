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
struct hci_dev {int /*<<< orphan*/  tx_task; int /*<<< orphan*/  (* notify ) (struct hci_dev*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  acl_cnt; int /*<<< orphan*/  name; } ;
struct hci_conn {scalar_t__ type; int /*<<< orphan*/  data_q; struct hci_conn* link; scalar_t__ sent; int /*<<< orphan*/  disc_timer; int /*<<< orphan*/  idle_timer; int /*<<< orphan*/  handle; struct hci_dev* hdev; } ;

/* Variables and functions */
 scalar_t__ ACL_LINK ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,struct hci_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_NOTIFY_CONN_DEL ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_conn_hash_del (struct hci_dev*,struct hci_conn*) ; 
 int /*<<< orphan*/  hci_conn_put (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_conn_put_device (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_dev_put (struct hci_dev*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_enable (int /*<<< orphan*/ *) ; 

int hci_conn_del(struct hci_conn *conn)
{
	struct hci_dev *hdev = conn->hdev;

	BT_DBG("%s conn %p handle %d", hdev->name, conn, conn->handle);

	del_timer(&conn->idle_timer);

	del_timer(&conn->disc_timer);

	if (conn->type == ACL_LINK) {
		struct hci_conn *sco = conn->link;
		if (sco)
			sco->link = NULL;

		/* Unacked frames */
		hdev->acl_cnt += conn->sent;
	} else {
		struct hci_conn *acl = conn->link;
		if (acl) {
			acl->link = NULL;
			hci_conn_put(acl);
		}
	}

	tasklet_disable(&hdev->tx_task);

	hci_conn_hash_del(hdev, conn);
	if (hdev->notify)
		hdev->notify(hdev, HCI_NOTIFY_CONN_DEL);

	tasklet_enable(&hdev->tx_task);

	skb_queue_purge(&conn->data_q);

	hci_conn_put_device(conn);

	hci_dev_put(hdev);

	return 0;
}