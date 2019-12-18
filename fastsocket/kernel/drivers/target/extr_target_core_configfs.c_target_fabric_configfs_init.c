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
struct target_fabric_configfs {int /*<<< orphan*/  tf_name; int /*<<< orphan*/  tf_list; int /*<<< orphan*/  tf_subsys; struct module* tf_module; int /*<<< orphan*/  tf_access_cnt; } ;
struct module {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct target_fabric_configfs* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ TARGET_FABRIC_NAME_SIZE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_tf_list ; 
 int /*<<< orphan*/  g_tf_lock ; 
 struct target_fabric_configfs* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,scalar_t__,char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/ * target_core_subsystem ; 
 int /*<<< orphan*/  target_fabric_setup_cits (struct target_fabric_configfs*) ; 

struct target_fabric_configfs *target_fabric_configfs_init(
	struct module *fabric_mod,
	const char *name)
{
	struct target_fabric_configfs *tf;

	if (!(name)) {
		pr_err("Unable to locate passed fabric name\n");
		return ERR_PTR(-EINVAL);
	}
	if (strlen(name) >= TARGET_FABRIC_NAME_SIZE) {
		pr_err("Passed name: %s exceeds TARGET_FABRIC"
			"_NAME_SIZE\n", name);
		return ERR_PTR(-EINVAL);
	}

	tf = kzalloc(sizeof(struct target_fabric_configfs), GFP_KERNEL);
	if (!tf)
		return ERR_PTR(-ENOMEM);

	INIT_LIST_HEAD(&tf->tf_list);
	atomic_set(&tf->tf_access_cnt, 0);
	/*
	 * Setup the default generic struct config_item_type's (cits) in
	 * struct target_fabric_configfs->tf_cit_tmpl
	 */
	tf->tf_module = fabric_mod;
	target_fabric_setup_cits(tf);

	tf->tf_subsys = target_core_subsystem[0];
	snprintf(tf->tf_name, TARGET_FABRIC_NAME_SIZE, "%s", name);

	mutex_lock(&g_tf_lock);
	list_add_tail(&tf->tf_list, &g_tf_list);
	mutex_unlock(&g_tf_lock);

	pr_debug("<<<<<<<<<<<<<<<<<<<<<< BEGIN FABRIC API >>>>>>>>"
			">>>>>>>>>>>>>>\n");
	pr_debug("Initialized struct target_fabric_configfs: %p for"
			" %s\n", tf, tf->tf_name);
	return tf;
}