#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char const* ci_name; } ;
struct config_group {TYPE_2__ cg_item; struct config_group** default_groups; } ;
struct TYPE_4__ {int /*<<< orphan*/  tf_subsys; } ;
struct target_fabric_configfs {char const* tf_name; struct config_group tf_group; TYPE_2__* tf_fabric; int /*<<< orphan*/  tf_subsys; TYPE_1__ tf_ops; struct config_group tf_disc_group; struct config_group** tf_default_groups; } ;
struct TYPE_6__ {char const tfc_wwn_cit; char const tfc_discovery_cit; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct config_group* ERR_PTR (int /*<<< orphan*/ ) ; 
 TYPE_3__* TF_CIT_TMPL (struct target_fabric_configfs*) ; 
 int /*<<< orphan*/  config_group_init_type_name (struct config_group*,char const*,char const*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int request_module (char*) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 struct target_fabric_configfs* target_core_get_fabric (char const*) ; 

__attribute__((used)) static struct config_group *target_core_register_fabric(
	struct config_group *group,
	const char *name)
{
	struct target_fabric_configfs *tf;
	int ret;

	pr_debug("Target_Core_ConfigFS: REGISTER -> group: %p name:"
			" %s\n", group, name);
	/*
	 * Below are some hardcoded request_module() calls to automatically
	 * local fabric modules when the following is called:
	 *
	 * mkdir -p /sys/kernel/config/target/$MODULE_NAME
	 *
	 * Note that this does not limit which TCM fabric module can be
	 * registered, but simply provids auto loading logic for modules with
	 * mkdir(2) system calls with known TCM fabric modules.
	 */
	if (!strncmp(name, "iscsi", 5)) {
		/*
		 * Automatically load the LIO Target fabric module when the
		 * following is called:
		 *
		 * mkdir -p $CONFIGFS/target/iscsi
		 */
		ret = request_module("iscsi_target_mod");
		if (ret < 0) {
			pr_err("request_module() failed for"
				" iscsi_target_mod.ko: %d\n", ret);
			return ERR_PTR(-EINVAL);
		}
	} else if (!strncmp(name, "loopback", 8)) {
		/*
		 * Automatically load the tcm_loop fabric module when the
		 * following is called:
		 *
		 * mkdir -p $CONFIGFS/target/loopback
		 */
		ret = request_module("tcm_loop");
		if (ret < 0) {
			pr_err("request_module() failed for"
				" tcm_loop.ko: %d\n", ret);
			return ERR_PTR(-EINVAL);
		}
	}

	tf = target_core_get_fabric(name);
	if (!tf) {
		pr_err("target_core_get_fabric() failed for %s\n",
			name);
		return ERR_PTR(-EINVAL);
	}
	pr_debug("Target_Core_ConfigFS: REGISTER -> Located fabric:"
			" %s\n", tf->tf_name);
	/*
	 * On a successful target_core_get_fabric() look, the returned
	 * struct target_fabric_configfs *tf will contain a usage reference.
	 */
	pr_debug("Target_Core_ConfigFS: REGISTER tfc_wwn_cit -> %p\n",
			&TF_CIT_TMPL(tf)->tfc_wwn_cit);

	tf->tf_group.default_groups = tf->tf_default_groups;
	tf->tf_group.default_groups[0] = &tf->tf_disc_group;
	tf->tf_group.default_groups[1] = NULL;

	config_group_init_type_name(&tf->tf_group, name,
			&TF_CIT_TMPL(tf)->tfc_wwn_cit);
	config_group_init_type_name(&tf->tf_disc_group, "discovery_auth",
			&TF_CIT_TMPL(tf)->tfc_discovery_cit);

	pr_debug("Target_Core_ConfigFS: REGISTER -> Allocated Fabric:"
			" %s\n", tf->tf_group.cg_item.ci_name);
	/*
	 * Setup tf_ops.tf_subsys pointer for usage with configfs_depend_item()
	 */
	tf->tf_ops.tf_subsys = tf->tf_subsys;
	tf->tf_fabric = &tf->tf_group.cg_item;
	pr_debug("Target_Core_ConfigFS: REGISTER -> Set tf->tf_fabric"
			" for %s\n", name);

	return &tf->tf_group;
}