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
typedef  int u16 ;
struct zd_usb {int dummy; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  int /*<<< orphan*/  fw_name ;

/* Variables and functions */
 int /*<<< orphan*/  E2P_DATA_OFFSET ; 
 int /*<<< orphan*/  FW_START ; 
 int /*<<< orphan*/  REBOOT ; 
 int /*<<< orphan*/  dev_dbg_f (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int get_bcdDevice (struct usb_device*) ; 
 int /*<<< orphan*/  get_fw_name (struct zd_usb*,char*,int,char*) ; 
 int get_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int handle_version_mismatch (struct zd_usb*,struct firmware const*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_fw_file (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int upload_code (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct usb_device* zd_usb_to_usbdev (struct zd_usb*) ; 

__attribute__((used)) static int upload_firmware(struct zd_usb *usb)
{
	int r;
	u16 fw_bcdDevice;
	u16 bcdDevice;
	struct usb_device *udev = zd_usb_to_usbdev(usb);
	const struct firmware *ub_fw = NULL;
	const struct firmware *uph_fw = NULL;
	char fw_name[128];

	bcdDevice = get_bcdDevice(udev);

	r = request_fw_file(&ub_fw,
		get_fw_name(usb, fw_name, sizeof(fw_name), "ub"),
		&udev->dev);
	if (r)
		goto error;

	fw_bcdDevice = get_word(ub_fw->data, E2P_DATA_OFFSET);

	if (fw_bcdDevice != bcdDevice) {
		dev_info(&udev->dev,
			"firmware version %#06x and device bootcode version "
			"%#06x differ\n", fw_bcdDevice, bcdDevice);
		if (bcdDevice <= 0x4313)
			dev_warn(&udev->dev, "device has old bootcode, please "
				"report success or failure\n");

		r = handle_version_mismatch(usb, ub_fw);
		if (r)
			goto error;
	} else {
		dev_dbg_f(&udev->dev,
			"firmware device id %#06x is equal to the "
			"actual device id\n", fw_bcdDevice);
	}


	r = request_fw_file(&uph_fw,
		get_fw_name(usb, fw_name, sizeof(fw_name), "uphr"),
		&udev->dev);
	if (r)
		goto error;

	r = upload_code(udev, uph_fw->data, uph_fw->size, FW_START, REBOOT);
	if (r) {
		dev_err(&udev->dev,
			"Could not upload firmware code uph. Error number %d\n",
			r);
	}

	/* FALL-THROUGH */
error:
	release_firmware(ub_fw);
	release_firmware(uph_fw);
	return r;
}