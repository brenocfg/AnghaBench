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
struct hci_ev_cmd_status {scalar_t__ ncmd; int /*<<< orphan*/  status; int /*<<< orphan*/  opcode; } ;
struct hci_dev {int /*<<< orphan*/  cmd_q; int /*<<< orphan*/  cmd_cnt; int /*<<< orphan*/  name; } ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int) ; 
#define  HCI_OP_ADD_SCO 138 
#define  HCI_OP_AUTH_REQUESTED 137 
#define  HCI_OP_CREATE_CONN 136 
#define  HCI_OP_EXIT_SNIFF_MODE 135 
#define  HCI_OP_INQUIRY 134 
#define  HCI_OP_READ_REMOTE_EXT_FEATURES 133 
#define  HCI_OP_READ_REMOTE_FEATURES 132 
#define  HCI_OP_REMOTE_NAME_REQ 131 
#define  HCI_OP_SETUP_SYNC_CONN 130 
#define  HCI_OP_SET_CONN_ENCRYPT 129 
#define  HCI_OP_SNIFF_MODE 128 
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hci_cs_add_sco (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_cs_auth_requested (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_cs_create_conn (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_cs_exit_sniff_mode (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_cs_inquiry (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_cs_read_remote_ext_features (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_cs_read_remote_features (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_cs_remote_name_req (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_cs_set_conn_encrypt (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_cs_setup_sync_conn (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_cs_sniff_mode (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_sched_cmd (struct hci_dev*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void hci_cmd_status_evt(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_ev_cmd_status *ev = (void *) skb->data;
	__u16 opcode;

	skb_pull(skb, sizeof(*ev));

	opcode = __le16_to_cpu(ev->opcode);

	switch (opcode) {
	case HCI_OP_INQUIRY:
		hci_cs_inquiry(hdev, ev->status);
		break;

	case HCI_OP_CREATE_CONN:
		hci_cs_create_conn(hdev, ev->status);
		break;

	case HCI_OP_ADD_SCO:
		hci_cs_add_sco(hdev, ev->status);
		break;

	case HCI_OP_AUTH_REQUESTED:
		hci_cs_auth_requested(hdev, ev->status);
		break;

	case HCI_OP_SET_CONN_ENCRYPT:
		hci_cs_set_conn_encrypt(hdev, ev->status);
		break;

	case HCI_OP_REMOTE_NAME_REQ:
		hci_cs_remote_name_req(hdev, ev->status);
		break;

	case HCI_OP_READ_REMOTE_FEATURES:
		hci_cs_read_remote_features(hdev, ev->status);
		break;

	case HCI_OP_READ_REMOTE_EXT_FEATURES:
		hci_cs_read_remote_ext_features(hdev, ev->status);
		break;

	case HCI_OP_SETUP_SYNC_CONN:
		hci_cs_setup_sync_conn(hdev, ev->status);
		break;

	case HCI_OP_SNIFF_MODE:
		hci_cs_sniff_mode(hdev, ev->status);
		break;

	case HCI_OP_EXIT_SNIFF_MODE:
		hci_cs_exit_sniff_mode(hdev, ev->status);
		break;

	default:
		BT_DBG("%s opcode 0x%x", hdev->name, opcode);
		break;
	}

	if (ev->ncmd) {
		atomic_set(&hdev->cmd_cnt, 1);
		if (!skb_queue_empty(&hdev->cmd_q))
			hci_sched_cmd(hdev);
	}
}