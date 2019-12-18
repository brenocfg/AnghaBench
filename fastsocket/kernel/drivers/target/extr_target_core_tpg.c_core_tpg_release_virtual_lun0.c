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
struct se_lun {int dummy; } ;
struct se_portal_group {struct se_lun tpg_virt_lun0; } ;

/* Variables and functions */
 int /*<<< orphan*/  core_tpg_post_dellun (struct se_portal_group*,struct se_lun*) ; 

__attribute__((used)) static void core_tpg_release_virtual_lun0(struct se_portal_group *se_tpg)
{
	struct se_lun *lun = &se_tpg->tpg_virt_lun0;

	core_tpg_post_dellun(se_tpg, lun);
}