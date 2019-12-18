#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct se_session {TYPE_3__* se_tpg; TYPE_1__* se_node_acl; } ;
struct se_lun {int /*<<< orphan*/  lun_cmd_lock; int /*<<< orphan*/  lun_cmd_list; struct se_device* lun_se_dev; } ;
struct se_device {int /*<<< orphan*/  stats_lock; int /*<<< orphan*/  read_bytes; int /*<<< orphan*/  write_bytes; int /*<<< orphan*/  num_cmds; } ;
struct se_dev_entry {int lun_flags; int /*<<< orphan*/  pr_res_key; struct se_lun* se_lun; int /*<<< orphan*/  deve_cmds; int /*<<< orphan*/  read_bytes; int /*<<< orphan*/  write_bytes; int /*<<< orphan*/  total_bytes; int /*<<< orphan*/  total_cmds; } ;
struct se_cmd {scalar_t__ data_direction; size_t orig_fe_lun; int /*<<< orphan*/  se_lun_node; scalar_t__ data_length; struct se_device* se_dev; int /*<<< orphan*/  se_cmd_flags; struct se_lun* se_lun; TYPE_2__* se_tfo; int /*<<< orphan*/  pr_res_key; struct se_dev_entry* se_deve; struct se_session* se_sess; } ;
typedef  int /*<<< orphan*/  sense_reason_t ;
struct TYPE_6__ {struct se_lun tpg_virt_lun0; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_fabric_name ) () ;} ;
struct TYPE_4__ {int /*<<< orphan*/  device_list_lock; struct se_dev_entry** device_list; } ;

/* Variables and functions */
 scalar_t__ DMA_FROM_DEVICE ; 
 scalar_t__ DMA_NONE ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int /*<<< orphan*/  SCF_SE_LUN_CMD ; 
 int /*<<< orphan*/  TCM_NON_EXISTENT_LUN ; 
 int /*<<< orphan*/  TCM_WRITE_PROTECTED ; 
 int TRANSPORT_LUNFLAGS_INITIATOR_ACCESS ; 
 int TRANSPORT_LUNFLAGS_READ_ONLY ; 
 size_t TRANSPORT_MAX_LUNS_PER_TPG ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 

sense_reason_t
transport_lookup_cmd_lun(struct se_cmd *se_cmd, u32 unpacked_lun)
{
	struct se_lun *se_lun = NULL;
	struct se_session *se_sess = se_cmd->se_sess;
	struct se_device *dev;
	unsigned long flags;

	if (unpacked_lun >= TRANSPORT_MAX_LUNS_PER_TPG)
		return TCM_NON_EXISTENT_LUN;

	spin_lock_irqsave(&se_sess->se_node_acl->device_list_lock, flags);
	se_cmd->se_deve = se_sess->se_node_acl->device_list[unpacked_lun];
	if (se_cmd->se_deve->lun_flags & TRANSPORT_LUNFLAGS_INITIATOR_ACCESS) {
		struct se_dev_entry *deve = se_cmd->se_deve;

		deve->total_cmds++;
		deve->total_bytes += se_cmd->data_length;

		if ((se_cmd->data_direction == DMA_TO_DEVICE) &&
		    (deve->lun_flags & TRANSPORT_LUNFLAGS_READ_ONLY)) {
			pr_err("TARGET_CORE[%s]: Detected WRITE_PROTECTED LUN"
				" Access for 0x%08x\n",
				se_cmd->se_tfo->get_fabric_name(),
				unpacked_lun);
			spin_unlock_irqrestore(&se_sess->se_node_acl->device_list_lock, flags);
			return TCM_WRITE_PROTECTED;
		}

		if (se_cmd->data_direction == DMA_TO_DEVICE)
			deve->write_bytes += se_cmd->data_length;
		else if (se_cmd->data_direction == DMA_FROM_DEVICE)
			deve->read_bytes += se_cmd->data_length;

		deve->deve_cmds++;

		se_lun = deve->se_lun;
		se_cmd->se_lun = deve->se_lun;
		se_cmd->pr_res_key = deve->pr_res_key;
		se_cmd->orig_fe_lun = unpacked_lun;
		se_cmd->se_cmd_flags |= SCF_SE_LUN_CMD;
	}
	spin_unlock_irqrestore(&se_sess->se_node_acl->device_list_lock, flags);

	if (!se_lun) {
		/*
		 * Use the se_portal_group->tpg_virt_lun0 to allow for
		 * REPORT_LUNS, et al to be returned when no active
		 * MappedLUN=0 exists for this Initiator Port.
		 */
		if (unpacked_lun != 0) {
			pr_err("TARGET_CORE[%s]: Detected NON_EXISTENT_LUN"
				" Access for 0x%08x\n",
				se_cmd->se_tfo->get_fabric_name(),
				unpacked_lun);
			return TCM_NON_EXISTENT_LUN;
		}
		/*
		 * Force WRITE PROTECT for virtual LUN 0
		 */
		if ((se_cmd->data_direction != DMA_FROM_DEVICE) &&
		    (se_cmd->data_direction != DMA_NONE))
			return TCM_WRITE_PROTECTED;

		se_lun = &se_sess->se_tpg->tpg_virt_lun0;
		se_cmd->se_lun = &se_sess->se_tpg->tpg_virt_lun0;
		se_cmd->orig_fe_lun = 0;
		se_cmd->se_cmd_flags |= SCF_SE_LUN_CMD;
	}

	/* Directly associate cmd with se_dev */
	se_cmd->se_dev = se_lun->lun_se_dev;

	/* TODO: get rid of this and use atomics for stats */
	dev = se_lun->lun_se_dev;
	spin_lock_irqsave(&dev->stats_lock, flags);
	dev->num_cmds++;
	if (se_cmd->data_direction == DMA_TO_DEVICE)
		dev->write_bytes += se_cmd->data_length;
	else if (se_cmd->data_direction == DMA_FROM_DEVICE)
		dev->read_bytes += se_cmd->data_length;
	spin_unlock_irqrestore(&dev->stats_lock, flags);

	spin_lock_irqsave(&se_lun->lun_cmd_lock, flags);
	list_add_tail(&se_cmd->se_lun_node, &se_lun->lun_cmd_list);
	spin_unlock_irqrestore(&se_lun->lun_cmd_lock, flags);

	return 0;
}