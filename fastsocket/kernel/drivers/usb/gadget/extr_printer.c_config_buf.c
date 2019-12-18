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
typedef  scalar_t__ u8 ;
struct usb_descriptor_header {int dummy; } ;
struct usb_config_descriptor {scalar_t__ bDescriptorType; } ;
typedef  enum usb_device_speed { ____Placeholder_usb_device_speed } usb_device_speed ;
struct TYPE_2__ {unsigned int bNumConfigurations; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  USB_DESC_BUFSIZE ; 
 scalar_t__ USB_DT_OTHER_SPEED_CONFIG ; 
 int USB_SPEED_HIGH ; 
 int /*<<< orphan*/  config_desc ; 
 TYPE_1__ device_desc ; 
 struct usb_descriptor_header** fs_printer_function ; 
 struct usb_descriptor_header** hs_printer_function ; 
 int usb_gadget_config_buf (int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,struct usb_descriptor_header const**) ; 

__attribute__((used)) static int
config_buf(enum usb_device_speed speed, u8 *buf, u8 type, unsigned index,
		int is_otg)
{
	int					len;
	const struct usb_descriptor_header	**function;
#ifdef CONFIG_USB_GADGET_DUALSPEED
	int					hs = (speed == USB_SPEED_HIGH);

	if (type == USB_DT_OTHER_SPEED_CONFIG)
		hs = !hs;

	if (hs) {
		function = hs_printer_function;
	} else {
		function = fs_printer_function;
	}
#else
	function = fs_printer_function;
#endif

	if (index >= device_desc.bNumConfigurations)
		return -EINVAL;

	/* for now, don't advertise srp-only devices */
	if (!is_otg)
		function++;

	len = usb_gadget_config_buf(&config_desc, buf, USB_DESC_BUFSIZE,
			function);
	if (len < 0)
		return len;
	((struct usb_config_descriptor *) buf)->bDescriptorType = type;
	return len;
}