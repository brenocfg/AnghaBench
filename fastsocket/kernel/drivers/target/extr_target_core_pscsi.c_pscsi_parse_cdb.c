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
struct se_cmd {unsigned char* t_task_cdb; int se_cmd_flags; int /*<<< orphan*/  execute_cmd; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;

/* Variables and functions */
#define  READ_10 137 
#define  READ_12 136 
#define  READ_16 135 
#define  READ_6 134 
#define  REPORT_LUNS 133 
 int SCF_BIDI ; 
 int SCF_SCSI_DATA_CDB ; 
 int /*<<< orphan*/  TCM_UNSUPPORTED_SCSI_OPCODE ; 
#define  WRITE_10 132 
#define  WRITE_12 131 
#define  WRITE_16 130 
#define  WRITE_6 129 
#define  WRITE_VERIFY 128 
 int /*<<< orphan*/  pscsi_clear_cdb_lun (unsigned char*) ; 
 int /*<<< orphan*/  pscsi_execute_cmd ; 
 int /*<<< orphan*/  spc_emulate_report_luns ; 

__attribute__((used)) static sense_reason_t
pscsi_parse_cdb(struct se_cmd *cmd)
{
	unsigned char *cdb = cmd->t_task_cdb;

	if (cmd->se_cmd_flags & SCF_BIDI)
		return TCM_UNSUPPORTED_SCSI_OPCODE;

	pscsi_clear_cdb_lun(cdb);

	/*
	 * For REPORT LUNS we always need to emulate the response, for everything
	 * else the default for pSCSI is to pass the command to the underlying
	 * LLD / physical hardware.
	 */
	switch (cdb[0]) {
	case REPORT_LUNS:
		cmd->execute_cmd = spc_emulate_report_luns;
		return 0;
	case READ_6:
	case READ_10:
	case READ_12:
	case READ_16:
	case WRITE_6:
	case WRITE_10:
	case WRITE_12:
	case WRITE_16:
	case WRITE_VERIFY:
		cmd->se_cmd_flags |= SCF_SCSI_DATA_CDB;
		/* FALLTHROUGH*/
	default:
		cmd->execute_cmd = pscsi_execute_cmd;
		return 0;
	}
}