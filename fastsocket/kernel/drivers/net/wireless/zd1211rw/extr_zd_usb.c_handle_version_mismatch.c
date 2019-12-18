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
typedef  int /*<<< orphan*/  u16 ;
struct zd_usb {int dummy; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct firmware {scalar_t__ size; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  fw_name ;

/* Variables and functions */
 int E2P_BOOT_CODE_OFFSET ; 
 scalar_t__ E2P_START ; 
 scalar_t__ FW_START ; 
 int /*<<< orphan*/  REBOOT ; 
 int /*<<< orphan*/  get_fw_name (struct zd_usb*,char*,int,char*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_fw_file (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int upload_code (struct usb_device*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 struct usb_device* zd_usb_to_usbdev (struct zd_usb*) ; 

__attribute__((used)) static int handle_version_mismatch(struct zd_usb *usb,
	const struct firmware *ub_fw)
{
	struct usb_device *udev = zd_usb_to_usbdev(usb);
	const struct firmware *ur_fw = NULL;
	int offset;
	int r = 0;
	char fw_name[128];

	r = request_fw_file(&ur_fw,
		get_fw_name(usb, fw_name, sizeof(fw_name), "ur"),
		&udev->dev);
	if (r)
		goto error;

	r = upload_code(udev, ur_fw->data, ur_fw->size, FW_START, REBOOT);
	if (r)
		goto error;

	offset = (E2P_BOOT_CODE_OFFSET * sizeof(u16));
	r = upload_code(udev, ub_fw->data + offset, ub_fw->size - offset,
		E2P_START + E2P_BOOT_CODE_OFFSET, REBOOT);

	/* At this point, the vendor driver downloads the whole firmware
	 * image, hacks around with version IDs, and uploads it again,
	 * completely overwriting the boot code. We do not do this here as
	 * it is not required on any tested devices, and it is suspected to
	 * cause problems. */
error:
	release_firmware(ur_fw);
	return r;
}