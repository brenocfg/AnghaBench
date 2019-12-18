#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_class; } ;
struct inquiry_entry {TYPE_1__ data; } ;
struct hci_ev_conn_request {int /*<<< orphan*/  bdaddr; int /*<<< orphan*/  link_type; int /*<<< orphan*/  dev_class; } ;
struct hci_dev {int link_mode; int voice_setting; int /*<<< orphan*/  name; } ;
struct hci_cp_reject_conn_req {int role; int retrans_effort; int reason; int /*<<< orphan*/  bdaddr; void* content_format; void* max_latency; void* rx_bandwidth; void* tx_bandwidth; void* pkt_type; } ;
struct hci_cp_accept_sync_conn_req {int role; int retrans_effort; int reason; int /*<<< orphan*/  bdaddr; void* content_format; void* max_latency; void* rx_bandwidth; void* tx_bandwidth; void* pkt_type; } ;
struct hci_cp_accept_conn_req {int role; int retrans_effort; int reason; int /*<<< orphan*/  bdaddr; void* content_format; void* max_latency; void* rx_bandwidth; void* tx_bandwidth; void* pkt_type; } ;
struct hci_conn {int pkt_type; int /*<<< orphan*/  state; int /*<<< orphan*/  dev_class; } ;
typedef  int /*<<< orphan*/  cp ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_LINK ; 
 int /*<<< orphan*/  BT_CONNECT ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BT_ERR (char*) ; 
 int HCI_LM_ACCEPT ; 
 int HCI_LM_MASTER ; 
 int /*<<< orphan*/  HCI_OP_ACCEPT_CONN_REQ ; 
 int /*<<< orphan*/  HCI_OP_ACCEPT_SYNC_CONN_REQ ; 
 int /*<<< orphan*/  HCI_OP_REJECT_CONN_REQ ; 
 int /*<<< orphan*/  bacpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batostr (int /*<<< orphan*/ *) ; 
 void* cpu_to_le16 (int) ; 
 void* cpu_to_le32 (int) ; 
 struct hci_conn* hci_conn_add (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct hci_conn* hci_conn_hash_lookup_ba (struct hci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hci_dev_lock (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_dev_unlock (struct hci_dev*) ; 
 struct inquiry_entry* hci_inquiry_cache_lookup (struct hci_dev*,int /*<<< orphan*/ *) ; 
 int hci_proto_connect_ind (struct hci_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_send_cmd (struct hci_dev*,int /*<<< orphan*/ ,int,struct hci_cp_reject_conn_req*) ; 
 int /*<<< orphan*/  lmp_esco_capable (struct hci_dev*) ; 
 scalar_t__ lmp_rswitch_capable (struct hci_dev*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void hci_conn_request_evt(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_ev_conn_request *ev = (void *) skb->data;
	int mask = hdev->link_mode;

	BT_DBG("%s bdaddr %s type 0x%x", hdev->name,
					batostr(&ev->bdaddr), ev->link_type);

	mask |= hci_proto_connect_ind(hdev, &ev->bdaddr, ev->link_type);

	if (mask & HCI_LM_ACCEPT) {
		/* Connection accepted */
		struct inquiry_entry *ie;
		struct hci_conn *conn;

		hci_dev_lock(hdev);

		if ((ie = hci_inquiry_cache_lookup(hdev, &ev->bdaddr)))
			memcpy(ie->data.dev_class, ev->dev_class, 3);

		conn = hci_conn_hash_lookup_ba(hdev, ev->link_type, &ev->bdaddr);
		if (!conn) {
			if (!(conn = hci_conn_add(hdev, ev->link_type, &ev->bdaddr))) {
				BT_ERR("No memmory for new connection");
				hci_dev_unlock(hdev);
				return;
			}
		}

		memcpy(conn->dev_class, ev->dev_class, 3);
		conn->state = BT_CONNECT;

		hci_dev_unlock(hdev);

		if (ev->link_type == ACL_LINK || !lmp_esco_capable(hdev)) {
			struct hci_cp_accept_conn_req cp;

			bacpy(&cp.bdaddr, &ev->bdaddr);

			if (lmp_rswitch_capable(hdev) && (mask & HCI_LM_MASTER))
				cp.role = 0x00; /* Become master */
			else
				cp.role = 0x01; /* Remain slave */

			hci_send_cmd(hdev, HCI_OP_ACCEPT_CONN_REQ,
							sizeof(cp), &cp);
		} else {
			struct hci_cp_accept_sync_conn_req cp;

			bacpy(&cp.bdaddr, &ev->bdaddr);
			cp.pkt_type = cpu_to_le16(conn->pkt_type);

			cp.tx_bandwidth   = cpu_to_le32(0x00001f40);
			cp.rx_bandwidth   = cpu_to_le32(0x00001f40);
			cp.max_latency    = cpu_to_le16(0xffff);
			cp.content_format = cpu_to_le16(hdev->voice_setting);
			cp.retrans_effort = 0xff;

			hci_send_cmd(hdev, HCI_OP_ACCEPT_SYNC_CONN_REQ,
							sizeof(cp), &cp);
		}
	} else {
		/* Connection rejected */
		struct hci_cp_reject_conn_req cp;

		bacpy(&cp.bdaddr, &ev->bdaddr);
		cp.reason = 0x0f;
		hci_send_cmd(hdev, HCI_OP_REJECT_CONN_REQ, sizeof(cp), &cp);
	}
}