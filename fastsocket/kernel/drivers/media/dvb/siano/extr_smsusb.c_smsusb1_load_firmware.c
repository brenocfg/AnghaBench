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
struct usb_device {int /*<<< orphan*/  dev; } ;
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int DEVICE_MODE_DVBT ; 
 int DEVICE_MODE_DVBT_BDA ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sms_err (char*,...) ; 
 char* sms_get_fw_name (int,int) ; 
 int /*<<< orphan*/  sms_info (char*,char*,int,...) ; 
 int /*<<< orphan*/  sms_warn (char*,char*,int) ; 
 char** smsusb1_fw_lkup ; 
 int usb_bulk_msg (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  usb_sndbulkpipe (struct usb_device*,int) ; 

__attribute__((used)) static int smsusb1_load_firmware(struct usb_device *udev, int id, int board_id)
{
	const struct firmware *fw;
	u8 *fw_buffer;
	int rc, dummy;
	char *fw_filename;

	if (id < DEVICE_MODE_DVBT || id > DEVICE_MODE_DVBT_BDA) {
		sms_err("invalid firmware id specified %d", id);
		return -EINVAL;
	}

	fw_filename = sms_get_fw_name(id, board_id);

	rc = request_firmware(&fw, fw_filename, &udev->dev);
	if (rc < 0) {
		sms_warn("failed to open \"%s\" mode %d, "
			 "trying again with default firmware", fw_filename, id);

		fw_filename = smsusb1_fw_lkup[id];
		rc = request_firmware(&fw, fw_filename, &udev->dev);
		if (rc < 0) {
			sms_warn("failed to open \"%s\" mode %d",
				 fw_filename, id);

			return rc;
		}
	}

	fw_buffer = kmalloc(fw->size, GFP_KERNEL);
	if (fw_buffer) {
		memcpy(fw_buffer, fw->data, fw->size);

		rc = usb_bulk_msg(udev, usb_sndbulkpipe(udev, 2),
				  fw_buffer, fw->size, &dummy, 1000);

		sms_info("sent %zd(%d) bytes, rc %d", fw->size, dummy, rc);

		kfree(fw_buffer);
	} else {
		sms_err("failed to allocate firmware buffer");
		rc = -ENOMEM;
	}
	sms_info("read FW %s, size=%zd", fw_filename, fw->size);

	release_firmware(fw);

	return rc;
}