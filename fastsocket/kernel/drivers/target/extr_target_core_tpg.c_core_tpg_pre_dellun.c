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
typedef  int u32 ;
struct se_portal_group {int /*<<< orphan*/  tpg_lun_lock; TYPE_1__* se_tpg_tfo; struct se_lun** tpg_lun_list; } ;
struct se_lun {scalar_t__ lun_status; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* tpg_get_tag ) (struct se_portal_group*) ;int /*<<< orphan*/  (* get_fabric_name ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  EOVERFLOW ; 
 struct se_lun* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ TRANSPORT_LUN_STATUS_ACTIVE ; 
 int TRANSPORT_MAX_LUNS_PER_TPG ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int,int,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 (struct se_portal_group*) ; 
 int /*<<< orphan*/  stub3 () ; 
 int /*<<< orphan*/  stub4 (struct se_portal_group*) ; 

struct se_lun *core_tpg_pre_dellun(
	struct se_portal_group *tpg,
	u32 unpacked_lun)
{
	struct se_lun *lun;

	if (unpacked_lun > (TRANSPORT_MAX_LUNS_PER_TPG-1)) {
		pr_err("%s LUN: %u exceeds TRANSPORT_MAX_LUNS_PER_TPG"
			"-1: %u for Target Portal Group: %u\n",
			tpg->se_tpg_tfo->get_fabric_name(), unpacked_lun,
			TRANSPORT_MAX_LUNS_PER_TPG-1,
			tpg->se_tpg_tfo->tpg_get_tag(tpg));
		return ERR_PTR(-EOVERFLOW);
	}

	spin_lock(&tpg->tpg_lun_lock);
	lun = tpg->tpg_lun_list[unpacked_lun];
	if (lun->lun_status != TRANSPORT_LUN_STATUS_ACTIVE) {
		pr_err("%s Logical Unit Number: %u is not active on"
			" Target Portal Group: %u, ignoring request.\n",
			tpg->se_tpg_tfo->get_fabric_name(), unpacked_lun,
			tpg->se_tpg_tfo->tpg_get_tag(tpg));
		spin_unlock(&tpg->tpg_lun_lock);
		return ERR_PTR(-ENODEV);
	}
	spin_unlock(&tpg->tpg_lun_lock);

	return lun;
}