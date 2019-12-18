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
struct smsusb_device_t {scalar_t__ coredev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct smsusb_device_t*) ; 
 int /*<<< orphan*/  sms_info (char*,struct smsusb_device_t*) ; 
 int /*<<< orphan*/  smscore_unregister_device (scalar_t__) ; 
 int /*<<< orphan*/  smsusb_stop_streaming (struct smsusb_device_t*) ; 
 struct smsusb_device_t* usb_get_intfdata (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void smsusb_term_device(struct usb_interface *intf)
{
	struct smsusb_device_t *dev = usb_get_intfdata(intf);

	if (dev) {
		smsusb_stop_streaming(dev);

		/* unregister from smscore */
		if (dev->coredev)
			smscore_unregister_device(dev->coredev);

		kfree(dev);

		sms_info("device %p destroyed", dev);
	}

	usb_set_intfdata(intf, NULL);
}