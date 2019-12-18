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
typedef  int u8 ;
struct sg_io_hdr {int dummy; } ;
struct nvme_ns {struct nvme_dev* dev; } ;
struct nvme_id_ctrl {int npss; } ;
struct nvme_dev {TYPE_1__* pci_dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int /*<<< orphan*/  NVME_FEAT_POWER_MGMT ; 
#define  NVME_POWER_STATE_ACTIVE 132 
#define  NVME_POWER_STATE_IDLE 131 
#define  NVME_POWER_STATE_LU_CONTROL 130 
#define  NVME_POWER_STATE_STANDBY 129 
#define  NVME_POWER_STATE_START_VALID 128 
 unsigned int POWER_STATE_0 ; 
 int /*<<< orphan*/  POWER_STATE_1 ; 
 int /*<<< orphan*/  POWER_STATE_2 ; 
 int /*<<< orphan*/  POWER_STATE_3 ; 
 int /*<<< orphan*/  SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  SCSI_ASCQ_CAUSE_NOT_REPORTABLE ; 
 int /*<<< orphan*/  SCSI_ASC_INVALID_CDB ; 
 int SNTI_TRANSLATION_SUCCESS ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,void*,int /*<<< orphan*/ ) ; 
 unsigned int max (int /*<<< orphan*/ ,int) ; 
 unsigned int min (int /*<<< orphan*/ ,int) ; 
 int nvme_identify (struct nvme_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int nvme_set_features (struct nvme_dev*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nvme_trans_completion (struct sg_io_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvme_trans_status_code (struct sg_io_hdr*,int) ; 

__attribute__((used)) static int nvme_trans_power_state(struct nvme_ns *ns, struct sg_io_hdr *hdr,
						u8 pc, u8 pcmod, u8 start)
{
	int res = SNTI_TRANSLATION_SUCCESS;
	int nvme_sc;
	struct nvme_dev *dev = ns->dev;
	dma_addr_t dma_addr;
	void *mem;
	struct nvme_id_ctrl *id_ctrl;
	int lowest_pow_st;	/* max npss = lowest power consumption */
	unsigned ps_desired = 0;

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
	lowest_pow_st = id_ctrl->npss - 1;

	switch (pc) {
	case NVME_POWER_STATE_START_VALID:
		/* Action unspecified if POWER CONDITION MODIFIER != 0 */
		if (pcmod == 0 && start == 0x1)
			ps_desired = POWER_STATE_0;
		if (pcmod == 0 && start == 0x0)
			ps_desired = lowest_pow_st;
		break;
	case NVME_POWER_STATE_ACTIVE:
		/* Action unspecified if POWER CONDITION MODIFIER != 0 */
		if (pcmod == 0)
			ps_desired = POWER_STATE_0;
		break;
	case NVME_POWER_STATE_IDLE:
		/* Action unspecified if POWER CONDITION MODIFIER != [0,1,2] */
		/* min of desired state and (lps-1) because lps is STOP */
		if (pcmod == 0x0)
			ps_desired = min(POWER_STATE_1, (lowest_pow_st - 1));
		else if (pcmod == 0x1)
			ps_desired = min(POWER_STATE_2, (lowest_pow_st - 1));
		else if (pcmod == 0x2)
			ps_desired = min(POWER_STATE_3, (lowest_pow_st - 1));
		break;
	case NVME_POWER_STATE_STANDBY:
		/* Action unspecified if POWER CONDITION MODIFIER != [0,1] */
		if (pcmod == 0x0)
			ps_desired = max(0, (lowest_pow_st - 2));
		else if (pcmod == 0x1)
			ps_desired = max(0, (lowest_pow_st - 1));
		break;
	case NVME_POWER_STATE_LU_CONTROL:
	default:
		res = nvme_trans_completion(hdr, SAM_STAT_CHECK_CONDITION,
				ILLEGAL_REQUEST, SCSI_ASC_INVALID_CDB,
				SCSI_ASCQ_CAUSE_NOT_REPORTABLE);
		break;
	}
	nvme_sc = nvme_set_features(dev, NVME_FEAT_POWER_MGMT, ps_desired, 0,
				    NULL);
	res = nvme_trans_status_code(hdr, nvme_sc);
	if (res)
		goto out_dma;
	if (nvme_sc)
		res = nvme_sc;
 out_dma:
	dma_free_coherent(&dev->pci_dev->dev, sizeof(struct nvme_id_ctrl), mem,
			  dma_addr);
 out:
	return res;
}