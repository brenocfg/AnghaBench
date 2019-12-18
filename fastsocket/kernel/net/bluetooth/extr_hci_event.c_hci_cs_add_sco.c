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
struct hci_dev {int /*<<< orphan*/  name; } ;
struct hci_cp_add_sco {int /*<<< orphan*/  handle; } ;
struct hci_conn {int /*<<< orphan*/  state; struct hci_conn* link; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CLOSED ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_OP_ADD_SCO ; 
 int /*<<< orphan*/  __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_conn_del (struct hci_conn*) ; 
 struct hci_conn* hci_conn_hash_lookup_handle (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_proto_connect_cfm (struct hci_conn*,int /*<<< orphan*/ ) ; 
 struct hci_cp_add_sco* hci_sent_cmd_data (struct hci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hci_cs_add_sco(struct hci_dev *hdev, __u8 status)
{
	struct hci_cp_add_sco *cp;
	struct hci_conn *acl, *sco;
	__u16 handle;

	BT_DBG("%s status 0x%x", hdev->name, status);

	if (!status)
		return;

	cp = hci_sent_cmd_data(hdev, HCI_OP_ADD_SCO);
	if (!cp)
		return;

	handle = __le16_to_cpu(cp->handle);

	BT_DBG("%s handle %d", hdev->name, handle);

	hci_dev_lock(hdev);

	acl = hci_conn_hash_lookup_handle(hdev, handle);
	if (acl && (sco = acl->link)) {
		sco->state = BT_CLOSED;

		hci_proto_connect_cfm(sco, status);
		hci_conn_del(sco);
	}

	hci_dev_unlock(hdev);
}