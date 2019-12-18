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
struct sas_ha_struct {struct pm8001_hba_info* lldd_ha; } ;
struct pm8001_hba_info {void* fw_status; int /*<<< orphan*/  fw_image; int /*<<< orphan*/  dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int code; int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 size_t EACCES ; 
 int FAIL_OPEN_BIOS_FILE ; 
 int FAIL_OUT_MEMORY ; 
 void* FAIL_PARAMETERS ; 
 int FLASH_CMD_NONE ; 
#define  FLASH_CMD_SET_NVMD 129 
#define  FLASH_CMD_UPDATE 128 
 void* FLASH_IN_PROGRESS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PM8001_FAIL_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 struct sas_ha_struct* SHOST_TO_SAS_HA (struct Scsi_Host*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 struct Scsi_Host* class_to_shost (struct device*) ; 
 TYPE_1__* flash_command_table ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_printk (char*,char*,int) ; 
 int pm8001_set_nvmd (struct pm8001_hba_info*) ; 
 int pm8001_update_flash (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 
 int request_firmware (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int sscanf (char const*,char*,char*,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static ssize_t pm8001_store_update_fw(struct device *cdev,
				      struct device_attribute *attr,
				      const char *buf, size_t count)
{
	struct Scsi_Host *shost = class_to_shost(cdev);
	struct sas_ha_struct *sha = SHOST_TO_SAS_HA(shost);
	struct pm8001_hba_info *pm8001_ha = sha->lldd_ha;
	char *cmd_ptr, *filename_ptr;
	int res, i;
	int flash_command = FLASH_CMD_NONE;
	int err = 0;
	if (!capable(CAP_SYS_ADMIN))
		return -EACCES;

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

	if (pm8001_ha->fw_status == FLASH_IN_PROGRESS) {
		err = FLASH_IN_PROGRESS;
		goto out1;
	}
	err = request_firmware(&pm8001_ha->fw_image,
			       filename_ptr,
			       pm8001_ha->dev);

	if (err) {
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("Failed to load firmware image file %s,"
			" error %d\n", filename_ptr, err));
		err = FAIL_OPEN_BIOS_FILE;
		goto out1;
	}

	switch (flash_command) {
	case FLASH_CMD_UPDATE:
		pm8001_ha->fw_status = FLASH_IN_PROGRESS;
		err = pm8001_update_flash(pm8001_ha);
		break;
	case FLASH_CMD_SET_NVMD:
		pm8001_ha->fw_status = FLASH_IN_PROGRESS;
		err = pm8001_set_nvmd(pm8001_ha);
		break;
	default:
		pm8001_ha->fw_status = FAIL_PARAMETERS;
		err = FAIL_PARAMETERS;
		break;
	}
	release_firmware(pm8001_ha->fw_image);
out1:
	kfree(cmd_ptr);
out:
	pm8001_ha->fw_status = err;

	if (!err)
		return count;
	else
		return -err;
}