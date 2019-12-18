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
struct usb_device_id {scalar_t__ driver_info; } ;
struct usb_device {int reset_resume; int /*<<< orphan*/  dev; } ;
struct hif_device_usb {int /*<<< orphan*/  fw_name; struct usb_device* udev; int /*<<< orphan*/  fw_done; struct usb_device_id const* usb_device_id; struct usb_interface* interface; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FIRMWARE_AR7010_1_1 ; 
 int /*<<< orphan*/  FIRMWARE_AR9271 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_AR7010_DEVICE (scalar_t__) ; 
 scalar_t__ STORAGE_DEVICE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  ath9k_hif_usb_firmware_cb ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kfree (struct hif_device_usb*) ; 
 struct hif_device_usb* kzalloc (int,int /*<<< orphan*/ ) ; 
 int request_firmware_nowait (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct hif_device_usb*,int /*<<< orphan*/ ) ; 
 int send_eject_command (struct usb_interface*) ; 
 int /*<<< orphan*/  usb_get_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct hif_device_usb*) ; 

__attribute__((used)) static int ath9k_hif_usb_probe(struct usb_interface *interface,
			       const struct usb_device_id *id)
{
	struct usb_device *udev = interface_to_usbdev(interface);
	struct hif_device_usb *hif_dev;
	int ret = 0;

	if (id->driver_info == STORAGE_DEVICE)
		return send_eject_command(interface);

	hif_dev = kzalloc(sizeof(struct hif_device_usb), GFP_KERNEL);
	if (!hif_dev) {
		ret = -ENOMEM;
		goto err_alloc;
	}

	usb_get_dev(udev);

	hif_dev->udev = udev;
	hif_dev->interface = interface;
	hif_dev->usb_device_id = id;
#ifdef CONFIG_PM
	udev->reset_resume = 1;
#endif
	usb_set_intfdata(interface, hif_dev);

	init_completion(&hif_dev->fw_done);

	/* Find out which firmware to load */

	if (IS_AR7010_DEVICE(id->driver_info))
		hif_dev->fw_name = FIRMWARE_AR7010_1_1;
	else
		hif_dev->fw_name = FIRMWARE_AR9271;

	ret = request_firmware_nowait(THIS_MODULE, true, hif_dev->fw_name,
				      &hif_dev->udev->dev, GFP_KERNEL,
				      hif_dev, ath9k_hif_usb_firmware_cb);
	if (ret) {
		dev_err(&hif_dev->udev->dev,
			"ath9k_htc: Async request for firmware %s failed\n",
			hif_dev->fw_name);
		goto err_fw_req;
	}

	dev_info(&hif_dev->udev->dev, "ath9k_htc: Firmware %s requested\n",
		 hif_dev->fw_name);

	return 0;

err_fw_req:
	usb_set_intfdata(interface, NULL);
	kfree(hif_dev);
	usb_put_dev(udev);
err_alloc:
	return ret;
}