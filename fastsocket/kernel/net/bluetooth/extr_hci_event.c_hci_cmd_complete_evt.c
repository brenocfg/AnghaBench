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
struct hci_ev_cmd_complete {scalar_t__ ncmd; int /*<<< orphan*/  opcode; } ;
struct hci_dev {int /*<<< orphan*/  cmd_q; int /*<<< orphan*/  cmd_cnt; int /*<<< orphan*/  name; } ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int) ; 
#define  HCI_OP_EXIT_PERIODIC_INQ 153 
#define  HCI_OP_HOST_BUFFER_SIZE 152 
#define  HCI_OP_INQUIRY_CANCEL 151 
#define  HCI_OP_READ_BD_ADDR 150 
#define  HCI_OP_READ_BUFFER_SIZE 149 
#define  HCI_OP_READ_CLASS_OF_DEV 148 
#define  HCI_OP_READ_DEF_LINK_POLICY 147 
#define  HCI_OP_READ_LINK_POLICY 146 
#define  HCI_OP_READ_LOCAL_COMMANDS 145 
#define  HCI_OP_READ_LOCAL_FEATURES 144 
#define  HCI_OP_READ_LOCAL_NAME 143 
#define  HCI_OP_READ_LOCAL_VERSION 142 
#define  HCI_OP_READ_SSP_MODE 141 
#define  HCI_OP_READ_VOICE_SETTING 140 
#define  HCI_OP_REMOTE_NAME_REQ_CANCEL 139 
#define  HCI_OP_RESET 138 
#define  HCI_OP_ROLE_DISCOVERY 137 
#define  HCI_OP_WRITE_AUTH_ENABLE 136 
#define  HCI_OP_WRITE_CLASS_OF_DEV 135 
#define  HCI_OP_WRITE_DEF_LINK_POLICY 134 
#define  HCI_OP_WRITE_ENCRYPT_MODE 133 
#define  HCI_OP_WRITE_LINK_POLICY 132 
#define  HCI_OP_WRITE_LOCAL_NAME 131 
#define  HCI_OP_WRITE_SCAN_ENABLE 130 
#define  HCI_OP_WRITE_SSP_MODE 129 
#define  HCI_OP_WRITE_VOICE_SETTING 128 
 int __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hci_cc_exit_periodic_inq (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_host_buffer_size (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_inquiry_cancel (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_bd_addr (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_buffer_size (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_class_of_dev (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_def_link_policy (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_link_policy (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_local_commands (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_local_features (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_local_name (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_local_version (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_ssp_mode (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_read_voice_setting (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_remote_name_req_cancel (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_reset (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_role_discovery (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_write_auth_enable (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_write_class_of_dev (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_write_def_link_policy (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_write_encrypt_mode (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_write_link_policy (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_write_local_name (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_write_scan_enable (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_write_ssp_mode (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cc_write_voice_setting (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_sched_cmd (struct hci_dev*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void hci_cmd_complete_evt(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_ev_cmd_complete *ev = (void *) skb->data;
	__u16 opcode;

	skb_pull(skb, sizeof(*ev));

	opcode = __le16_to_cpu(ev->opcode);

	switch (opcode) {
	case HCI_OP_INQUIRY_CANCEL:
		hci_cc_inquiry_cancel(hdev, skb);
		break;

	case HCI_OP_EXIT_PERIODIC_INQ:
		hci_cc_exit_periodic_inq(hdev, skb);
		break;

	case HCI_OP_REMOTE_NAME_REQ_CANCEL:
		hci_cc_remote_name_req_cancel(hdev, skb);
		break;

	case HCI_OP_ROLE_DISCOVERY:
		hci_cc_role_discovery(hdev, skb);
		break;

	case HCI_OP_READ_LINK_POLICY:
		hci_cc_read_link_policy(hdev, skb);
		break;

	case HCI_OP_WRITE_LINK_POLICY:
		hci_cc_write_link_policy(hdev, skb);
		break;

	case HCI_OP_READ_DEF_LINK_POLICY:
		hci_cc_read_def_link_policy(hdev, skb);
		break;

	case HCI_OP_WRITE_DEF_LINK_POLICY:
		hci_cc_write_def_link_policy(hdev, skb);
		break;

	case HCI_OP_RESET:
		hci_cc_reset(hdev, skb);
		break;

	case HCI_OP_WRITE_LOCAL_NAME:
		hci_cc_write_local_name(hdev, skb);
		break;

	case HCI_OP_READ_LOCAL_NAME:
		hci_cc_read_local_name(hdev, skb);
		break;

	case HCI_OP_WRITE_AUTH_ENABLE:
		hci_cc_write_auth_enable(hdev, skb);
		break;

	case HCI_OP_WRITE_ENCRYPT_MODE:
		hci_cc_write_encrypt_mode(hdev, skb);
		break;

	case HCI_OP_WRITE_SCAN_ENABLE:
		hci_cc_write_scan_enable(hdev, skb);
		break;

	case HCI_OP_READ_CLASS_OF_DEV:
		hci_cc_read_class_of_dev(hdev, skb);
		break;

	case HCI_OP_WRITE_CLASS_OF_DEV:
		hci_cc_write_class_of_dev(hdev, skb);
		break;

	case HCI_OP_READ_VOICE_SETTING:
		hci_cc_read_voice_setting(hdev, skb);
		break;

	case HCI_OP_WRITE_VOICE_SETTING:
		hci_cc_write_voice_setting(hdev, skb);
		break;

	case HCI_OP_HOST_BUFFER_SIZE:
		hci_cc_host_buffer_size(hdev, skb);
		break;

	case HCI_OP_READ_SSP_MODE:
		hci_cc_read_ssp_mode(hdev, skb);
		break;

	case HCI_OP_WRITE_SSP_MODE:
		hci_cc_write_ssp_mode(hdev, skb);
		break;

	case HCI_OP_READ_LOCAL_VERSION:
		hci_cc_read_local_version(hdev, skb);
		break;

	case HCI_OP_READ_LOCAL_COMMANDS:
		hci_cc_read_local_commands(hdev, skb);
		break;

	case HCI_OP_READ_LOCAL_FEATURES:
		hci_cc_read_local_features(hdev, skb);
		break;

	case HCI_OP_READ_BUFFER_SIZE:
		hci_cc_read_buffer_size(hdev, skb);
		break;

	case HCI_OP_READ_BD_ADDR:
		hci_cc_read_bd_addr(hdev, skb);
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