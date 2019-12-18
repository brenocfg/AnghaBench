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
struct se_portal_group {TYPE_1__* se_tpg_tfo; } ;
struct TYPE_4__ {int /*<<< orphan*/  cg_item; } ;
struct se_node_acl {TYPE_2__ acl_group; scalar_t__ dynamic_node_acl; struct se_portal_group* se_tpg; } ;
struct TYPE_3__ {int /*<<< orphan*/  tf_subsys; } ;

/* Variables and functions */
 int configfs_depend_item (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int core_scsi3_nodeacl_depend_item(struct se_node_acl *nacl)
{
	struct se_portal_group *tpg = nacl->se_tpg;

	if (nacl->dynamic_node_acl)
		return 0;

	return configfs_depend_item(tpg->se_tpg_tfo->tf_subsys,
			&nacl->acl_group.cg_item);
}