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
typedef  int /*<<< orphan*/  u8 ;
struct usb_gadget {int dummy; } ;
struct usb_config_descriptor {int /*<<< orphan*/  bDescriptorType; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  USB_BUFSIZ ; 
 int /*<<< orphan*/  config_desc ; 
 int /*<<< orphan*/  gmidi_function ; 
 int usb_gadget_config_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_buf(struct usb_gadget *gadget,
		u8 *buf, u8 type, unsigned index)
{
	int len;

	/* only one configuration */
	if (index != 0) {
		return -EINVAL;
	}
	len = usb_gadget_config_buf(&config_desc,
			buf, USB_BUFSIZ, gmidi_function);
	if (len < 0) {
		return len;
	}
	((struct usb_config_descriptor *)buf)->bDescriptorType = type;
	return len;
}