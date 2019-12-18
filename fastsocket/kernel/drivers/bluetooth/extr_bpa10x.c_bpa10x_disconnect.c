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
struct bpa10x_data {int /*<<< orphan*/  hdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct usb_interface*) ; 
 int /*<<< orphan*/  hci_free_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hci_unregister_dev (int /*<<< orphan*/ ) ; 
 struct bpa10x_data* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bpa10x_disconnect(struct usb_interface *intf)
{
	struct bpa10x_data *data = usb_get_intfdata(intf);

	BT_DBG("intf %p", intf);

	if (!data)
		return;

	usb_set_intfdata(intf, NULL);

	hci_unregister_dev(data->hdev);

	hci_free_dev(data->hdev);
}