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
typedef  int /*<<< orphan*/  u32 ;
struct se_session {struct se_portal_group* se_tpg; } ;
struct se_portal_group {int /*<<< orphan*/  se_tpg_tfo; } ;
struct se_cmd {int unknown_data_length; int se_cmd_flags; scalar_t__ data_direction; scalar_t__ se_sess; scalar_t__ se_tfo; } ;
struct scatterlist {int offset; int /*<<< orphan*/  length; } ;
typedef  scalar_t__ sense_reason_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ DMA_FROM_DEVICE ; 
 int SCF_BIDI ; 
 int SCF_SCSI_DATA_CDB ; 
 int TARGET_SCF_ACK_KREF ; 
 int TARGET_SCF_BIDI_OP ; 
 int TARGET_SCF_UNKNOWN_SIZE ; 
 int /*<<< orphan*/  core_alua_check_nonop_delay (struct se_cmd*) ; 
 int in_interrupt () ; 
 unsigned char* kmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kunmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 int target_get_sess_cmd (struct se_session*,struct se_cmd*,int) ; 
 int /*<<< orphan*/  target_put_sess_cmd (struct se_session*,struct se_cmd*) ; 
 scalar_t__ target_setup_cmd_from_cdb (struct se_cmd*,unsigned char*) ; 
 scalar_t__ transport_generic_map_mem_to_cmd (struct se_cmd*,struct scatterlist*,int /*<<< orphan*/ ,struct scatterlist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transport_generic_request_failure (struct se_cmd*,scalar_t__) ; 
 int /*<<< orphan*/  transport_handle_cdb_direct (struct se_cmd*) ; 
 int /*<<< orphan*/  transport_init_se_cmd (struct se_cmd*,int /*<<< orphan*/ ,struct se_session*,int /*<<< orphan*/ ,int,int,unsigned char*) ; 
 scalar_t__ transport_lookup_cmd_lun (struct se_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transport_send_check_condition_and_sense (struct se_cmd*,scalar_t__,int /*<<< orphan*/ ) ; 

int target_submit_cmd_map_sgls(struct se_cmd *se_cmd, struct se_session *se_sess,
		unsigned char *cdb, unsigned char *sense, u32 unpacked_lun,
		u32 data_length, int task_attr, int data_dir, int flags,
		struct scatterlist *sgl, u32 sgl_count,
		struct scatterlist *sgl_bidi, u32 sgl_bidi_count)
{
	struct se_portal_group *se_tpg;
	sense_reason_t rc;
	int ret;

	se_tpg = se_sess->se_tpg;
	BUG_ON(!se_tpg);
	BUG_ON(se_cmd->se_tfo || se_cmd->se_sess);
	BUG_ON(in_interrupt());
	/*
	 * Initialize se_cmd for target operation.  From this point
	 * exceptions are handled by sending exception status via
	 * target_core_fabric_ops->queue_status() callback
	 */
	transport_init_se_cmd(se_cmd, se_tpg->se_tpg_tfo, se_sess,
				data_length, data_dir, task_attr, sense);
	if (flags & TARGET_SCF_UNKNOWN_SIZE)
		se_cmd->unknown_data_length = 1;
	/*
	 * Obtain struct se_cmd->cmd_kref reference and add new cmd to
	 * se_sess->sess_cmd_list.  A second kref_get here is necessary
	 * for fabrics using TARGET_SCF_ACK_KREF that expect a second
	 * kref_put() to happen during fabric packet acknowledgement.
	 */
	ret = target_get_sess_cmd(se_sess, se_cmd, (flags & TARGET_SCF_ACK_KREF));
	if (ret)
		return ret;
	/*
	 * Signal bidirectional data payloads to target-core
	 */
	if (flags & TARGET_SCF_BIDI_OP)
		se_cmd->se_cmd_flags |= SCF_BIDI;
	/*
	 * Locate se_lun pointer and attach it to struct se_cmd
	 */
	rc = transport_lookup_cmd_lun(se_cmd, unpacked_lun);
	if (rc) {
		transport_send_check_condition_and_sense(se_cmd, rc, 0);
		target_put_sess_cmd(se_sess, se_cmd);
		return 0;
	}

	rc = target_setup_cmd_from_cdb(se_cmd, cdb);
	if (rc != 0) {
		transport_generic_request_failure(se_cmd, rc);
		return 0;
	}
	/*
	 * When a non zero sgl_count has been passed perform SGL passthrough
	 * mapping for pre-allocated fabric memory instead of having target
	 * core perform an internal SGL allocation..
	 */
	if (sgl_count != 0) {
		BUG_ON(!sgl);

		/*
		 * A work-around for tcm_loop as some userspace code via
		 * scsi-generic do not memset their associated read buffers,
		 * so go ahead and do that here for type non-data CDBs.  Also
		 * note that this is currently guaranteed to be a single SGL
		 * for this case by target core in target_setup_cmd_from_cdb()
		 * -> transport_generic_cmd_sequencer().
		 */
		if (!(se_cmd->se_cmd_flags & SCF_SCSI_DATA_CDB) &&
		     se_cmd->data_direction == DMA_FROM_DEVICE) {
			unsigned char *buf = NULL;

			if (sgl)
				buf = kmap(sg_page(sgl)) + sgl->offset;

			if (buf) {
				memset(buf, 0, sgl->length);
				kunmap(sg_page(sgl));
			}
		}

		rc = transport_generic_map_mem_to_cmd(se_cmd, sgl, sgl_count,
				sgl_bidi, sgl_bidi_count);
		if (rc != 0) {
			transport_generic_request_failure(se_cmd, rc);
			return 0;
		}
	}
	/*
	 * Check if we need to delay processing because of ALUA
	 * Active/NonOptimized primary access state..
	 */
	core_alua_check_nonop_delay(se_cmd);

	transport_handle_cdb_direct(se_cmd);
	return 0;
}