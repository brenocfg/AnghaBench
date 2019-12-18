#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct usb_otg_descriptor {int bmAttributes; } ;
struct usb_device {scalar_t__ parent; unsigned int portnum; int /*<<< orphan*/  dev; struct usb_bus* bus; TYPE_2__* config; int /*<<< orphan*/ * rawdescriptors; } ;
struct usb_bus {scalar_t__ root_hub; unsigned int otg_port; int b_hnp_enable; scalar_t__ is_b_host; } ;
struct TYPE_3__ {int /*<<< orphan*/  wTotalLength; } ;
struct TYPE_4__ {TYPE_1__ desc; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int /*<<< orphan*/  PMSG_SUSPEND ; 
 int /*<<< orphan*/  USB_CTRL_SET_TIMEOUT ; 
 int /*<<< orphan*/  USB_DEVICE_A_ALT_HNP_SUPPORT ; 
 int /*<<< orphan*/  USB_DEVICE_B_HNP_ENABLE ; 
 int /*<<< orphan*/  USB_DT_OTG ; 
 int USB_OTG_HNP ; 
 int /*<<< orphan*/  USB_REQ_SET_FEATURE ; 
 scalar_t__ __usb_get_extra_descriptor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  is_targeted (struct usb_device*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int usb_control_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usb_port_suspend (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (struct usb_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int usb_enumerate_device_otg(struct usb_device *udev)
{
	int err = 0;

#ifdef	CONFIG_USB_OTG
	/*
	 * OTG-aware devices on OTG-capable root hubs may be able to use SRP,
	 * to wake us after we've powered off VBUS; and HNP, switching roles
	 * "host" to "peripheral".  The OTG descriptor helps figure this out.
	 */
	if (!udev->bus->is_b_host
			&& udev->config
			&& udev->parent == udev->bus->root_hub) {
		struct usb_otg_descriptor	*desc = 0;
		struct usb_bus			*bus = udev->bus;

		/* descriptor may appear anywhere in config */
		if (__usb_get_extra_descriptor (udev->rawdescriptors[0],
					le16_to_cpu(udev->config[0].desc.wTotalLength),
					USB_DT_OTG, (void **) &desc) == 0) {
			if (desc->bmAttributes & USB_OTG_HNP) {
				unsigned		port1 = udev->portnum;

				dev_info(&udev->dev,
					"Dual-Role OTG device on %sHNP port\n",
					(port1 == bus->otg_port)
						? "" : "non-");

				/* enable HNP before suspend, it's simpler */
				if (port1 == bus->otg_port)
					bus->b_hnp_enable = 1;
				err = usb_control_msg(udev,
					usb_sndctrlpipe(udev, 0),
					USB_REQ_SET_FEATURE, 0,
					bus->b_hnp_enable
						? USB_DEVICE_B_HNP_ENABLE
						: USB_DEVICE_A_ALT_HNP_SUPPORT,
					0, NULL, 0, USB_CTRL_SET_TIMEOUT);
				if (err < 0) {
					/* OTG MESSAGE: report errors here,
					 * customize to match your product.
					 */
					dev_info(&udev->dev,
						"can't set HNP mode: %d\n",
						err);
					bus->b_hnp_enable = 0;
				}
			}
		}
	}

	if (!is_targeted(udev)) {

		/* Maybe it can talk to us, though we can't talk to it.
		 * (Includes HNP test device.)
		 */
		if (udev->bus->b_hnp_enable || udev->bus->is_b_host) {
			err = usb_port_suspend(udev, PMSG_SUSPEND);
			if (err < 0)
				dev_dbg(&udev->dev, "HNP fail, %d\n", err);
		}
		err = -ENOTSUPP;
		goto fail;
	}
fail:
#endif
	return err;
}