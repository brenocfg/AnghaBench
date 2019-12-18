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
typedef  scalar_t__ u8 ;
struct sg_io_hdr {int dummy; } ;
struct nvme_ns {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GET_INQ_ALLOC_LENGTH (scalar_t__*) ; 
 scalar_t__ GET_INQ_EVPD_BIT (scalar_t__*) ; 
 scalar_t__ GET_INQ_PAGE_CODE (scalar_t__*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 scalar_t__ INQ_STANDARD_INQUIRY_PAGE ; 
 int /*<<< orphan*/  SAM_STAT_CHECK_CONDITION ; 
 int /*<<< orphan*/  SCSI_ASCQ_CAUSE_NOT_REPORTABLE ; 
 int /*<<< orphan*/  SCSI_ASC_INVALID_CDB ; 
 int SNTI_TRANSLATION_SUCCESS ; 
 int /*<<< orphan*/  STANDARD_INQUIRY_LENGTH ; 
#define  VPD_BLOCK_DEV_CHARACTERISTICS 132 
#define  VPD_DEVICE_IDENTIFIERS 131 
#define  VPD_EXTENDED_INQUIRY 130 
#define  VPD_SERIAL_NUMBER 129 
#define  VPD_SUPPORTED_PAGES 128 
 int /*<<< orphan*/  kfree (scalar_t__*) ; 
 scalar_t__* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvme_trans_bdev_char_page (struct nvme_ns*,struct sg_io_hdr*,int) ; 
 int nvme_trans_completion (struct sg_io_hdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nvme_trans_device_id_page (struct nvme_ns*,struct sg_io_hdr*,scalar_t__*,int) ; 
 int nvme_trans_ext_inq_page (struct nvme_ns*,struct sg_io_hdr*,int) ; 
 int nvme_trans_standard_inquiry_page (struct nvme_ns*,struct sg_io_hdr*,scalar_t__*,int) ; 
 int nvme_trans_supported_vpd_pages (struct nvme_ns*,struct sg_io_hdr*,scalar_t__*,int) ; 
 int nvme_trans_unit_serial_page (struct nvme_ns*,struct sg_io_hdr*,scalar_t__*,int) ; 

__attribute__((used)) static int nvme_trans_inquiry(struct nvme_ns *ns, struct sg_io_hdr *hdr,
							u8 *cmd)
{
	int res = SNTI_TRANSLATION_SUCCESS;
	u8 evpd;
	u8 page_code;
	int alloc_len;
	u8 *inq_response;

	evpd = GET_INQ_EVPD_BIT(cmd);
	page_code = GET_INQ_PAGE_CODE(cmd);
	alloc_len = GET_INQ_ALLOC_LENGTH(cmd);

	inq_response = kmalloc(STANDARD_INQUIRY_LENGTH, GFP_KERNEL);
	if (inq_response == NULL) {
		res = -ENOMEM;
		goto out_mem;
	}

	if (evpd == 0) {
		if (page_code == INQ_STANDARD_INQUIRY_PAGE) {
			res = nvme_trans_standard_inquiry_page(ns, hdr,
						inq_response, alloc_len);
		} else {
			res = nvme_trans_completion(hdr,
						SAM_STAT_CHECK_CONDITION,
						ILLEGAL_REQUEST,
						SCSI_ASC_INVALID_CDB,
						SCSI_ASCQ_CAUSE_NOT_REPORTABLE);
		}
	} else {
		switch (page_code) {
		case VPD_SUPPORTED_PAGES:
			res = nvme_trans_supported_vpd_pages(ns, hdr,
						inq_response, alloc_len);
			break;
		case VPD_SERIAL_NUMBER:
			res = nvme_trans_unit_serial_page(ns, hdr, inq_response,
								alloc_len);
			break;
		case VPD_DEVICE_IDENTIFIERS:
			res = nvme_trans_device_id_page(ns, hdr, inq_response,
								alloc_len);
			break;
		case VPD_EXTENDED_INQUIRY:
			res = nvme_trans_ext_inq_page(ns, hdr, alloc_len);
			break;
		case VPD_BLOCK_DEV_CHARACTERISTICS:
			res = nvme_trans_bdev_char_page(ns, hdr, alloc_len);
			break;
		default:
			res = nvme_trans_completion(hdr,
						SAM_STAT_CHECK_CONDITION,
						ILLEGAL_REQUEST,
						SCSI_ASC_INVALID_CDB,
						SCSI_ASCQ_CAUSE_NOT_REPORTABLE);
			break;
		}
	}
	kfree(inq_response);
 out_mem:
	return res;
}