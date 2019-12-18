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
struct se_node_acl {struct se_portal_group* se_tpg; } ;
struct se_lun_acl {int /*<<< orphan*/  mapped_lun; int /*<<< orphan*/  initiatorname; struct se_node_acl* se_lun_nacl; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_fabric_name ) () ;} ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  TRANSPORT_LUNFLAGS_READ_ONLY ; 
 int /*<<< orphan*/  TRANSPORT_LUNFLAGS_READ_WRITE ; 
 int /*<<< orphan*/  core_update_device_list_access (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct se_node_acl*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strict_strtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static ssize_t target_fabric_mappedlun_store_write_protect(
	struct se_lun_acl *lacl,
	const char *page,
	size_t count)
{
	struct se_node_acl *se_nacl = lacl->se_lun_nacl;
	struct se_portal_group *se_tpg = se_nacl->se_tpg;
	unsigned long op;

	if (strict_strtoul(page, 0, &op))
		return -EINVAL;

	if ((op != 1) && (op != 0))
		return -EINVAL;

	core_update_device_list_access(lacl->mapped_lun, (op) ?
			TRANSPORT_LUNFLAGS_READ_ONLY :
			TRANSPORT_LUNFLAGS_READ_WRITE,
			lacl->se_lun_nacl);

	pr_debug("%s_ConfigFS: Changed Initiator ACL: %s"
		" Mapped LUN: %u Write Protect bit to %s\n",
		se_tpg->se_tpg_tfo->get_fabric_name(),
		lacl->initiatorname, lacl->mapped_lun, (op) ? "ON" : "OFF");

	return count;

}