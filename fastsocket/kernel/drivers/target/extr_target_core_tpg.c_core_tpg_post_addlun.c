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
struct se_portal_group {int /*<<< orphan*/  tpg_lun_lock; } ;
struct se_lun {int /*<<< orphan*/  lun_status; int /*<<< orphan*/  lun_access; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRANSPORT_LUN_STATUS_ACTIVE ; 
 int core_dev_export (void*,struct se_portal_group*,struct se_lun*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int core_tpg_post_addlun(
	struct se_portal_group *tpg,
	struct se_lun *lun,
	u32 lun_access,
	void *lun_ptr)
{
	int ret;

	ret = core_dev_export(lun_ptr, tpg, lun);
	if (ret < 0)
		return ret;

	spin_lock(&tpg->tpg_lun_lock);
	lun->lun_access = lun_access;
	lun->lun_status = TRANSPORT_LUN_STATUS_ACTIVE;
	spin_unlock(&tpg->tpg_lun_lock);

	return 0;
}