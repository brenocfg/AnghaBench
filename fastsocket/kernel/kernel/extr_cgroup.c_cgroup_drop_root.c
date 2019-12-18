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
struct cgroupfs_root {int /*<<< orphan*/  hierarchy_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  hierarchy_id_lock ; 
 int /*<<< orphan*/  hierarchy_ida ; 
 int /*<<< orphan*/  ida_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cgroupfs_root*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cgroup_drop_root(struct cgroupfs_root *root)
{
	if (!root)
		return;

	BUG_ON(!root->hierarchy_id);
	spin_lock(&hierarchy_id_lock);
	ida_remove(&hierarchy_ida, root->hierarchy_id);
	spin_unlock(&hierarchy_id_lock);
	kfree(root);
}