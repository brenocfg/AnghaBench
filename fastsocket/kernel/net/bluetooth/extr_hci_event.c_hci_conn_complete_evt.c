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
struct sk_buff {scalar_t__ data; } ;
struct hci_ev_conn_complete {scalar_t__ link_type; scalar_t__ status; int /*<<< orphan*/  handle; int /*<<< orphan*/  bdaddr; } ;
struct hci_dev {int hci_ver; int /*<<< orphan*/  flags; int /*<<< orphan*/  name; } ;
struct hci_cp_read_remote_features {int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  handle; } ;
struct hci_cp_change_conn_ptype {int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  handle; } ;
struct hci_conn {scalar_t__ type; int /*<<< orphan*/  handle; struct hci_conn* link; int /*<<< orphan*/  state; int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  out; int /*<<< orphan*/  link_mode; int /*<<< orphan*/  disc_timeout; } ;
typedef  int /*<<< orphan*/  cp ;

/* Variables and functions */
 scalar_t__ ACL_LINK ; 
 int /*<<< orphan*/  BT_CLOSED ; 
 int /*<<< orphan*/  BT_CONFIG ; 
 int /*<<< orphan*/  BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ESCO_LINK ; 
 int /*<<< orphan*/  HCI_AUTH ; 
 int /*<<< orphan*/  HCI_DISCONN_TIMEOUT ; 
 int /*<<< orphan*/  HCI_ENCRYPT ; 
 int /*<<< orphan*/  HCI_LM_AUTH ; 
 int /*<<< orphan*/  HCI_LM_ENCRYPT ; 
 int /*<<< orphan*/  HCI_OP_CHANGE_CONN_PTYPE ; 
 int /*<<< orphan*/  HCI_OP_READ_REMOTE_FEATURES ; 
 scalar_t__ SCO_LINK ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_add_sco (struct hci_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_conn_add_sysfs (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_conn_check_pending (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_conn_del (struct hci_conn*) ; 
 struct hci_conn* hci_conn_hash_lookup_ba (struct hci_dev*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_conn_hold (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_conn_hold_device (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_proto_connect_cfm (struct hci_conn*,scalar_t__) ; 
 int /*<<< orphan*/  hci_send_cmd (struct hci_dev*,int /*<<< orphan*/ ,int,struct hci_cp_read_remote_features*) ; 
 int /*<<< orphan*/  hci_setup_sync (struct hci_conn*,int /*<<< orphan*/ ) ; 
 scalar_t__ lmp_esco_capable (struct hci_dev*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void hci_conn_complete_evt(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_ev_conn_complete *ev = (void *) skb->data;
	struct hci_conn *conn;

	BT_DBG("%s", hdev->name);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_ba(hdev, ev->link_type, &ev->bdaddr);
	if (!conn) {
		if (ev->link_type != SCO_LINK)
			goto unlock;

		conn = hci_conn_hash_lookup_ba(hdev, ESCO_LINK, &ev->bdaddr);
		if (!conn)
			goto unlock;

		conn->type = SCO_LINK;
	}

	if (!ev->status) {
		conn->handle = __le16_to_cpu(ev->handle);

		if (conn->type == ACL_LINK) {
			conn->state = BT_CONFIG;
			hci_conn_hold(conn);
			conn->disc_timeout = HCI_DISCONN_TIMEOUT;
		} else
			conn->state = BT_CONNECTED;

		hci_conn_hold_device(conn);
		hci_conn_add_sysfs(conn);

		if (test_bit(HCI_AUTH, &hdev->flags))
			conn->link_mode |= HCI_LM_AUTH;

		if (test_bit(HCI_ENCRYPT, &hdev->flags))
			conn->link_mode |= HCI_LM_ENCRYPT;

		/* Get remote features */
		if (conn->type == ACL_LINK) {
			struct hci_cp_read_remote_features cp;
			cp.handle = ev->handle;
			hci_send_cmd(hdev, HCI_OP_READ_REMOTE_FEATURES,
							sizeof(cp), &cp);
		}

		/* Set packet type for incoming connection */
		if (!conn->out && hdev->hci_ver < 3) {
			struct hci_cp_change_conn_ptype cp;
			cp.handle = ev->handle;
			cp.pkt_type = cpu_to_le16(conn->pkt_type);
			hci_send_cmd(hdev, HCI_OP_CHANGE_CONN_PTYPE,
							sizeof(cp), &cp);
		}
	} else
		conn->state = BT_CLOSED;

	if (conn->type == ACL_LINK) {
		struct hci_conn *sco = conn->link;
		if (sco) {
			if (!ev->status) {
				if (lmp_esco_capable(hdev))
					hci_setup_sync(sco, conn->handle);
				else
					hci_add_sco(sco, conn->handle);
			} else {
				hci_proto_connect_cfm(sco, ev->status);
				hci_conn_del(sco);
			}
		}
	}

	if (ev->status) {
		hci_proto_connect_cfm(conn, ev->status);
		hci_conn_del(conn);
	} else if (ev->link_type != ACL_LINK)
		hci_proto_connect_cfm(conn, ev->status);

unlock:
	hci_dev_unlock(hdev);

	hci_conn_check_pending(hdev);
}