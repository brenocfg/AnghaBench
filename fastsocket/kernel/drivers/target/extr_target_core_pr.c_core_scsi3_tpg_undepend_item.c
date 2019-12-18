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
struct TYPE_4__ {int /*<<< orphan*/  cg_item; } ;
struct se_portal_group {int /*<<< orphan*/  tpg_pr_ref_count; TYPE_2__ tpg_group; TYPE_1__* se_tpg_tfo; } ;
struct TYPE_3__ {int /*<<< orphan*/  tf_subsys; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configfs_undepend_item (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic_dec () ; 

__attribute__((used)) static void core_scsi3_tpg_undepend_item(struct se_portal_group *tpg)
{
	configfs_undepend_item(tpg->se_tpg_tfo->tf_subsys,
			&tpg->tpg_group.cg_item);

	atomic_dec(&tpg->tpg_pr_ref_count);
	smp_mb__after_atomic_dec();
}