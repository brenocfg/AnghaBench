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
typedef  unsigned char u8 ;
struct se_cmd {unsigned char* t_task_cdb; int /*<<< orphan*/  data_length; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  GOOD ; 
 unsigned char NO_SENSE ; 
 int SE_SENSE_BUF ; 
 size_t SPC_ASCQ_KEY_OFFSET ; 
 size_t SPC_ASC_KEY_OFFSET ; 
 size_t SPC_SENSE_KEY_OFFSET ; 
 int /*<<< orphan*/  TCM_INVALID_CDB_FIELD ; 
 int /*<<< orphan*/  TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE ; 
 unsigned char UNIT_ATTENTION ; 
 int /*<<< orphan*/  core_scsi3_ua_clear_for_request_sense (struct se_cmd*,unsigned char*,unsigned char*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  min_t (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  target_complete_cmd (struct se_cmd*,int /*<<< orphan*/ ) ; 
 unsigned char* transport_kmap_data_sg (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_kunmap_data_sg (struct se_cmd*) ; 
 int /*<<< orphan*/  u32 ; 

__attribute__((used)) static sense_reason_t spc_emulate_request_sense(struct se_cmd *cmd)
{
	unsigned char *cdb = cmd->t_task_cdb;
	unsigned char *rbuf;
	u8 ua_asc = 0, ua_ascq = 0;
	unsigned char buf[SE_SENSE_BUF];

	memset(buf, 0, SE_SENSE_BUF);

	if (cdb[1] & 0x01) {
		pr_err("REQUEST_SENSE description emulation not"
			" supported\n");
		return TCM_INVALID_CDB_FIELD;
	}

	rbuf = transport_kmap_data_sg(cmd);
	if (!rbuf)
		return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	if (!core_scsi3_ua_clear_for_request_sense(cmd, &ua_asc, &ua_ascq)) {
		/*
		 * CURRENT ERROR, UNIT ATTENTION
		 */
		buf[0] = 0x70;
		buf[SPC_SENSE_KEY_OFFSET] = UNIT_ATTENTION;

		/*
		 * The Additional Sense Code (ASC) from the UNIT ATTENTION
		 */
		buf[SPC_ASC_KEY_OFFSET] = ua_asc;
		buf[SPC_ASCQ_KEY_OFFSET] = ua_ascq;
		buf[7] = 0x0A;
	} else {
		/*
		 * CURRENT ERROR, NO SENSE
		 */
		buf[0] = 0x70;
		buf[SPC_SENSE_KEY_OFFSET] = NO_SENSE;

		/*
		 * NO ADDITIONAL SENSE INFORMATION
		 */
		buf[SPC_ASC_KEY_OFFSET] = 0x00;
		buf[7] = 0x0A;
	}

	memcpy(rbuf, buf, min_t(u32, sizeof(buf), cmd->data_length));
	transport_kunmap_data_sg(cmd);

	target_complete_cmd(cmd, GOOD);
	return 0;
}