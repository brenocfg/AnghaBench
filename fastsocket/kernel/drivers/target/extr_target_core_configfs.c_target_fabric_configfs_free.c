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
struct target_fabric_configfs {int /*<<< orphan*/  tf_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_tf_lock ; 
 int /*<<< orphan*/  kfree (struct target_fabric_configfs*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void target_fabric_configfs_free(
	struct target_fabric_configfs *tf)
{
	mutex_lock(&g_tf_lock);
	list_del(&tf->tf_list);
	mutex_unlock(&g_tf_lock);

	kfree(tf);
}