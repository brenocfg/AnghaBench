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
typedef  int u16 ;
struct t10_reservation {scalar_t__ pr_aptpl_active; } ;
struct se_device {struct t10_reservation t10_pr; } ;
struct se_cmd {int data_length; struct se_device* se_dev; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;

/* Variables and functions */
 int /*<<< orphan*/  TCM_INVALID_CDB_FIELD ; 
 int /*<<< orphan*/  TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 unsigned char* transport_kmap_data_sg (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_kunmap_data_sg (struct se_cmd*) ; 

__attribute__((used)) static sense_reason_t
core_scsi3_pri_report_capabilities(struct se_cmd *cmd)
{
	struct se_device *dev = cmd->se_dev;
	struct t10_reservation *pr_tmpl = &dev->t10_pr;
	unsigned char *buf;
	u16 add_len = 8; /* Hardcoded to 8. */

	if (cmd->data_length < 6) {
		pr_err("PRIN SA REPORT_CAPABILITIES SCSI Data Length:"
			" %u too small\n", cmd->data_length);
		return TCM_INVALID_CDB_FIELD;
	}

	buf = transport_kmap_data_sg(cmd);
	if (!buf)
		return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	buf[0] = ((add_len << 8) & 0xff);
	buf[1] = (add_len & 0xff);
	buf[2] |= 0x10; /* CRH: Compatible Reservation Hanlding bit. */
	buf[2] |= 0x08; /* SIP_C: Specify Initiator Ports Capable bit */
	buf[2] |= 0x04; /* ATP_C: All Target Ports Capable bit */
	buf[2] |= 0x01; /* PTPL_C: Persistence across Target Power Loss bit */
	/*
	 * We are filling in the PERSISTENT RESERVATION TYPE MASK below, so
	 * set the TMV: Task Mask Valid bit.
	 */
	buf[3] |= 0x80;
	/*
	 * Change ALLOW COMMANDs to 0x20 or 0x40 later from Table 166
	 */
	buf[3] |= 0x10; /* ALLOW COMMANDs field 001b */
	/*
	 * PTPL_A: Persistence across Target Power Loss Active bit
	 */
	if (pr_tmpl->pr_aptpl_active)
		buf[3] |= 0x01;
	/*
	 * Setup the PERSISTENT RESERVATION TYPE MASK from Table 167
	 */
	buf[4] |= 0x80; /* PR_TYPE_EXCLUSIVE_ACCESS_ALLREG */
	buf[4] |= 0x40; /* PR_TYPE_EXCLUSIVE_ACCESS_REGONLY */
	buf[4] |= 0x20; /* PR_TYPE_WRITE_EXCLUSIVE_REGONLY */
	buf[4] |= 0x08; /* PR_TYPE_EXCLUSIVE_ACCESS */
	buf[4] |= 0x02; /* PR_TYPE_WRITE_EXCLUSIVE */
	buf[5] |= 0x01; /* PR_TYPE_EXCLUSIVE_ACCESS_ALLREG */

	transport_kunmap_data_sg(cmd);

	return 0;
}