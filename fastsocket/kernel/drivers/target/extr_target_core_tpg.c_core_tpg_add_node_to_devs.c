#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct se_portal_group {int /*<<< orphan*/  tpg_lun_lock; TYPE_2__* se_tpg_tfo; struct se_lun** tpg_lun_list; } ;
struct se_node_acl {int dummy; } ;
struct se_lun {scalar_t__ lun_status; int /*<<< orphan*/  unpacked_lun; struct se_device* lun_se_dev; } ;
struct se_device {TYPE_1__* transport; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* tpg_get_tag ) (struct se_portal_group*) ;int /*<<< orphan*/  (* get_fabric_name ) () ;int /*<<< orphan*/  (* tpg_check_demo_mode_write_protect ) (struct se_portal_group*) ;} ;
struct TYPE_3__ {scalar_t__ (* get_device_type ) (struct se_device*) ;} ;

/* Variables and functions */
 scalar_t__ TRANSPORT_LUNFLAGS_READ_ONLY ; 
 scalar_t__ TRANSPORT_LUNFLAGS_READ_WRITE ; 
 scalar_t__ TRANSPORT_LUN_STATUS_ACTIVE ; 
 int TRANSPORT_MAX_LUNS_PER_TPG ; 
 scalar_t__ TYPE_DISK ; 
 int /*<<< orphan*/  core_enable_device_list_for_node (struct se_lun*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,struct se_node_acl*,struct se_portal_group*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct se_portal_group*) ; 
 scalar_t__ stub2 (struct se_device*) ; 
 int /*<<< orphan*/  stub3 () ; 
 int /*<<< orphan*/  stub4 (struct se_portal_group*) ; 

void core_tpg_add_node_to_devs(
	struct se_node_acl *acl,
	struct se_portal_group *tpg)
{
	int i = 0;
	u32 lun_access = 0;
	struct se_lun *lun;
	struct se_device *dev;

	spin_lock(&tpg->tpg_lun_lock);
	for (i = 0; i < TRANSPORT_MAX_LUNS_PER_TPG; i++) {
		lun = tpg->tpg_lun_list[i];
		if (lun->lun_status != TRANSPORT_LUN_STATUS_ACTIVE)
			continue;

		spin_unlock(&tpg->tpg_lun_lock);

		dev = lun->lun_se_dev;
		/*
		 * By default in LIO-Target $FABRIC_MOD,
		 * demo_mode_write_protect is ON, or READ_ONLY;
		 */
		if (!tpg->se_tpg_tfo->tpg_check_demo_mode_write_protect(tpg)) {
			lun_access = TRANSPORT_LUNFLAGS_READ_WRITE;
		} else {
			/*
			 * Allow only optical drives to issue R/W in default RO
			 * demo mode.
			 */
			if (dev->transport->get_device_type(dev) == TYPE_DISK)
				lun_access = TRANSPORT_LUNFLAGS_READ_ONLY;
			else
				lun_access = TRANSPORT_LUNFLAGS_READ_WRITE;
		}

		pr_debug("TARGET_CORE[%s]->TPG[%u]_LUN[%u] - Adding %s"
			" access for LUN in Demo Mode\n",
			tpg->se_tpg_tfo->get_fabric_name(),
			tpg->se_tpg_tfo->tpg_get_tag(tpg), lun->unpacked_lun,
			(lun_access == TRANSPORT_LUNFLAGS_READ_WRITE) ?
			"READ-WRITE" : "READ-ONLY");

		core_enable_device_list_for_node(lun, NULL, lun->unpacked_lun,
				lun_access, acl, tpg);
		spin_lock(&tpg->tpg_lun_lock);
	}
	spin_unlock(&tpg->tpg_lun_lock);
}