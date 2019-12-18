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
struct usb_interface {int dummy; } ;
struct hci_dev {int dummy; } ;
struct btusb_data {struct usb_interface* isoc; struct usb_interface* intf; struct hci_dev* hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct usb_interface*) ; 
 int /*<<< orphan*/  __hci_dev_hold (struct hci_dev*) ; 
 int /*<<< orphan*/  __hci_dev_put (struct hci_dev*) ; 
 int /*<<< orphan*/  btusb_driver ; 
 int /*<<< orphan*/  hci_free_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  hci_unregister_dev (struct hci_dev*) ; 
 int /*<<< orphan*/  usb_driver_release_interface (int /*<<< orphan*/ *,struct usb_interface*) ; 
 struct btusb_data* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btusb_disconnect(struct usb_interface *intf)
{
	struct btusb_data *data = usb_get_intfdata(intf);
	struct hci_dev *hdev;

	BT_DBG("intf %p", intf);

	if (!data)
		return;

	hdev = data->hdev;

	__hci_dev_hold(hdev);

	usb_set_intfdata(data->intf, NULL);

	if (data->isoc)
		usb_set_intfdata(data->isoc, NULL);

	hci_unregister_dev(hdev);

	if (intf == data->isoc)
		usb_driver_release_interface(&btusb_driver, data->intf);
	else if (data->isoc)
		usb_driver_release_interface(&btusb_driver, data->isoc);

	__hci_dev_put(hdev);

	hci_free_dev(hdev);
}