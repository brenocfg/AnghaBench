#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct pm8001_ioctl_payload {int /*<<< orphan*/  func_specific; } ;
struct TYPE_6__ {TYPE_1__* region; } ;
struct pm8001_hba_info {struct pm8001_ccb_info* ccb_info; TYPE_2__ memoryMap; } ;
struct pm8001_ccb_info {size_t ccb_tag; struct fw_control_ex* fw_control_context; } ;
struct TYPE_7__ {scalar_t__ e; int /*<<< orphan*/  len; } ;
struct TYPE_8__ {TYPE_3__ im_len; int /*<<< orphan*/  addr; } ;
struct fw_flash_updata_info {int /*<<< orphan*/  total_image_len; int /*<<< orphan*/  cur_image_len; int /*<<< orphan*/  cur_image_offset; TYPE_4__ sgl; } ;
struct fw_control_info {int /*<<< orphan*/  len; int /*<<< orphan*/  size; int /*<<< orphan*/  offset; int /*<<< orphan*/  buffer; } ;
struct fw_control_ex {int /*<<< orphan*/  len; int /*<<< orphan*/  phys_addr; void* virtAddr; struct fw_control_info* fw_control; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_5__ {int /*<<< orphan*/  phys_addr; void* virt_ptr; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t FW_FLASH ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fw_control_ex*) ; 
 struct fw_control_ex* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pm8001_chip_fw_flash_update_build (struct pm8001_hba_info*,struct fw_flash_updata_info*,size_t) ; 
 int pm8001_tag_alloc (struct pm8001_hba_info*,size_t*) ; 

int
pm8001_chip_fw_flash_update_req(struct pm8001_hba_info *pm8001_ha,
	void *payload)
{
	struct fw_flash_updata_info flash_update_info;
	struct fw_control_info *fw_control;
	struct fw_control_ex *fw_control_context;
	int rc;
	u32 tag;
	struct pm8001_ccb_info *ccb;
	void *buffer = pm8001_ha->memoryMap.region[FW_FLASH].virt_ptr;
	dma_addr_t phys_addr = pm8001_ha->memoryMap.region[FW_FLASH].phys_addr;
	struct pm8001_ioctl_payload *ioctl_payload = payload;

	fw_control_context = kzalloc(sizeof(struct fw_control_ex), GFP_KERNEL);
	if (!fw_control_context)
		return -ENOMEM;
	fw_control = (struct fw_control_info *)&ioctl_payload->func_specific;
	memcpy(buffer, fw_control->buffer, fw_control->len);
	flash_update_info.sgl.addr = cpu_to_le64(phys_addr);
	flash_update_info.sgl.im_len.len = cpu_to_le32(fw_control->len);
	flash_update_info.sgl.im_len.e = 0;
	flash_update_info.cur_image_offset = fw_control->offset;
	flash_update_info.cur_image_len = fw_control->len;
	flash_update_info.total_image_len = fw_control->size;
	fw_control_context->fw_control = fw_control;
	fw_control_context->virtAddr = buffer;
	fw_control_context->phys_addr = phys_addr;
	fw_control_context->len = fw_control->len;
	rc = pm8001_tag_alloc(pm8001_ha, &tag);
	if (rc) {
		kfree(fw_control_context);
		return rc;
	}
	ccb = &pm8001_ha->ccb_info[tag];
	ccb->fw_control_context = fw_control_context;
	ccb->ccb_tag = tag;
	rc = pm8001_chip_fw_flash_update_build(pm8001_ha, &flash_update_info,
		tag);
	return rc;
}