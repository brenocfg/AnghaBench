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
struct toshiba_acpi_dev {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ HCI_SUCCESS ; 
 int /*<<< orphan*/  HCI_WIRELESS ; 
 int /*<<< orphan*/  HCI_WIRELESS_BT_ATTACH ; 
 int /*<<< orphan*/  HCI_WIRELESS_BT_POWER ; 
 scalar_t__ hci_get_radio_state (int*) ; 
 int /*<<< orphan*/  hci_write2 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bt_rfkill_set_block(void *data, bool blocked)
{
	struct toshiba_acpi_dev *dev = data;
	u32 result1, result2;
	u32 value;
	int err;
	bool radio_state;

	value = (blocked == false);

	mutex_lock(&dev->mutex);
	if (hci_get_radio_state(&radio_state) != HCI_SUCCESS) {
		err = -EBUSY;
		goto out;
	}

	if (!radio_state) {
		err = 0;
		goto out;
	}

	hci_write2(HCI_WIRELESS, value, HCI_WIRELESS_BT_POWER, &result1);
	hci_write2(HCI_WIRELESS, value, HCI_WIRELESS_BT_ATTACH, &result2);

	if (result1 != HCI_SUCCESS || result2 != HCI_SUCCESS)
		err = -EBUSY;
	else
		err = 0;
 out:
	mutex_unlock(&dev->mutex);
	return err;
}