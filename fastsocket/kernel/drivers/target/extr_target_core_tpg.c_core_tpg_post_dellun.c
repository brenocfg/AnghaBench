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
struct se_portal_group {int /*<<< orphan*/  tpg_lun_lock; } ;
struct se_lun {int /*<<< orphan*/  lun_status; int /*<<< orphan*/  lun_se_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRANSPORT_LUN_STATUS_FREE ; 
 int /*<<< orphan*/  core_dev_unexport (int /*<<< orphan*/ ,struct se_portal_group*,struct se_lun*) ; 
 int /*<<< orphan*/  core_tpg_shutdown_lun (struct se_portal_group*,struct se_lun*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int core_tpg_post_dellun(
	struct se_portal_group *tpg,
	struct se_lun *lun)
{
	core_tpg_shutdown_lun(tpg, lun);

	core_dev_unexport(lun->lun_se_dev, tpg, lun);

	spin_lock(&tpg->tpg_lun_lock);
	lun->lun_status = TRANSPORT_LUN_STATUS_FREE;
	spin_unlock(&tpg->tpg_lun_lock);

	return 0;
}