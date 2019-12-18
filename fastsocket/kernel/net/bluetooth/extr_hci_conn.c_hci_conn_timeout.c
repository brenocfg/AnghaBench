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
struct hci_dev {int dummy; } ;
struct hci_conn {int state; int /*<<< orphan*/  out; int /*<<< orphan*/  type; int /*<<< orphan*/  refcnt; struct hci_dev* hdev; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LINK ; 
 int BT_CLOSED ; 
#define  BT_CONFIG 131 
#define  BT_CONNECT 130 
#define  BT_CONNECT2 129 
#define  BT_CONNECTED 128 
 int /*<<< orphan*/  BT_DBG (char*,struct hci_conn*,int) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_acl_connect_cancel (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_acl_disconn (struct hci_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_proto_disconn_ind (struct hci_conn*) ; 

__attribute__((used)) static void hci_conn_timeout(unsigned long arg)
{
	struct hci_conn *conn = (void *) arg;
	struct hci_dev *hdev = conn->hdev;
	__u8 reason;

	BT_DBG("conn %p state %d", conn, conn->state);

	if (atomic_read(&conn->refcnt))
		return;

	hci_dev_lock(hdev);

	switch (conn->state) {
	case BT_CONNECT:
	case BT_CONNECT2:
		if (conn->type == ACL_LINK && conn->out)
			hci_acl_connect_cancel(conn);
		break;
	case BT_CONFIG:
	case BT_CONNECTED:
		reason = hci_proto_disconn_ind(conn);
		hci_acl_disconn(conn, reason);
		break;
	default:
		conn->state = BT_CLOSED;
		break;
	}

	hci_dev_unlock(hdev);
}