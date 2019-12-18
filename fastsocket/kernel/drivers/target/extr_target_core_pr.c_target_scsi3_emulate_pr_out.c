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
typedef  int /*<<< orphan*/  u64 ;
struct se_cmd {unsigned char* t_task_cdb; int data_length; int /*<<< orphan*/  se_sess; TYPE_1__* se_dev; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
struct TYPE_2__ {int dev_reservation_flags; } ;

/* Variables and functions */
 int DRF_SPC2_RESERVATIONS ; 
 int /*<<< orphan*/  GOOD ; 
#define  PRO_CLEAR 135 
#define  PRO_PREEMPT 134 
#define  PRO_PREEMPT_AND_ABORT 133 
#define  PRO_REGISTER 132 
#define  PRO_REGISTER_AND_IGNORE_EXISTING_KEY 131 
#define  PRO_REGISTER_AND_MOVE 130 
#define  PRO_RELEASE 129 
#define  PRO_RESERVE 128 
 int /*<<< orphan*/  TCM_INVALID_CDB_FIELD ; 
 int /*<<< orphan*/  TCM_INVALID_PARAMETER_LIST ; 
 int /*<<< orphan*/  TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE ; 
 int /*<<< orphan*/  TCM_RESERVATION_CONFLICT ; 
 int /*<<< orphan*/  core_scsi3_emulate_pro_clear (struct se_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_scsi3_emulate_pro_preempt (struct se_cmd*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  core_scsi3_emulate_pro_register (struct se_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  core_scsi3_emulate_pro_register_and_move (struct se_cmd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  core_scsi3_emulate_pro_release (struct se_cmd*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_scsi3_emulate_pro_reserve (struct se_cmd*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  core_scsi3_extract_reservation_key (unsigned char*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int /*<<< orphan*/  target_complete_cmd (struct se_cmd*,int /*<<< orphan*/ ) ; 
 unsigned char* transport_kmap_data_sg (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_kunmap_data_sg (struct se_cmd*) ; 

sense_reason_t
target_scsi3_emulate_pr_out(struct se_cmd *cmd)
{
	unsigned char *cdb = &cmd->t_task_cdb[0];
	unsigned char *buf;
	u64 res_key, sa_res_key;
	int sa, scope, type, aptpl;
	int spec_i_pt = 0, all_tg_pt = 0, unreg = 0;
	sense_reason_t ret;

	/*
	 * Following spc2r20 5.5.1 Reservations overview:
	 *
	 * If a logical unit has been reserved by any RESERVE command and is
	 * still reserved by any initiator, all PERSISTENT RESERVE IN and all
	 * PERSISTENT RESERVE OUT commands shall conflict regardless of
	 * initiator or service action and shall terminate with a RESERVATION
	 * CONFLICT status.
	 */
	if (cmd->se_dev->dev_reservation_flags & DRF_SPC2_RESERVATIONS) {
		pr_err("Received PERSISTENT_RESERVE CDB while legacy"
			" SPC-2 reservation is held, returning"
			" RESERVATION_CONFLICT\n");
		return TCM_RESERVATION_CONFLICT;
	}

	/*
	 * FIXME: A NULL struct se_session pointer means an this is not coming from
	 * a $FABRIC_MOD's nexus, but from internal passthrough ops.
	 */
	if (!cmd->se_sess)
		return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	if (cmd->data_length < 24) {
		pr_warn("SPC-PR: Received PR OUT parameter list"
			" length too small: %u\n", cmd->data_length);
		return TCM_INVALID_PARAMETER_LIST;
	}

	/*
	 * From the PERSISTENT_RESERVE_OUT command descriptor block (CDB)
	 */
	sa = (cdb[1] & 0x1f);
	scope = (cdb[2] & 0xf0);
	type = (cdb[2] & 0x0f);

	buf = transport_kmap_data_sg(cmd);
	if (!buf)
		return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	/*
	 * From PERSISTENT_RESERVE_OUT parameter list (payload)
	 */
	res_key = core_scsi3_extract_reservation_key(&buf[0]);
	sa_res_key = core_scsi3_extract_reservation_key(&buf[8]);
	/*
	 * REGISTER_AND_MOVE uses a different SA parameter list containing
	 * SCSI TransportIDs.
	 */
	if (sa != PRO_REGISTER_AND_MOVE) {
		spec_i_pt = (buf[20] & 0x08);
		all_tg_pt = (buf[20] & 0x04);
		aptpl = (buf[20] & 0x01);
	} else {
		aptpl = (buf[17] & 0x01);
		unreg = (buf[17] & 0x02);
	}
	transport_kunmap_data_sg(cmd);
	buf = NULL;

	/*
	 * SPEC_I_PT=1 is only valid for Service action: REGISTER
	 */
	if (spec_i_pt && ((cdb[1] & 0x1f) != PRO_REGISTER))
		return TCM_INVALID_PARAMETER_LIST;

	/*
	 * From spc4r17 section 6.14:
	 *
	 * If the SPEC_I_PT bit is set to zero, the service action is not
	 * REGISTER AND MOVE, and the parameter list length is not 24, then
	 * the command shall be terminated with CHECK CONDITION status, with
	 * the sense key set to ILLEGAL REQUEST, and the additional sense
	 * code set to PARAMETER LIST LENGTH ERROR.
	 */
	if (!spec_i_pt && ((cdb[1] & 0x1f) != PRO_REGISTER_AND_MOVE) &&
	    (cmd->data_length != 24)) {
		pr_warn("SPC-PR: Received PR OUT illegal parameter"
			" list length: %u\n", cmd->data_length);
		return TCM_INVALID_PARAMETER_LIST;
	}

	/*
	 * (core_scsi3_emulate_pro_* function parameters
	 * are defined by spc4r17 Table 174:
	 * PERSISTENT_RESERVE_OUT service actions and valid parameters.
	 */
	switch (sa) {
	case PRO_REGISTER:
		ret = core_scsi3_emulate_pro_register(cmd,
			res_key, sa_res_key, aptpl, all_tg_pt, spec_i_pt, 0);
		break;
	case PRO_RESERVE:
		ret = core_scsi3_emulate_pro_reserve(cmd, type, scope, res_key);
		break;
	case PRO_RELEASE:
		ret = core_scsi3_emulate_pro_release(cmd, type, scope, res_key);
		break;
	case PRO_CLEAR:
		ret = core_scsi3_emulate_pro_clear(cmd, res_key);
		break;
	case PRO_PREEMPT:
		ret = core_scsi3_emulate_pro_preempt(cmd, type, scope,
					res_key, sa_res_key, 0);
		break;
	case PRO_PREEMPT_AND_ABORT:
		ret = core_scsi3_emulate_pro_preempt(cmd, type, scope,
					res_key, sa_res_key, 1);
		break;
	case PRO_REGISTER_AND_IGNORE_EXISTING_KEY:
		ret = core_scsi3_emulate_pro_register(cmd,
			0, sa_res_key, aptpl, all_tg_pt, spec_i_pt, 1);
		break;
	case PRO_REGISTER_AND_MOVE:
		ret = core_scsi3_emulate_pro_register_and_move(cmd, res_key,
				sa_res_key, aptpl, unreg);
		break;
	default:
		pr_err("Unknown PERSISTENT_RESERVE_OUT service"
			" action: 0x%02x\n", cdb[1] & 0x1f);
		return TCM_INVALID_CDB_FIELD;
	}

	if (!ret)
		target_complete_cmd(cmd, GOOD);
	return ret;
}