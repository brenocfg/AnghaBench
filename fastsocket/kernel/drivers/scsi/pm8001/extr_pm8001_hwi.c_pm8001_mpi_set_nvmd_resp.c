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
typedef  size_t u32 ;
struct pm8001_hba_info {int /*<<< orphan*/  nvmd_completion; struct pm8001_ccb_info* ccb_info; } ;
struct pm8001_ccb_info {int ccb_tag; int /*<<< orphan*/ * task; } ;
struct get_nvm_data_resp {int /*<<< orphan*/  dlen_status; int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 size_t NVMD_STAT ; 
 int /*<<< orphan*/  PM8001_FAIL_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM8001_MSG_DBG (struct pm8001_hba_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ ) ; 
 size_t le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_ccb_free (struct pm8001_hba_info*,size_t) ; 
 int /*<<< orphan*/  pm8001_printk (char*) ; 

void pm8001_mpi_set_nvmd_resp(struct pm8001_hba_info *pm8001_ha, void *piomb)
{
	struct get_nvm_data_resp *pPayload =
		(struct get_nvm_data_resp *)(piomb + 4);
	u32 tag = le32_to_cpu(pPayload->tag);
	struct pm8001_ccb_info *ccb = &pm8001_ha->ccb_info[tag];
	u32 dlen_status = le32_to_cpu(pPayload->dlen_status);
	complete(pm8001_ha->nvmd_completion);
	PM8001_MSG_DBG(pm8001_ha, pm8001_printk("Set nvm data complete!\n"));
	if ((dlen_status & NVMD_STAT) != 0) {
		PM8001_FAIL_DBG(pm8001_ha,
			pm8001_printk("Set nvm data error!\n"));
		return;
	}
	ccb->task = NULL;
	ccb->ccb_tag = 0xFFFFFFFF;
	pm8001_ccb_free(pm8001_ha, tag);
}