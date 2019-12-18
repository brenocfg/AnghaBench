#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct se_tmr_req {TYPE_3__* task_cmd; } ;
struct se_portal_group {TYPE_4__* se_tpg_tfo; } ;
struct se_node_acl {int /*<<< orphan*/  initiatorname; } ;
struct TYPE_6__ {int emulate_tas; } ;
struct se_device {int dev_reservation_flags; TYPE_5__* transport; int /*<<< orphan*/  stats_lock; int /*<<< orphan*/  num_resets; int /*<<< orphan*/  dev_reservation_lock; int /*<<< orphan*/ * dev_reserved_node_acl; TYPE_1__ dev_attrib; } ;
struct se_cmd {int dummy; } ;
struct list_head {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {char* (* get_fabric_name ) () ;} ;
struct TYPE_8__ {TYPE_2__* se_sess; } ;
struct TYPE_7__ {struct se_portal_group* se_tpg; struct se_node_acl* se_node_acl; } ;

/* Variables and functions */
 int DRF_SPC2_RESERVATIONS ; 
 int /*<<< orphan*/  core_tmr_drain_state_list (struct se_device*,struct se_cmd*,struct se_node_acl*,int,struct list_head*) ; 
 int /*<<< orphan*/  core_tmr_drain_tmr_list (struct se_device*,struct se_tmr_req*,struct list_head*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 char* stub1 () ; 

int core_tmr_lun_reset(
        struct se_device *dev,
        struct se_tmr_req *tmr,
        struct list_head *preempt_and_abort_list,
        struct se_cmd *prout_cmd)
{
	struct se_node_acl *tmr_nacl = NULL;
	struct se_portal_group *tmr_tpg = NULL;
	int tas;
        /*
	 * TASK_ABORTED status bit, this is configurable via ConfigFS
	 * struct se_device attributes.  spc4r17 section 7.4.6 Control mode page
	 *
	 * A task aborted status (TAS) bit set to zero specifies that aborted
	 * tasks shall be terminated by the device server without any response
	 * to the application client. A TAS bit set to one specifies that tasks
	 * aborted by the actions of an I_T nexus other than the I_T nexus on
	 * which the command was received shall be completed with TASK ABORTED
	 * status (see SAM-4).
	 */
	tas = dev->dev_attrib.emulate_tas;
	/*
	 * Determine if this se_tmr is coming from a $FABRIC_MOD
	 * or struct se_device passthrough..
	 */
	if (tmr && tmr->task_cmd && tmr->task_cmd->se_sess) {
		tmr_nacl = tmr->task_cmd->se_sess->se_node_acl;
		tmr_tpg = tmr->task_cmd->se_sess->se_tpg;
		if (tmr_nacl && tmr_tpg) {
			pr_debug("LUN_RESET: TMR caller fabric: %s"
				" initiator port %s\n",
				tmr_tpg->se_tpg_tfo->get_fabric_name(),
				tmr_nacl->initiatorname);
		}
	}
	pr_debug("LUN_RESET: %s starting for [%s], tas: %d\n",
		(preempt_and_abort_list) ? "Preempt" : "TMR",
		dev->transport->name, tas);

	core_tmr_drain_tmr_list(dev, tmr, preempt_and_abort_list);
	core_tmr_drain_state_list(dev, prout_cmd, tmr_nacl, tas,
				preempt_and_abort_list);

	/*
	 * Clear any legacy SPC-2 reservation when called during
	 * LOGICAL UNIT RESET
	 */
	if (!preempt_and_abort_list &&
	     (dev->dev_reservation_flags & DRF_SPC2_RESERVATIONS)) {
		spin_lock(&dev->dev_reservation_lock);
		dev->dev_reserved_node_acl = NULL;
		dev->dev_reservation_flags &= ~DRF_SPC2_RESERVATIONS;
		spin_unlock(&dev->dev_reservation_lock);
		pr_debug("LUN_RESET: SCSI-2 Released reservation\n");
	}

	spin_lock_irq(&dev->stats_lock);
	dev->num_resets++;
	spin_unlock_irq(&dev->stats_lock);

	pr_debug("LUN_RESET: %s for [%s] Complete\n",
			(preempt_and_abort_list) ? "Preempt" : "TMR",
			dev->transport->name);
	return 0;
}