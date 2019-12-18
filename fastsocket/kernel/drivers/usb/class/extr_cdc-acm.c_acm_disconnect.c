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
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device {int dummy; } ;
struct tty_struct {int dummy; } ;
struct TYPE_2__ {scalar_t__ count; } ;
struct acm {TYPE_1__ port; struct usb_interface* control; struct usb_interface* data; int /*<<< orphan*/  combined_interfaces; int /*<<< orphan*/  ctrl_dma; int /*<<< orphan*/  ctrl_buffer; int /*<<< orphan*/  ctrlsize; int /*<<< orphan*/ * dev; scalar_t__ country_codes; } ;

/* Variables and functions */
 int /*<<< orphan*/  acm_driver ; 
 int /*<<< orphan*/  acm_read_buffers_free (struct acm*) ; 
 int /*<<< orphan*/  acm_tty_unregister (struct acm*) ; 
 int /*<<< orphan*/  acm_write_buffers_free (struct acm*) ; 
 int /*<<< orphan*/  dev_attr_bmCapabilities ; 
 int /*<<< orphan*/  dev_attr_iCountryCodeRelDate ; 
 int /*<<< orphan*/  dev_attr_wCountryCodes ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  open_mutex ; 
 int /*<<< orphan*/  stop_data_traffic (struct acm*) ; 
 int /*<<< orphan*/  tty_hangup (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 
 struct tty_struct* tty_port_tty_get (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_buffer_free (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_driver_release_interface (int /*<<< orphan*/ *,struct usb_interface*) ; 
 struct acm* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acm_disconnect(struct usb_interface *intf)
{
	struct acm *acm = usb_get_intfdata(intf);
	struct usb_device *usb_dev = interface_to_usbdev(intf);
	struct tty_struct *tty;

	/* sibling interface is already cleaning up */
	if (!acm)
		return;

	mutex_lock(&open_mutex);
	if (acm->country_codes) {
		device_remove_file(&acm->control->dev,
				&dev_attr_wCountryCodes);
		device_remove_file(&acm->control->dev,
				&dev_attr_iCountryCodeRelDate);
	}
	device_remove_file(&acm->control->dev, &dev_attr_bmCapabilities);
	acm->dev = NULL;
	usb_set_intfdata(acm->control, NULL);
	usb_set_intfdata(acm->data, NULL);

	stop_data_traffic(acm);

	acm_write_buffers_free(acm);
	usb_buffer_free(usb_dev, acm->ctrlsize, acm->ctrl_buffer,
								acm->ctrl_dma);
	acm_read_buffers_free(acm);

	if (!acm->combined_interfaces)
		usb_driver_release_interface(&acm_driver, intf == acm->control ?
					acm->data : acm->control);

	if (acm->port.count == 0) {
		acm_tty_unregister(acm);
		mutex_unlock(&open_mutex);
		return;
	}

	mutex_unlock(&open_mutex);
	tty = tty_port_tty_get(&acm->port);
	if (tty) {
		tty_hangup(tty);
		tty_kref_put(tty);
	}
}