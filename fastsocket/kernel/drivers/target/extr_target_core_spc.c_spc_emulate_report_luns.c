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
typedef  size_t u32 ;
struct se_session {TYPE_1__* se_node_acl; } ;
struct se_dev_entry {int lun_flags; int /*<<< orphan*/  mapped_lun; } ;
struct se_cmd {int data_length; struct se_session* se_sess; } ;
struct scsi_lun {int dummy; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
struct TYPE_2__ {int /*<<< orphan*/  device_list_lock; struct se_dev_entry** device_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GOOD ; 
 int /*<<< orphan*/  TCM_INVALID_CDB_FIELD ; 
 int /*<<< orphan*/  TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE ; 
 int TRANSPORT_LUNFLAGS_INITIATOR_ACCESS ; 
 size_t TRANSPORT_MAX_LUNS_PER_TPG ; 
 int /*<<< orphan*/  int_to_scsilun (int /*<<< orphan*/ ,struct scsi_lun*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_complete_cmd (struct se_cmd*,int /*<<< orphan*/ ) ; 
 unsigned char* transport_kmap_data_sg (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_kunmap_data_sg (struct se_cmd*) ; 

sense_reason_t spc_emulate_report_luns(struct se_cmd *cmd)
{
	struct se_dev_entry *deve;
	struct se_session *sess = cmd->se_sess;
	unsigned char *buf;
	u32 lun_count = 0, offset = 8, i;

	if (cmd->data_length < 16) {
		pr_warn("REPORT LUNS allocation length %u too small\n",
			cmd->data_length);
		return TCM_INVALID_CDB_FIELD;
	}

	buf = transport_kmap_data_sg(cmd);
	if (!buf)
		return TCM_LOGICAL_UNIT_COMMUNICATION_FAILURE;

	/*
	 * If no struct se_session pointer is present, this struct se_cmd is
	 * coming via a target_core_mod PASSTHROUGH op, and not through
	 * a $FABRIC_MOD.  In that case, report LUN=0 only.
	 */
	if (!sess) {
		int_to_scsilun(0, (struct scsi_lun *)&buf[offset]);
		lun_count = 1;
		goto done;
	}

	spin_lock_irq(&sess->se_node_acl->device_list_lock);
	for (i = 0; i < TRANSPORT_MAX_LUNS_PER_TPG; i++) {
		deve = sess->se_node_acl->device_list[i];
		if (!(deve->lun_flags & TRANSPORT_LUNFLAGS_INITIATOR_ACCESS))
			continue;
		/*
		 * We determine the correct LUN LIST LENGTH even once we
		 * have reached the initial allocation length.
		 * See SPC2-R20 7.19.
		 */
		lun_count++;
		if ((offset + 8) > cmd->data_length)
			continue;

		int_to_scsilun(deve->mapped_lun, (struct scsi_lun *)&buf[offset]);
		offset += 8;
	}
	spin_unlock_irq(&sess->se_node_acl->device_list_lock);

	/*
	 * See SPC3 r07, page 159.
	 */
done:
	lun_count *= 8;
	buf[0] = ((lun_count >> 24) & 0xff);
	buf[1] = ((lun_count >> 16) & 0xff);
	buf[2] = ((lun_count >> 8) & 0xff);
	buf[3] = (lun_count & 0xff);
	transport_kunmap_data_sg(cmd);

	target_complete_cmd(cmd, GOOD);
	return 0;
}