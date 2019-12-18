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
struct usbduxfastsub_s {struct usb_device* usbdev; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOARDNAME ; 
 int /*<<< orphan*/  comedi_usb_auto_config (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int firmwareUpload (struct usbduxfastsub_s*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 

__attribute__((used)) static void usbduxfast_firmware_request_complete_handler(const struct firmware
							 *fw, void *context)
{
	struct usbduxfastsub_s *usbduxfastsub_tmp = context;
	struct usb_device *usbdev = usbduxfastsub_tmp->usbdev;
	int ret;

	if (fw == NULL)
		return;

	/*
	 * we need to upload the firmware here because fw will be
	 * freed once we've left this function
	 */
	ret = firmwareUpload(usbduxfastsub_tmp, fw->data, fw->size);

	if (ret) {
		dev_err(&usbdev->dev,
			"Could not upload firmware (err=%d)\n", ret);
		goto out;
	}

	comedi_usb_auto_config(usbdev, BOARDNAME);
 out:
	release_firmware(fw);
}