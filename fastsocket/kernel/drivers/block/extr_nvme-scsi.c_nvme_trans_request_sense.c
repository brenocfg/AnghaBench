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
struct nvme_ns {int dummy; } ;

/* Variables and functions */
 int DESCRIPTOR_FORMAT_SENSE_DATA_TYPE ; 
 int DESC_FMT_SENSE_DATA_SIZE ; 
 int DESC_FORMAT_SENSE_DATA ; 
 int ENOMEM ; 
 int FIXED_FMT_SENSE_DATA_SIZE ; 
 int FIXED_SENSE_DATA ; 
 int FIXED_SENSE_DATA_ADD_LENGTH ; 
 int GET_REQUEST_SENSE_ALLOC_LENGTH (int*) ; 
 int GET_U8_FROM_CDB (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NO_SENSE ; 
 int REQUEST_SENSE_DESC_MASK ; 
 int /*<<< orphan*/  REQUEST_SENSE_DESC_OFFSET ; 
 int SCSI_ASCQ_CAUSE_NOT_REPORTABLE ; 
 int SCSI_ASC_NO_SENSE ; 
 int SNTI_TRANSLATION_SUCCESS ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kzalloc (int,int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 int nvme_trans_copy_to_user (struct sg_io_hdr*,int*,int) ; 

__attribute__((used)) static int nvme_trans_request_sense(struct nvme_ns *ns, struct sg_io_hdr *hdr,
							u8 *cmd)
{
	int res = SNTI_TRANSLATION_SUCCESS;
	u8 alloc_len, xfer_len, resp_size;
	u8 desc_format;
	u8 *response;

	alloc_len = GET_REQUEST_SENSE_ALLOC_LENGTH(cmd);
	desc_format = GET_U8_FROM_CDB(cmd, REQUEST_SENSE_DESC_OFFSET);
	desc_format &= REQUEST_SENSE_DESC_MASK;

	resp_size = ((desc_format) ? (DESC_FMT_SENSE_DATA_SIZE) :
					(FIXED_FMT_SENSE_DATA_SIZE));
	response = kzalloc(resp_size, GFP_KERNEL);
	if (response == NULL) {
		res = -ENOMEM;
		goto out;
	}

	if (desc_format == DESCRIPTOR_FORMAT_SENSE_DATA_TYPE) {
		/* Descriptor Format Sense Data */
		response[0] = DESC_FORMAT_SENSE_DATA;
		response[1] = NO_SENSE;
		/* TODO How is LOW POWER CONDITION ON handled? (byte 2) */
		response[2] = SCSI_ASC_NO_SENSE;
		response[3] = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
		/* SDAT_OVFL = 0 | Additional Sense Length = 0 */
	} else {
		/* Fixed Format Sense Data */
		response[0] = FIXED_SENSE_DATA;
		/* Byte 1 = Obsolete */
		response[2] = NO_SENSE; /* FM, EOM, ILI, SDAT_OVFL = 0 */
		/* Bytes 3-6 - Information - set to zero */
		response[7] = FIXED_SENSE_DATA_ADD_LENGTH;
		/* Bytes 8-11 - Cmd Specific Information - set to zero */
		response[12] = SCSI_ASC_NO_SENSE;
		response[13] = SCSI_ASCQ_CAUSE_NOT_REPORTABLE;
		/* Byte 14 = Field Replaceable Unit Code = 0 */
		/* Bytes 15-17 - SKSV=0; Sense Key Specific = 0 */
	}

	xfer_len = min(alloc_len, resp_size);
	res = nvme_trans_copy_to_user(hdr, response, xfer_len);

	kfree(response);
 out:
	return res;
}