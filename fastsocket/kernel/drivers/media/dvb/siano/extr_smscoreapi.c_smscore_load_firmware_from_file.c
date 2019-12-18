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
struct smscore_device_t {int device_flags; int /*<<< orphan*/  context; int /*<<< orphan*/  device; } ;
struct firmware {int /*<<< orphan*/  size; int /*<<< orphan*/  data; } ;
typedef  int (* loadfirmware_t ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  SMS_ALLOC_ALIGNMENT ; 
 int SMS_DEVICE_FAMILY2 ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sms_info (char*,...) ; 
 int smscore_load_firmware_family2 (struct smscore_device_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smscore_load_firmware_from_file(struct smscore_device_t *coredev,
					   char *filename,
					   loadfirmware_t loadfirmware_handler)
{
	int rc = -ENOENT;
	const struct firmware *fw;
	u8 *fw_buffer;

	if (loadfirmware_handler == NULL && !(coredev->device_flags &
					      SMS_DEVICE_FAMILY2))
		return -EINVAL;

	rc = request_firmware(&fw, filename, coredev->device);
	if (rc < 0) {
		sms_info("failed to open \"%s\"", filename);
		return rc;
	}
	sms_info("read FW %s, size=%zd", filename, fw->size);
	fw_buffer = kmalloc(ALIGN(fw->size, SMS_ALLOC_ALIGNMENT),
			    GFP_KERNEL | GFP_DMA);
	if (fw_buffer) {
		memcpy(fw_buffer, fw->data, fw->size);

		rc = (coredev->device_flags & SMS_DEVICE_FAMILY2) ?
		      smscore_load_firmware_family2(coredev,
						    fw_buffer,
						    fw->size) :
		      loadfirmware_handler(coredev->context,
					   fw_buffer, fw->size);

		kfree(fw_buffer);
	} else {
		sms_info("failed to allocate firmware buffer");
		rc = -ENOMEM;
	}

	release_firmware(fw);

	return rc;
}