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
struct pm8001_ioctl_payload {int length; int minor_function; scalar_t__ id; int /*<<< orphan*/  func_specific; } ;
struct pm8001_hba_info {int /*<<< orphan*/ * nvmd_completion; TYPE_1__* fw_image; } ;
struct TYPE_4__ {int (* set_nvmd_req ) (struct pm8001_hba_info*,struct pm8001_ioctl_payload*) ;} ;
struct TYPE_3__ {int size; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int FAIL_FILE_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 TYPE_2__* PM8001_CHIP_DISP ; 
 int /*<<< orphan*/  completion ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int stub1 (struct pm8001_hba_info*,struct pm8001_ioctl_payload*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pm8001_set_nvmd(struct pm8001_hba_info *pm8001_ha)
{
	struct pm8001_ioctl_payload	*payload;
	DECLARE_COMPLETION_ONSTACK(completion);
	u8		*ioctlbuffer = NULL;
	u32		length = 0;
	u32		ret = 0;

	length = 1024 * 5 + sizeof(*payload) - 1;
	ioctlbuffer = kzalloc(length, GFP_KERNEL);
	if (!ioctlbuffer)
		return -ENOMEM;
	if ((pm8001_ha->fw_image->size <= 0) ||
	    (pm8001_ha->fw_image->size > 4096)) {
		ret = FAIL_FILE_SIZE;
		goto out;
	}
	payload = (struct pm8001_ioctl_payload *)ioctlbuffer;
	memcpy((u8 *)&payload->func_specific, (u8 *)pm8001_ha->fw_image->data,
				pm8001_ha->fw_image->size);
	payload->length = pm8001_ha->fw_image->size;
	payload->id = 0;
	payload->minor_function = 0x1;
	pm8001_ha->nvmd_completion = &completion;
	ret = PM8001_CHIP_DISP->set_nvmd_req(pm8001_ha, payload);
	wait_for_completion(&completion);
out:
	kfree(ioctlbuffer);
	return ret;
}