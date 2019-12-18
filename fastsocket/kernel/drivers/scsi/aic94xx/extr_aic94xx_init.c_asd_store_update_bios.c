#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_6__ {scalar_t__ vendor; scalar_t__ device; scalar_t__ sub_vendor; scalar_t__ sub_device; } ;
struct bios_file_header {int filelen; int checksum; TYPE_1__ contrl_id; } ;
struct asd_ha_struct {void* bios_status; TYPE_3__* bios_image; TYPE_2__* pcidev; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  header ;
struct TYPE_9__ {int code; int /*<<< orphan*/  command; } ;
struct TYPE_8__ {int size; scalar_t__* data; } ;
struct TYPE_7__ {scalar_t__ vendor; scalar_t__ device; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASD_DPRINTK (char*,...) ; 
 int FAIL_CHECK_PCI_ID ; 
 int FAIL_CHECK_SUM ; 
 int FAIL_FILE_SIZE ; 
 int FAIL_OPEN_BIOS_FILE ; 
 int FAIL_OUT_MEMORY ; 
 int FAIL_PARAMETERS ; 
 int FLASH_CMD_NONE ; 
 int FLASH_CMD_UPDATE ; 
 void* FLASH_IN_PROGRESS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  asd_printk (char*,char*,int) ; 
 int asd_verify_flash_seg (struct asd_ha_struct*,scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int asd_write_flash_seg (struct asd_ha_struct*,scalar_t__*,int /*<<< orphan*/ ,int) ; 
 struct asd_ha_struct* dev_to_asd_ha (struct device*) ; 
 TYPE_5__* flash_command_table ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (TYPE_3__*) ; 
 int request_firmware (TYPE_3__**,char*,int /*<<< orphan*/ *) ; 
 int sscanf (char const*,char*,char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static ssize_t asd_store_update_bios(struct device *dev,
	struct device_attribute *attr,
	const char *buf, size_t count)
{
	struct asd_ha_struct *asd_ha = dev_to_asd_ha(dev);
	char *cmd_ptr, *filename_ptr;
	struct bios_file_header header, *hdr_ptr;
	int res, i;
	u32 csum = 0;
	int flash_command = FLASH_CMD_NONE;
	int err = 0;

	cmd_ptr = kzalloc(count*2, GFP_KERNEL);

	if (!cmd_ptr) {
		err = FAIL_OUT_MEMORY;
		goto out;
	}

	filename_ptr = cmd_ptr + count;
	res = sscanf(buf, "%s %s", cmd_ptr, filename_ptr);
	if (res != 2) {
		err = FAIL_PARAMETERS;
		goto out1;
	}

	for (i = 0; flash_command_table[i].code != FLASH_CMD_NONE; i++) {
		if (!memcmp(flash_command_table[i].command,
				 cmd_ptr, strlen(cmd_ptr))) {
			flash_command = flash_command_table[i].code;
			break;
		}
	}
	if (flash_command == FLASH_CMD_NONE) {
		err = FAIL_PARAMETERS;
		goto out1;
	}

	if (asd_ha->bios_status == FLASH_IN_PROGRESS) {
		err = FLASH_IN_PROGRESS;
		goto out1;
	}
	err = request_firmware(&asd_ha->bios_image,
				   filename_ptr,
				   &asd_ha->pcidev->dev);
	if (err) {
		asd_printk("Failed to load bios image file %s, error %d\n",
			   filename_ptr, err);
		err = FAIL_OPEN_BIOS_FILE;
		goto out1;
	}

	hdr_ptr = (struct bios_file_header *)asd_ha->bios_image->data;

	if ((hdr_ptr->contrl_id.vendor != asd_ha->pcidev->vendor ||
		hdr_ptr->contrl_id.device != asd_ha->pcidev->device) &&
		(hdr_ptr->contrl_id.sub_vendor != asd_ha->pcidev->vendor ||
		hdr_ptr->contrl_id.sub_device != asd_ha->pcidev->device)) {

		ASD_DPRINTK("The PCI vendor or device id does not match\n");
		ASD_DPRINTK("vendor=%x dev=%x sub_vendor=%x sub_dev=%x"
		" pci vendor=%x pci dev=%x\n",
		hdr_ptr->contrl_id.vendor,
		hdr_ptr->contrl_id.device,
		hdr_ptr->contrl_id.sub_vendor,
		hdr_ptr->contrl_id.sub_device,
		asd_ha->pcidev->vendor,
		asd_ha->pcidev->device);
		err = FAIL_CHECK_PCI_ID;
		goto out2;
	}

	if (hdr_ptr->filelen != asd_ha->bios_image->size) {
		err = FAIL_FILE_SIZE;
		goto out2;
	}

	/* calculate checksum */
	for (i = 0; i < hdr_ptr->filelen; i++)
		csum += asd_ha->bios_image->data[i];

	if ((csum & 0x0000ffff) != hdr_ptr->checksum) {
		ASD_DPRINTK("BIOS file checksum mismatch\n");
		err = FAIL_CHECK_SUM;
		goto out2;
	}
	if (flash_command == FLASH_CMD_UPDATE) {
		asd_ha->bios_status = FLASH_IN_PROGRESS;
		err = asd_write_flash_seg(asd_ha,
			&asd_ha->bios_image->data[sizeof(*hdr_ptr)],
			0, hdr_ptr->filelen-sizeof(*hdr_ptr));
		if (!err)
			err = asd_verify_flash_seg(asd_ha,
				&asd_ha->bios_image->data[sizeof(*hdr_ptr)],
				0, hdr_ptr->filelen-sizeof(*hdr_ptr));
	} else {
		asd_ha->bios_status = FLASH_IN_PROGRESS;
		err = asd_verify_flash_seg(asd_ha,
			&asd_ha->bios_image->data[sizeof(header)],
			0, hdr_ptr->filelen-sizeof(header));
	}

out2:
	release_firmware(asd_ha->bios_image);
out1:
	kfree(cmd_ptr);
out:
	asd_ha->bios_status = err;

	if (!err)
		return count;
	else
		return -err;
}