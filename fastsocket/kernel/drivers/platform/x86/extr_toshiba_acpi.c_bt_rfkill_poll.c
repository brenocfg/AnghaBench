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
struct rfkill {int dummy; } ;

/* Variables and functions */
 scalar_t__ HCI_SUCCESS ; 
 int /*<<< orphan*/  bt_rfkill_set_block (void*,int) ; 
 scalar_t__ hci_get_radio_state (int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ rfkill_set_hw_state (struct rfkill*,int) ; 

__attribute__((used)) static void bt_rfkill_poll(struct rfkill *rfkill, void *data)
{
	bool new_rfk_state;
	bool value;
	u32 hci_result;
	struct toshiba_acpi_dev *dev = data;

	mutex_lock(&dev->mutex);

	hci_result = hci_get_radio_state(&value);
	if (hci_result != HCI_SUCCESS) {
		/* Can't do anything useful */
		mutex_unlock(&dev->mutex);
		return;
	}

	new_rfk_state = value;

	mutex_unlock(&dev->mutex);

	if (rfkill_set_hw_state(rfkill, !new_rfk_state))
		bt_rfkill_set_block(data, true);
}