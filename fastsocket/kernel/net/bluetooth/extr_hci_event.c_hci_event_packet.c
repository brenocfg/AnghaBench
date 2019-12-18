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
struct hci_event_hdr {int evt; } ;
struct TYPE_2__ {int /*<<< orphan*/  evt_rx; } ;
struct hci_dev {TYPE_1__ stat; int /*<<< orphan*/  name; } ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HCI_EVENT_HDR_SIZE ; 
#define  HCI_EV_AUTH_COMPLETE 159 
#define  HCI_EV_CHANGE_LINK_KEY_COMPLETE 158 
#define  HCI_EV_CLOCK_OFFSET 157 
#define  HCI_EV_CMD_COMPLETE 156 
#define  HCI_EV_CMD_STATUS 155 
#define  HCI_EV_CONN_COMPLETE 154 
#define  HCI_EV_CONN_REQUEST 153 
#define  HCI_EV_DISCONN_COMPLETE 152 
#define  HCI_EV_ENCRYPT_CHANGE 151 
#define  HCI_EV_EXTENDED_INQUIRY_RESULT 150 
#define  HCI_EV_INQUIRY_COMPLETE 149 
#define  HCI_EV_INQUIRY_RESULT 148 
#define  HCI_EV_INQUIRY_RESULT_WITH_RSSI 147 
#define  HCI_EV_IO_CAPA_REQUEST 146 
#define  HCI_EV_LINK_KEY_NOTIFY 145 
#define  HCI_EV_LINK_KEY_REQ 144 
#define  HCI_EV_MODE_CHANGE 143 
#define  HCI_EV_NUM_COMP_PKTS 142 
#define  HCI_EV_PIN_CODE_REQ 141 
#define  HCI_EV_PKT_TYPE_CHANGE 140 
#define  HCI_EV_PSCAN_REP_MODE 139 
#define  HCI_EV_QOS_SETUP_COMPLETE 138 
#define  HCI_EV_REMOTE_EXT_FEATURES 137 
#define  HCI_EV_REMOTE_FEATURES 136 
#define  HCI_EV_REMOTE_HOST_FEATURES 135 
#define  HCI_EV_REMOTE_NAME 134 
#define  HCI_EV_REMOTE_VERSION 133 
#define  HCI_EV_ROLE_CHANGE 132 
#define  HCI_EV_SIMPLE_PAIR_COMPLETE 131 
#define  HCI_EV_SNIFF_SUBRATE 130 
#define  HCI_EV_SYNC_CONN_CHANGED 129 
#define  HCI_EV_SYNC_CONN_COMPLETE 128 
 int /*<<< orphan*/  hci_auth_complete_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_change_link_key_complete_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_clock_offset_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cmd_complete_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_cmd_status_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_conn_complete_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_conn_request_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_disconn_complete_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_encrypt_change_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_extended_inquiry_result_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_inquiry_complete_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_inquiry_result_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_inquiry_result_with_rssi_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_io_capa_request_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_link_key_notify_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_link_key_request_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_mode_change_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_num_comp_pkts_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_pin_code_request_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_pkt_type_change_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_pscan_rep_mode_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_qos_setup_complete_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_remote_ext_features_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_remote_features_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_remote_host_features_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_remote_name_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_remote_version_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_role_change_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_simple_pair_complete_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_sniff_subrate_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_sync_conn_changed_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  hci_sync_conn_complete_evt (struct hci_dev*,struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 

void hci_event_packet(struct hci_dev *hdev, struct sk_buff *skb)
{
	struct hci_event_hdr *hdr = (void *) skb->data;
	__u8 event = hdr->evt;

	skb_pull(skb, HCI_EVENT_HDR_SIZE);

	switch (event) {
	case HCI_EV_INQUIRY_COMPLETE:
		hci_inquiry_complete_evt(hdev, skb);
		break;

	case HCI_EV_INQUIRY_RESULT:
		hci_inquiry_result_evt(hdev, skb);
		break;

	case HCI_EV_CONN_COMPLETE:
		hci_conn_complete_evt(hdev, skb);
		break;

	case HCI_EV_CONN_REQUEST:
		hci_conn_request_evt(hdev, skb);
		break;

	case HCI_EV_DISCONN_COMPLETE:
		hci_disconn_complete_evt(hdev, skb);
		break;

	case HCI_EV_AUTH_COMPLETE:
		hci_auth_complete_evt(hdev, skb);
		break;

	case HCI_EV_REMOTE_NAME:
		hci_remote_name_evt(hdev, skb);
		break;

	case HCI_EV_ENCRYPT_CHANGE:
		hci_encrypt_change_evt(hdev, skb);
		break;

	case HCI_EV_CHANGE_LINK_KEY_COMPLETE:
		hci_change_link_key_complete_evt(hdev, skb);
		break;

	case HCI_EV_REMOTE_FEATURES:
		hci_remote_features_evt(hdev, skb);
		break;

	case HCI_EV_REMOTE_VERSION:
		hci_remote_version_evt(hdev, skb);
		break;

	case HCI_EV_QOS_SETUP_COMPLETE:
		hci_qos_setup_complete_evt(hdev, skb);
		break;

	case HCI_EV_CMD_COMPLETE:
		hci_cmd_complete_evt(hdev, skb);
		break;

	case HCI_EV_CMD_STATUS:
		hci_cmd_status_evt(hdev, skb);
		break;

	case HCI_EV_ROLE_CHANGE:
		hci_role_change_evt(hdev, skb);
		break;

	case HCI_EV_NUM_COMP_PKTS:
		hci_num_comp_pkts_evt(hdev, skb);
		break;

	case HCI_EV_MODE_CHANGE:
		hci_mode_change_evt(hdev, skb);
		break;

	case HCI_EV_PIN_CODE_REQ:
		hci_pin_code_request_evt(hdev, skb);
		break;

	case HCI_EV_LINK_KEY_REQ:
		hci_link_key_request_evt(hdev, skb);
		break;

	case HCI_EV_LINK_KEY_NOTIFY:
		hci_link_key_notify_evt(hdev, skb);
		break;

	case HCI_EV_CLOCK_OFFSET:
		hci_clock_offset_evt(hdev, skb);
		break;

	case HCI_EV_PKT_TYPE_CHANGE:
		hci_pkt_type_change_evt(hdev, skb);
		break;

	case HCI_EV_PSCAN_REP_MODE:
		hci_pscan_rep_mode_evt(hdev, skb);
		break;

	case HCI_EV_INQUIRY_RESULT_WITH_RSSI:
		hci_inquiry_result_with_rssi_evt(hdev, skb);
		break;

	case HCI_EV_REMOTE_EXT_FEATURES:
		hci_remote_ext_features_evt(hdev, skb);
		break;

	case HCI_EV_SYNC_CONN_COMPLETE:
		hci_sync_conn_complete_evt(hdev, skb);
		break;

	case HCI_EV_SYNC_CONN_CHANGED:
		hci_sync_conn_changed_evt(hdev, skb);
		break;

	case HCI_EV_SNIFF_SUBRATE:
		hci_sniff_subrate_evt(hdev, skb);
		break;

	case HCI_EV_EXTENDED_INQUIRY_RESULT:
		hci_extended_inquiry_result_evt(hdev, skb);
		break;

	case HCI_EV_IO_CAPA_REQUEST:
		hci_io_capa_request_evt(hdev, skb);
		break;

	case HCI_EV_SIMPLE_PAIR_COMPLETE:
		hci_simple_pair_complete_evt(hdev, skb);
		break;

	case HCI_EV_REMOTE_HOST_FEATURES:
		hci_remote_host_features_evt(hdev, skb);
		break;

	default:
		BT_DBG("%s event 0x%x", hdev->name, event);
		break;
	}

	kfree_skb(skb);
	hdev->stat.evt_rx++;
}