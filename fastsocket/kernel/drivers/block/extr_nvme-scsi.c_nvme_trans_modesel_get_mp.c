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
struct sg_io_hdr {int dummy; } ;
struct nvme_ns {struct nvme_dev* dev; } ;
struct nvme_dev {int dummy; } ;

/* Variables and functions */
 int CACHING_MODE_PAGE_WCE_MASK ; 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
#define  MODE_PAGE_CACHING 130 
#define  MODE_PAGE_CONTROL 129 
#define  MODE_PAGE_POWER_CONDITION 128 
 int /*<<< orphan*/  NVME_FEAT_VOLATILE_WC ; 
 int /*<<< orphan*/  SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  SCSI_ASCQ_CAUSE_NOT_REPORTABLE ; 
 int /*<<< orphan*/  SCSI_ASC_INVALID_CDB ; 
 int /*<<< orphan*/  SCSI_ASC_INVALID_PARAMETER ; 
 int SNTI_INTERNAL_ERROR ; 
 int SNTI_TRANSLATION_SUCCESS ; 
 int nvme_set_features (struct nvme_dev*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nvme_trans_completion (struct sg_io_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvme_trans_status_code (struct sg_io_hdr*,int) ; 

__attribute__((used)) static int nvme_trans_modesel_get_mp(struct nvme_ns *ns, struct sg_io_hdr *hdr,
					u8 *mode_page, u8 page_code)
{
	int res = SNTI_TRANSLATION_SUCCESS;
	int nvme_sc;
	struct nvme_dev *dev = ns->dev;
	unsigned dword11;

	switch (page_code) {
	case MODE_PAGE_CACHING:
		dword11 = ((mode_page[2] & CACHING_MODE_PAGE_WCE_MASK) ? 1 : 0);
		nvme_sc = nvme_set_features(dev, NVME_FEAT_VOLATILE_WC, dword11,
					    0, NULL);
		res = nvme_trans_status_code(hdr, nvme_sc);
		if (res)
			break;
		if (nvme_sc) {
			res = nvme_sc;
			break;
		}
		break;
	case MODE_PAGE_CONTROL:
		break;
	case MODE_PAGE_POWER_CONDITION:
		/* Verify the OS is not trying to set timers */
		if ((mode_page[2] & 0x01) != 0 || (mode_page[3] & 0x0F) != 0) {
			res = nvme_trans_completion(hdr,
						SAM_STAT_CHECK_CONDITION,
						ILLEGAL_REQUEST,
						SCSI_ASC_INVALID_PARAMETER,
						SCSI_ASCQ_CAUSE_NOT_REPORTABLE);
			if (!res)
				res = SNTI_INTERNAL_ERROR;
			break;
		}
		break;
	default:
		res = nvme_trans_completion(hdr, SAM_STAT_CHECK_CONDITION,
					ILLEGAL_REQUEST, SCSI_ASC_INVALID_CDB,
					SCSI_ASCQ_CAUSE_NOT_REPORTABLE);
		if (!res)
			res = SNTI_INTERNAL_ERROR;
		break;
	}

	return res;
}