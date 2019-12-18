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
struct se_portal_group {int /*<<< orphan*/  tpg_lun_lock; struct se_lun** tpg_lun_list; } ;
struct se_lun {scalar_t__ lun_status; int /*<<< orphan*/  unpacked_lun; int /*<<< orphan*/ * lun_se_dev; } ;

/* Variables and functions */
 scalar_t__ TRANSPORT_LUN_STATUS_ACTIVE ; 
 int TRANSPORT_MAX_LUNS_PER_TPG ; 
 int /*<<< orphan*/  core_dev_del_lun (struct se_portal_group*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void core_tpg_clear_object_luns(struct se_portal_group *tpg)
{
	int i;
	struct se_lun *lun;

	spin_lock(&tpg->tpg_lun_lock);
	for (i = 0; i < TRANSPORT_MAX_LUNS_PER_TPG; i++) {
		lun = tpg->tpg_lun_list[i];

		if ((lun->lun_status != TRANSPORT_LUN_STATUS_ACTIVE) ||
		    (lun->lun_se_dev == NULL))
			continue;

		spin_unlock(&tpg->tpg_lun_lock);
		core_dev_del_lun(tpg, lun->unpacked_lun);
		spin_lock(&tpg->tpg_lun_lock);
	}
	spin_unlock(&tpg->tpg_lun_lock);
}