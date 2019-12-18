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
struct se_tmr_req {TYPE_3__* tmr_dev; int /*<<< orphan*/  tmr_list; struct se_lun* tmr_lun; } ;
struct se_session {TYPE_1__* se_node_acl; } ;
struct se_lun {TYPE_3__* lun_se_dev; } ;
struct se_dev_entry {int lun_flags; int /*<<< orphan*/  pr_res_key; struct se_lun* se_lun; } ;
struct se_cmd {size_t orig_fe_lun; TYPE_3__* se_dev; TYPE_2__* se_tfo; int /*<<< orphan*/  pr_res_key; struct se_lun* se_lun; struct se_dev_entry* se_deve; struct se_tmr_req* se_tmr_req; struct se_session* se_sess; } ;
struct TYPE_6__ {int /*<<< orphan*/  se_tmr_lock; int /*<<< orphan*/  dev_tmr_list; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_fabric_name ) () ;} ;
struct TYPE_4__ {int /*<<< orphan*/  device_list_lock; struct se_dev_entry** device_list; } ;

/* Variables and functions */
 int ENODEV ; 
 int TRANSPORT_LUNFLAGS_INITIATOR_ACCESS ; 
 size_t TRANSPORT_MAX_LUNS_PER_TPG ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 () ; 

int transport_lookup_tmr_lun(struct se_cmd *se_cmd, u32 unpacked_lun)
{
	struct se_dev_entry *deve;
	struct se_lun *se_lun = NULL;
	struct se_session *se_sess = se_cmd->se_sess;
	struct se_tmr_req *se_tmr = se_cmd->se_tmr_req;
	unsigned long flags;

	if (unpacked_lun >= TRANSPORT_MAX_LUNS_PER_TPG)
		return -ENODEV;

	spin_lock_irqsave(&se_sess->se_node_acl->device_list_lock, flags);
	se_cmd->se_deve = se_sess->se_node_acl->device_list[unpacked_lun];
	deve = se_cmd->se_deve;

	if (deve->lun_flags & TRANSPORT_LUNFLAGS_INITIATOR_ACCESS) {
		se_tmr->tmr_lun = deve->se_lun;
		se_cmd->se_lun = deve->se_lun;
		se_lun = deve->se_lun;
		se_cmd->pr_res_key = deve->pr_res_key;
		se_cmd->orig_fe_lun = unpacked_lun;
	}
	spin_unlock_irqrestore(&se_sess->se_node_acl->device_list_lock, flags);

	if (!se_lun) {
		pr_debug("TARGET_CORE[%s]: Detected NON_EXISTENT_LUN"
			" Access for 0x%08x\n",
			se_cmd->se_tfo->get_fabric_name(),
			unpacked_lun);
		return -ENODEV;
	}

	/* Directly associate cmd with se_dev */
	se_cmd->se_dev = se_lun->lun_se_dev;
	se_tmr->tmr_dev = se_lun->lun_se_dev;

	spin_lock_irqsave(&se_tmr->tmr_dev->se_tmr_lock, flags);
	list_add_tail(&se_tmr->tmr_list, &se_tmr->tmr_dev->dev_tmr_list);
	spin_unlock_irqrestore(&se_tmr->tmr_dev->se_tmr_lock, flags);

	return 0;
}