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
struct tcm_loop_tpg {TYPE_1__* tl_hba; } ;
struct se_portal_group {struct tcm_loop_tpg* se_tpg_fabric_ptr; } ;
struct TYPE_2__ {char* tl_wwn_address; } ;

/* Variables and functions */

__attribute__((used)) static char *tcm_loop_get_endpoint_wwn(struct se_portal_group *se_tpg)
{
	struct tcm_loop_tpg *tl_tpg = se_tpg->se_tpg_fabric_ptr;
	/*
	 * Return the passed NAA identifier for the SAS Target Port
	 */
	return &tl_tpg->tl_hba->tl_wwn_address[0];
}