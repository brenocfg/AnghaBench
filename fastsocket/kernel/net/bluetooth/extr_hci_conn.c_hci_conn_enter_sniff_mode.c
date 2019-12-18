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
struct hci_dev {scalar_t__ mode; int link_policy; int handle; int sniff_max_interval; int sniff_min_interval; int /*<<< orphan*/  pend; int /*<<< orphan*/  flags; struct hci_dev* hdev; } ;
struct hci_cp_sniff_subrate {void* timeout; void* attempt; void* min_interval; void* max_interval; void* handle; void* min_local_timeout; void* min_remote_timeout; void* max_latency; } ;
struct hci_cp_sniff_mode {void* timeout; void* attempt; void* min_interval; void* max_interval; void* handle; void* min_local_timeout; void* min_remote_timeout; void* max_latency; } ;
struct hci_conn {scalar_t__ mode; int link_policy; int handle; int sniff_max_interval; int sniff_min_interval; int /*<<< orphan*/  pend; int /*<<< orphan*/  flags; struct hci_conn* hdev; } ;
typedef  int /*<<< orphan*/  cp ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct hci_dev*,scalar_t__) ; 
 scalar_t__ HCI_CM_ACTIVE ; 
 int /*<<< orphan*/  HCI_CONN_MODE_CHANGE_PEND ; 
 int HCI_LP_SNIFF ; 
 int /*<<< orphan*/  HCI_OP_SNIFF_MODE ; 
 int /*<<< orphan*/  HCI_OP_SNIFF_SUBRATE ; 
 int /*<<< orphan*/  HCI_RAW ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  hci_send_cmd (struct hci_dev*,int /*<<< orphan*/ ,int,struct hci_cp_sniff_subrate*) ; 
 int /*<<< orphan*/  lmp_sniff_capable (struct hci_dev*) ; 
 scalar_t__ lmp_sniffsubr_capable (struct hci_dev*) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void hci_conn_enter_sniff_mode(struct hci_conn *conn)
{
	struct hci_dev *hdev = conn->hdev;

	BT_DBG("conn %p mode %d", conn, conn->mode);

	if (test_bit(HCI_RAW, &hdev->flags))
		return;

	if (!lmp_sniff_capable(hdev) || !lmp_sniff_capable(conn))
		return;

	if (conn->mode != HCI_CM_ACTIVE || !(conn->link_policy & HCI_LP_SNIFF))
		return;

	if (lmp_sniffsubr_capable(hdev) && lmp_sniffsubr_capable(conn)) {
		struct hci_cp_sniff_subrate cp;
		cp.handle             = cpu_to_le16(conn->handle);
		cp.max_latency        = cpu_to_le16(0);
		cp.min_remote_timeout = cpu_to_le16(0);
		cp.min_local_timeout  = cpu_to_le16(0);
		hci_send_cmd(hdev, HCI_OP_SNIFF_SUBRATE, sizeof(cp), &cp);
	}

	if (!test_and_set_bit(HCI_CONN_MODE_CHANGE_PEND, &conn->pend)) {
		struct hci_cp_sniff_mode cp;
		cp.handle       = cpu_to_le16(conn->handle);
		cp.max_interval = cpu_to_le16(hdev->sniff_max_interval);
		cp.min_interval = cpu_to_le16(hdev->sniff_min_interval);
		cp.attempt      = cpu_to_le16(4);
		cp.timeout      = cpu_to_le16(1);
		hci_send_cmd(hdev, HCI_OP_SNIFF_MODE, sizeof(cp), &cp);
	}
}