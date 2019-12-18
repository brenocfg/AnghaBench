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
struct se_portal_group {struct ft_tpg* se_tpg_fabric_ptr; } ;
struct ft_tpg {TYPE_1__* lport_acl; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */

__attribute__((used)) static char *ft_get_fabric_wwn(struct se_portal_group *se_tpg)
{
	struct ft_tpg *tpg = se_tpg->se_tpg_fabric_ptr;

	return tpg->lport_acl->name;
}