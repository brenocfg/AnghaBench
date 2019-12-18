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
typedef  scalar_t__ u8 ;
typedef  unsigned int u32 ;
struct sg_io_hdr {scalar_t__ iovec_count; scalar_t__ dxferp; } ;
struct nvme_ns {struct nvme_dev* dev; } ;
struct nvme_iod {int dummy; } ;
struct nvme_dev {int dummy; } ;
struct TYPE_4__ {void** cdw10; scalar_t__ opcode; } ;
struct TYPE_3__ {void* offset; void* numd; } ;
struct nvme_command {TYPE_2__ common; TYPE_1__ dlfw; } ;
typedef  int /*<<< orphan*/  c ;

/* Variables and functions */
 unsigned int BYTES_TO_DWORDS ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 scalar_t__ IS_ERR (struct nvme_iod*) ; 
 scalar_t__ NVME_FWACT_REPL_ACTV ; 
 int PTR_ERR (struct nvme_iod*) ; 
 int /*<<< orphan*/  SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  SCSI_ASCQ_CAUSE_NOT_REPORTABLE ; 
 int /*<<< orphan*/  SCSI_ASC_INVALID_CDB ; 
 int SNTI_TRANSLATION_SUCCESS ; 
 void* cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  memset (struct nvme_command*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ nvme_admin_activate_fw ; 
 scalar_t__ nvme_admin_download_fw ; 
 int /*<<< orphan*/  nvme_free_iod (struct nvme_dev*,struct nvme_iod*) ; 
 struct nvme_iod* nvme_map_user_pages (struct nvme_dev*,int /*<<< orphan*/ ,unsigned long,unsigned int) ; 
 unsigned int nvme_setup_prps (struct nvme_dev*,TYPE_2__*,struct nvme_iod*,unsigned int,int /*<<< orphan*/ ) ; 
 int nvme_submit_admin_cmd (struct nvme_dev*,struct nvme_command*,int /*<<< orphan*/ *) ; 
 int nvme_trans_completion (struct sg_io_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvme_trans_status_code (struct sg_io_hdr*,int) ; 
 int /*<<< orphan*/  nvme_unmap_user_pages (struct nvme_dev*,int /*<<< orphan*/ ,struct nvme_iod*) ; 

__attribute__((used)) static int nvme_trans_send_fw_cmd(struct nvme_ns *ns, struct sg_io_hdr *hdr,
					u8 opcode, u32 tot_len, u32 offset,
					u8 buffer_id)
{
	int res = SNTI_TRANSLATION_SUCCESS;
	int nvme_sc;
	struct nvme_dev *dev = ns->dev;
	struct nvme_command c;
	struct nvme_iod *iod = NULL;
	unsigned length;

	memset(&c, 0, sizeof(c));
	c.common.opcode = opcode;
	if (opcode == nvme_admin_download_fw) {
		if (hdr->iovec_count > 0) {
			/* Assuming SGL is not allowed for this command */
			res = nvme_trans_completion(hdr,
						SAM_STAT_CHECK_CONDITION,
						ILLEGAL_REQUEST,
						SCSI_ASC_INVALID_CDB,
						SCSI_ASCQ_CAUSE_NOT_REPORTABLE);
			goto out;
		}
		iod = nvme_map_user_pages(dev, DMA_TO_DEVICE,
				(unsigned long)hdr->dxferp, tot_len);
		if (IS_ERR(iod)) {
			res = PTR_ERR(iod);
			goto out;
		}
		length = nvme_setup_prps(dev, &c.common, iod, tot_len,
								GFP_KERNEL);
		if (length != tot_len) {
			res = -ENOMEM;
			goto out_unmap;
		}

		c.dlfw.numd = cpu_to_le32((tot_len/BYTES_TO_DWORDS) - 1);
		c.dlfw.offset = cpu_to_le32(offset/BYTES_TO_DWORDS);
	} else if (opcode == nvme_admin_activate_fw) {
		u32 cdw10 = buffer_id | NVME_FWACT_REPL_ACTV;
		c.common.cdw10[0] = cpu_to_le32(cdw10);
	}

	nvme_sc = nvme_submit_admin_cmd(dev, &c, NULL);
	res = nvme_trans_status_code(hdr, nvme_sc);
	if (res)
		goto out_unmap;
	if (nvme_sc)
		res = nvme_sc;

 out_unmap:
	if (opcode == nvme_admin_download_fw) {
		nvme_unmap_user_pages(dev, DMA_TO_DEVICE, iod);
		nvme_free_iod(dev, iod);
	}
 out:
	return res;
}