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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct pm8001_ioctl_payload {int length; int /*<<< orphan*/  func_specific; scalar_t__ id; } ;
struct pm8001_hba_info {int /*<<< orphan*/ * nvmd_completion; TYPE_1__* fw_image; } ;
struct pm8001_fw_image_header {int /*<<< orphan*/  image_length; } ;
struct fw_control_info {int len; int size; scalar_t__ retcode; int offset; scalar_t__ buffer; } ;
struct TYPE_4__ {int (* fw_flash_update_req ) (struct pm8001_hba_info*,struct pm8001_ioctl_payload*) ;} ;
struct TYPE_3__ {int size; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int FAIL_FILE_SIZE ; 
 scalar_t__ FLASH_UPDATE_IN_PROGRESS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HEADER_LEN ; 
 int IOCTL_BUF_SIZE ; 
 TYPE_2__* PM8001_CHIP_DISP ; 
 int be32_to_cpu (int) ; 
 int /*<<< orphan*/  completion ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int stub1 (struct pm8001_hba_info*,struct pm8001_ioctl_payload*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pm8001_update_flash(struct pm8001_hba_info *pm8001_ha)
{
	struct pm8001_ioctl_payload	*payload;
	DECLARE_COMPLETION_ONSTACK(completion);
	u8		*ioctlbuffer = NULL;
	u32		length = 0;
	struct fw_control_info	*fwControl;
	u32		loopNumber, loopcount = 0;
	u32		sizeRead = 0;
	u32		partitionSize, partitionSizeTmp;
	u32		ret = 0;
	u32		partitionNumber = 0;
	struct pm8001_fw_image_header *image_hdr;

	length = 1024 * 16 + sizeof(*payload) - 1;
	ioctlbuffer = kzalloc(length, GFP_KERNEL);
	image_hdr = (struct pm8001_fw_image_header *)pm8001_ha->fw_image->data;
	if (!ioctlbuffer)
		return -ENOMEM;
	if (pm8001_ha->fw_image->size < 28) {
		ret = FAIL_FILE_SIZE;
		goto out;
	}

	while (sizeRead < pm8001_ha->fw_image->size) {
		partitionSizeTmp =
			*(u32 *)((u8 *)&image_hdr->image_length + sizeRead);
		partitionSize = be32_to_cpu(partitionSizeTmp);
		loopcount = (partitionSize + HEADER_LEN)/IOCTL_BUF_SIZE;
		if (loopcount % IOCTL_BUF_SIZE)
			loopcount++;
		if (loopcount == 0)
			loopcount++;
		for (loopNumber = 0; loopNumber < loopcount; loopNumber++) {
			payload = (struct pm8001_ioctl_payload *)ioctlbuffer;
			payload->length = 1024*16;
			payload->id = 0;
			fwControl =
			      (struct fw_control_info *)&payload->func_specific;
			fwControl->len = IOCTL_BUF_SIZE;   /* IN */
			fwControl->size = partitionSize + HEADER_LEN;/* IN */
			fwControl->retcode = 0;/* OUT */
			fwControl->offset = loopNumber * IOCTL_BUF_SIZE;/*OUT */

		/* for the last chunk of data in case file size is not even with
		4k, load only the rest*/
		if (((loopcount-loopNumber) == 1) &&
			((partitionSize + HEADER_LEN) % IOCTL_BUF_SIZE)) {
			fwControl->len =
				(partitionSize + HEADER_LEN) % IOCTL_BUF_SIZE;
			memcpy((u8 *)fwControl->buffer,
				(u8 *)pm8001_ha->fw_image->data + sizeRead,
				(partitionSize + HEADER_LEN) % IOCTL_BUF_SIZE);
			sizeRead +=
				(partitionSize + HEADER_LEN) % IOCTL_BUF_SIZE;
		} else {
			memcpy((u8 *)fwControl->buffer,
				(u8 *)pm8001_ha->fw_image->data + sizeRead,
				IOCTL_BUF_SIZE);
			sizeRead += IOCTL_BUF_SIZE;
		}

		pm8001_ha->nvmd_completion = &completion;
		ret = PM8001_CHIP_DISP->fw_flash_update_req(pm8001_ha, payload);
		wait_for_completion(&completion);
		if (ret || (fwControl->retcode > FLASH_UPDATE_IN_PROGRESS)) {
			ret = fwControl->retcode;
			kfree(ioctlbuffer);
			ioctlbuffer = NULL;
			break;
		}
	}
	if (ret)
		break;
	partitionNumber++;
}
out:
	kfree(ioctlbuffer);
	return ret;
}