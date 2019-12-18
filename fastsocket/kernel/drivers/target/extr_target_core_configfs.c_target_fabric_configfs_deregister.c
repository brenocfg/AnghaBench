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
struct target_fabric_configfs {struct configfs_subsystem* tf_subsys; int /*<<< orphan*/ * tf_module; int /*<<< orphan*/  tf_name; int /*<<< orphan*/  tf_list; int /*<<< orphan*/  tf_access_cnt; } ;
struct configfs_subsystem {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_tf_lock ; 
 int /*<<< orphan*/  kfree (struct target_fabric_configfs*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

void target_fabric_configfs_deregister(
	struct target_fabric_configfs *tf)
{
	struct configfs_subsystem *su;

	if (!tf) {
		pr_err("Unable to locate passed target_fabric_"
			"configfs\n");
		return;
	}
	su = tf->tf_subsys;
	if (!su) {
		pr_err("Unable to locate passed tf->tf_subsys"
			" pointer\n");
		return;
	}
	pr_debug("<<<<<<<<<<<<<<<<<<<<<< BEGIN FABRIC API >>>>>>>>>>"
			">>>>>>>>>>>>\n");
	mutex_lock(&g_tf_lock);
	if (atomic_read(&tf->tf_access_cnt)) {
		mutex_unlock(&g_tf_lock);
		pr_err("Non zero tf->tf_access_cnt for fabric %s\n",
			tf->tf_name);
		BUG();
	}
	list_del(&tf->tf_list);
	mutex_unlock(&g_tf_lock);

	pr_debug("Target_Core_ConfigFS: DEREGISTER -> Releasing tf:"
			" %s\n", tf->tf_name);
	tf->tf_module = NULL;
	tf->tf_subsys = NULL;
	kfree(tf);

	pr_debug("<<<<<<<<<<<<<<<<<<<<<< END FABRIC API >>>>>>>>>>>>>>>>>"
			">>>>>\n");
}