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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct sg_io_hdr {int dummy; } ;
struct nvme_ns {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int MODE_PAGE_CACHING ; 
 int MODE_PAGE_CONTROL ; 
 int MODE_PAGE_POWER_CONDITION ; 
 scalar_t__ MODE_SELECT_10_MPH_SIZE ; 
 scalar_t__ MODE_SELECT_6_MPH_SIZE ; 
 int MODE_SELECT_PAGE_CODE_MASK ; 
 int /*<<< orphan*/  SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  SCSI_ASCQ_CAUSE_NOT_REPORTABLE ; 
 int /*<<< orphan*/  SCSI_ASC_INVALID_CDB ; 
 int SNTI_TRANSLATION_SUCCESS ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int nvme_trans_completion (struct sg_io_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvme_trans_copy_from_user (struct sg_io_hdr*,int*,scalar_t__) ; 
 int /*<<< orphan*/  nvme_trans_modesel_get_bd_len (int*,int,scalar_t__*,int*) ; 
 int nvme_trans_modesel_get_mp (struct nvme_ns*,struct sg_io_hdr*,int*,int) ; 
 int /*<<< orphan*/  nvme_trans_modesel_save_bd (struct nvme_ns*,int*,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static int nvme_trans_modesel_data(struct nvme_ns *ns, struct sg_io_hdr *hdr,
					u8 *cmd, u16 parm_list_len, u8 pf,
					u8 sp, u8 cdb10)
{
	int res = SNTI_TRANSLATION_SUCCESS;
	u8 *parm_list;
	u16 bd_len;
	u8 llbaa = 0;
	u16 index, saved_index;
	u8 page_code;
	u16 mp_size;

	/* Get parm list from data-in/out buffer */
	parm_list = kmalloc(parm_list_len, GFP_KERNEL);
	if (parm_list == NULL) {
		res = -ENOMEM;
		goto out;
	}

	res = nvme_trans_copy_from_user(hdr, parm_list, parm_list_len);
	if (res != SNTI_TRANSLATION_SUCCESS)
		goto out_mem;

	nvme_trans_modesel_get_bd_len(parm_list, cdb10, &bd_len, &llbaa);
	index = (cdb10) ? (MODE_SELECT_10_MPH_SIZE) : (MODE_SELECT_6_MPH_SIZE);

	if (bd_len != 0) {
		/* Block Descriptors present, parse */
		nvme_trans_modesel_save_bd(ns, parm_list, index, bd_len, llbaa);
		index += bd_len;
	}
	saved_index = index;

	/* Multiple mode pages may be present; iterate through all */
	/* In 1st Iteration, don't do NVME Command, only check for CDB errors */
	do {
		page_code = parm_list[index] & MODE_SELECT_PAGE_CODE_MASK;
		mp_size = parm_list[index + 1] + 2;
		if ((page_code != MODE_PAGE_CACHING) &&
		    (page_code != MODE_PAGE_CONTROL) &&
		    (page_code != MODE_PAGE_POWER_CONDITION)) {
			res = nvme_trans_completion(hdr,
						SAM_STAT_CHECK_CONDITION,
						ILLEGAL_REQUEST,
						SCSI_ASC_INVALID_CDB,
						SCSI_ASCQ_CAUSE_NOT_REPORTABLE);
			goto out_mem;
		}
		index += mp_size;
	} while (index < parm_list_len);

	/* In 2nd Iteration, do the NVME Commands */
	index = saved_index;
	do {
		page_code = parm_list[index] & MODE_SELECT_PAGE_CODE_MASK;
		mp_size = parm_list[index + 1] + 2;
		res = nvme_trans_modesel_get_mp(ns, hdr, &parm_list[index],
								page_code);
		if (res != SNTI_TRANSLATION_SUCCESS)
			break;
		index += mp_size;
	} while (index < parm_list_len);

 out_mem:
	kfree(parm_list);
 out:
	return res;
}