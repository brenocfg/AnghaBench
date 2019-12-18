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
struct hci_ev_encrypt_change {scalar_t__ encrypt; int /*<<< orphan*/  status; int /*<<< orphan*/  handle; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
struct hci_conn {scalar_t__ state; int /*<<< orphan*/  pend; int /*<<< orphan*/  link_mode; } ;

/* Variables and functions */
 scalar_t__ BT_CONFIG ; 
 scalar_t__ BT_CONNECTED ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_CONN_ENCRYPT_PEND ; 
 int /*<<< orphan*/  HCI_LM_AUTH ; 
 int /*<<< orphan*/  HCI_LM_ENCRYPT ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hci_conn* hci_conn_hash_lookup_handle (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_conn_put (struct hci_conn*) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_encrypt_cfm (struct hci_conn*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hci_proto_connect_cfm (struct hci_conn*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void hci_encrypt_change_evt(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_ev_encrypt_change *ev = (void *) skb->data;
	struct hci_conn *conn;

	BT_DBG("%s status %d", hdev->name, ev->status);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_handle(hdev, __le16_to_cpu(ev->handle));
	if (conn) {
		if (!ev->status) {
			if (ev->encrypt) {
				/* Encryption implies authentication */
				conn->link_mode |= HCI_LM_AUTH;
				conn->link_mode |= HCI_LM_ENCRYPT;
			} else
				conn->link_mode &= ~HCI_LM_ENCRYPT;
		}

		clear_bit(HCI_CONN_ENCRYPT_PEND, &conn->pend);

		if (conn->state == BT_CONFIG) {
			if (!ev->status)
				conn->state = BT_CONNECTED;

			hci_proto_connect_cfm(conn, ev->status);
			hci_conn_put(conn);
		} else
			hci_encrypt_cfm(conn, ev->status, ev->encrypt);
	}

	hci_dev_unlock(hdev);
}