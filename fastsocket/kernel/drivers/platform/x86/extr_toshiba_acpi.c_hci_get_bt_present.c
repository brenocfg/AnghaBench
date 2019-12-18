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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ HCI_SUCCESS ; 
 int /*<<< orphan*/  HCI_WIRELESS ; 
 scalar_t__ HCI_WIRELESS_BT_PRESENT ; 
 int /*<<< orphan*/  hci_read2 (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static u32 hci_get_bt_present(bool *present)
{
	u32 hci_result;
	u32 value, value2;

	value = 0;
	value2 = 0;
	hci_read2(HCI_WIRELESS, &value, &value2, &hci_result);
	if (hci_result == HCI_SUCCESS)
		*present = (value & HCI_WIRELESS_BT_PRESENT) ? true : false;

	return hci_result;
}