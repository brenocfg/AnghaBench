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
struct TYPE_3__ {int req_lim_delta; unsigned char status; int* data; scalar_t__ sense_data_len; int /*<<< orphan*/  flags; scalar_t__ resp_data_len; scalar_t__ data_out_res_cnt; scalar_t__ data_in_res_cnt; int /*<<< orphan*/  tag; int /*<<< orphan*/  opcode; } ;
struct TYPE_4__ {TYPE_1__ rsp; } ;
union viosrp_iu {TYPE_2__ srp; } ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct srp_rsp {int dummy; } ;
struct scsi_cmnd {int /*<<< orphan*/  sense_buffer; } ;
struct iu_entry {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 unsigned char NO_SENSE ; 
 unsigned char SAM_STAT_CHECK_CONDITION ; 
 scalar_t__ SCSI_SENSE_BUFFERSIZE ; 
 int /*<<< orphan*/  SRP_RSP ; 
 int /*<<< orphan*/  SRP_RSP_FLAG_DIOVER ; 
 int /*<<< orphan*/  SRP_RSP_FLAG_RSPVALID ; 
 int /*<<< orphan*/  SRP_RSP_FLAG_SNSVALID ; 
 scalar_t__ SRP_RSP_SENSE_DATA_LEN ; 
 int /*<<< orphan*/  VIOSRP_SRP_FORMAT ; 
 int /*<<< orphan*/  V_DIOVER ; 
 int /*<<< orphan*/  V_LINKED ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (union viosrp_iu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  send_iu (struct iu_entry*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 union viosrp_iu* vio_iu (struct iu_entry*) ; 

__attribute__((used)) static int send_rsp(struct iu_entry *iue, struct scsi_cmnd *sc,
		    unsigned char status, unsigned char asc)
{
	union viosrp_iu *iu = vio_iu(iue);
	uint64_t tag = iu->srp.rsp.tag;

	/* If the linked bit is on and status is good */
	if (test_bit(V_LINKED, &iue->flags) && (status == NO_SENSE))
		status = 0x10;

	memset(iu, 0, sizeof(struct srp_rsp));
	iu->srp.rsp.opcode = SRP_RSP;
	iu->srp.rsp.req_lim_delta = 1;
	iu->srp.rsp.tag = tag;

	if (test_bit(V_DIOVER, &iue->flags))
		iu->srp.rsp.flags |= SRP_RSP_FLAG_DIOVER;

	iu->srp.rsp.data_in_res_cnt = 0;
	iu->srp.rsp.data_out_res_cnt = 0;

	iu->srp.rsp.flags &= ~SRP_RSP_FLAG_RSPVALID;

	iu->srp.rsp.resp_data_len = 0;
	iu->srp.rsp.status = status;
	if (status) {
		uint8_t *sense = iu->srp.rsp.data;

		if (sc) {
			iu->srp.rsp.flags |= SRP_RSP_FLAG_SNSVALID;
			iu->srp.rsp.sense_data_len = SCSI_SENSE_BUFFERSIZE;
			memcpy(sense, sc->sense_buffer, SCSI_SENSE_BUFFERSIZE);
		} else {
			iu->srp.rsp.status = SAM_STAT_CHECK_CONDITION;
			iu->srp.rsp.flags |= SRP_RSP_FLAG_SNSVALID;
			iu->srp.rsp.sense_data_len = SRP_RSP_SENSE_DATA_LEN;

			/* Valid bit and 'current errors' */
			sense[0] = (0x1 << 7 | 0x70);
			/* Sense key */
			sense[2] = status;
			/* Additional sense length */
			sense[7] = 0xa;	/* 10 bytes */
			/* Additional sense code */
			sense[12] = asc;
		}
	}

	send_iu(iue, sizeof(iu->srp.rsp) + SRP_RSP_SENSE_DATA_LEN,
		VIOSRP_SRP_FORMAT);

	return 0;
}