#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hci_dev {int /*<<< orphan*/  flags; int /*<<< orphan*/  name; struct btusb_data* driver_data; } ;
struct btusb_data {TYPE_1__* intf; int /*<<< orphan*/  flags; int /*<<< orphan*/  intr_anchor; } ;
struct TYPE_3__ {int needs_remote_wakeup; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTUSB_BULK_RUNNING ; 
 int /*<<< orphan*/  BTUSB_INTR_RUNNING ; 
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HCI_RUNNING ; 
 int btusb_submit_bulk_urb (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int btusb_submit_intr_urb (struct hci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int usb_autopm_get_interface (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_autopm_put_interface (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_kill_anchored_urbs (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btusb_open(struct hci_dev *hdev)
{
	struct btusb_data *data = hdev->driver_data;
	int err;

	BT_DBG("%s", hdev->name);

	err = usb_autopm_get_interface(data->intf);
	if (err < 0)
		return err;

	data->intf->needs_remote_wakeup = 1;

	if (test_and_set_bit(HCI_RUNNING, &hdev->flags))
		goto done;

	if (test_and_set_bit(BTUSB_INTR_RUNNING, &data->flags))
		goto done;

	err = btusb_submit_intr_urb(hdev, GFP_KERNEL);
	if (err < 0)
		goto failed;

	err = btusb_submit_bulk_urb(hdev, GFP_KERNEL);
	if (err < 0) {
		usb_kill_anchored_urbs(&data->intr_anchor);
		goto failed;
	}

	set_bit(BTUSB_BULK_RUNNING, &data->flags);
	btusb_submit_bulk_urb(hdev, GFP_KERNEL);

done:
	usb_autopm_put_interface(data->intf);
	return 0;

failed:
	clear_bit(BTUSB_INTR_RUNNING, &data->flags);
	clear_bit(HCI_RUNNING, &hdev->flags);
	usb_autopm_put_interface(data->intf);
	return err;
}