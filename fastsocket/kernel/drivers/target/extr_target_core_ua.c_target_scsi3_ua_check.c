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
struct se_session {struct se_node_acl* se_node_acl; } ;
struct se_node_acl {struct se_dev_entry** device_list; } ;
struct se_dev_entry {int /*<<< orphan*/  ua_count; } ;
struct se_cmd {size_t orig_fe_lun; int* t_task_cdb; struct se_session* se_sess; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;

/* Variables and functions */
#define  INQUIRY 130 
#define  REPORT_LUNS 129 
#define  REQUEST_SENSE 128 
 int /*<<< orphan*/  TCM_CHECK_CONDITION_UNIT_ATTENTION ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 

sense_reason_t
target_scsi3_ua_check(struct se_cmd *cmd)
{
	struct se_dev_entry *deve;
	struct se_session *sess = cmd->se_sess;
	struct se_node_acl *nacl;

	if (!sess)
		return 0;

	nacl = sess->se_node_acl;
	if (!nacl)
		return 0;

	deve = nacl->device_list[cmd->orig_fe_lun];
	if (!atomic_read(&deve->ua_count))
		return 0;
	/*
	 * From sam4r14, section 5.14 Unit attention condition:
	 *
	 * a) if an INQUIRY command enters the enabled command state, the
	 *    device server shall process the INQUIRY command and shall neither
	 *    report nor clear any unit attention condition;
	 * b) if a REPORT LUNS command enters the enabled command state, the
	 *    device server shall process the REPORT LUNS command and shall not
	 *    report any unit attention condition;
	 * e) if a REQUEST SENSE command enters the enabled command state while
	 *    a unit attention condition exists for the SCSI initiator port
	 *    associated with the I_T nexus on which the REQUEST SENSE command
	 *    was received, then the device server shall process the command
	 *    and either:
	 */
	switch (cmd->t_task_cdb[0]) {
	case INQUIRY:
	case REPORT_LUNS:
	case REQUEST_SENSE:
		return 0;
	default:
		return TCM_CHECK_CONDITION_UNIT_ATTENTION;
	}
}