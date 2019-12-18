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
struct se_portal_group {TYPE_1__* se_tpg_tfo; } ;
struct se_node_acl {int queue_depth; int /*<<< orphan*/  initiatorname; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_fabric_name ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static int core_set_queue_depth_for_node(
	struct se_portal_group *tpg,
	struct se_node_acl *acl)
{
	if (!acl->queue_depth) {
		pr_err("Queue depth for %s Initiator Node: %s is 0,"
			"defaulting to 1.\n", tpg->se_tpg_tfo->get_fabric_name(),
			acl->initiatorname);
		acl->queue_depth = 1;
	}

	return 0;
}