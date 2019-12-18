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
typedef  unsigned long __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  HCI_OP_WRITE_SCAN_ENABLE ; 
 int /*<<< orphan*/  hci_send_cmd (struct hci_dev*,int /*<<< orphan*/ ,int,unsigned long*) ; 

__attribute__((used)) static void hci_scan_req(struct hci_dev *hdev, unsigned long opt)
{
	__u8 scan = opt;

	BT_DBG("%s %x", hdev->name, scan);

	/* Inquiry and Page scans */
	hci_send_cmd(hdev, HCI_OP_WRITE_SCAN_ENABLE, 1, &scan);
}