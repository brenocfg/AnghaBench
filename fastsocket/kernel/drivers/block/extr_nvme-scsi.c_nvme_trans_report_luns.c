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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct sg_io_hdr {int dummy; } ;
struct nvme_ns {struct nvme_dev* dev; } ;
struct nvme_id_ctrl {int /*<<< orphan*/  nn; } ;
struct nvme_dev {TYPE_1__* pci_dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
typedef  int /*<<< orphan*/  __be64 ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ALL_LUNS_RETURNED ; 
 scalar_t__ ALL_WELL_KNOWN_LUNS_RETURNED ; 
 int ENOMEM ; 
 scalar_t__ GET_REPORT_LUNS_ALLOC_LENGTH (scalar_t__*) ; 
 scalar_t__ GET_U8_FROM_CDB (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 scalar_t__ LUN_DATA_HEADER_SIZE ; 
 scalar_t__ LUN_ENTRY_SIZE ; 
 scalar_t__ REPORT_LUNS_FIRST_LUN_OFFSET ; 
 int /*<<< orphan*/  REPORT_LUNS_SR_OFFSET ; 
 scalar_t__ RESTRICTED_LUNS_RETURNED ; 
 int /*<<< orphan*/  SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  SCSI_ASCQ_CAUSE_NOT_REPORTABLE ; 
 int /*<<< orphan*/  SCSI_ASC_INVALID_CDB ; 
 int SNTI_TRANSLATION_SUCCESS ; 
 int /*<<< orphan*/  cpu_to_be32 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_be64 (scalar_t__) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int nvme_identify (struct nvme_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int nvme_trans_completion (struct sg_io_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvme_trans_copy_to_user (struct sg_io_hdr*,scalar_t__*,scalar_t__) ; 
 int nvme_trans_status_code (struct sg_io_hdr*,int) ; 

__attribute__((used)) static int nvme_trans_report_luns(struct nvme_ns *ns, struct sg_io_hdr *hdr,
							u8 *cmd)
{
	int res = SNTI_TRANSLATION_SUCCESS;
	int nvme_sc;
	u32 alloc_len, xfer_len, resp_size;
	u8 select_report;
	u8 *response;
	struct nvme_dev *dev = ns->dev;
	dma_addr_t dma_addr;
	void *mem;
	struct nvme_id_ctrl *id_ctrl;
	u32 ll_length, lun_id;
	u8 lun_id_offset = REPORT_LUNS_FIRST_LUN_OFFSET;
	__be32 tmp_len;

	alloc_len = GET_REPORT_LUNS_ALLOC_LENGTH(cmd);
	select_report = GET_U8_FROM_CDB(cmd, REPORT_LUNS_SR_OFFSET);

	if ((select_report != ALL_LUNS_RETURNED) &&
	    (select_report != ALL_WELL_KNOWN_LUNS_RETURNED) &&
	    (select_report != RESTRICTED_LUNS_RETURNED)) {
		res = nvme_trans_completion(hdr, SAM_STAT_CHECK_CONDITION,
					ILLEGAL_REQUEST, SCSI_ASC_INVALID_CDB,
					SCSI_ASCQ_CAUSE_NOT_REPORTABLE);
		goto out;
	} else {
		/* NVMe Controller Identify */
		mem = dma_alloc_coherent(&dev->pci_dev->dev,
					sizeof(struct nvme_id_ctrl),
					&dma_addr, GFP_KERNEL);
		if (mem == NULL) {
			res = -ENOMEM;
			goto out;
		}
		nvme_sc = nvme_identify(dev, 0, 1, dma_addr);
		res = nvme_trans_status_code(hdr, nvme_sc);
		if (res)
			goto out_dma;
		if (nvme_sc) {
			res = nvme_sc;
			goto out_dma;
		}
		id_ctrl = mem;
		ll_length = le32_to_cpu(id_ctrl->nn) * LUN_ENTRY_SIZE;
		resp_size = ll_length + LUN_DATA_HEADER_SIZE;

		if (alloc_len < resp_size) {
			res = nvme_trans_completion(hdr,
					SAM_STAT_CHECK_CONDITION,
					ILLEGAL_REQUEST, SCSI_ASC_INVALID_CDB,
					SCSI_ASCQ_CAUSE_NOT_REPORTABLE);
			goto out_dma;
		}

		response = kzalloc(resp_size, GFP_KERNEL);
		if (response == NULL) {
			res = -ENOMEM;
			goto out_dma;
		}

		/* The first LUN ID will always be 0 per the SAM spec */
		for (lun_id = 0; lun_id < le32_to_cpu(id_ctrl->nn); lun_id++) {
			/*
			 * Set the LUN Id and then increment to the next LUN
			 * location in the parameter data.
			 */
			__be64 tmp_id = cpu_to_be64(lun_id);
			memcpy(&response[lun_id_offset], &tmp_id, sizeof(u64));
			lun_id_offset += LUN_ENTRY_SIZE;
		}
		tmp_len = cpu_to_be32(ll_length);
		memcpy(response, &tmp_len, sizeof(u32));
	}

	xfer_len = min(alloc_len, resp_size);
	res = nvme_trans_copy_to_user(hdr, response, xfer_len);

	kfree(response);
 out_dma:
	dma_free_coherent(&dev->pci_dev->dev, sizeof(struct nvme_id_ctrl), mem,
			  dma_addr);
 out:
	return res;
}