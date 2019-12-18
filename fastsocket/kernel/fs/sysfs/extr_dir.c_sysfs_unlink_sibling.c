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
struct sysfs_dirent {TYPE_2__* s_parent; int /*<<< orphan*/  name_node; int /*<<< orphan*/  inode_node; } ;
struct TYPE_3__ {int /*<<< orphan*/  name_tree; int /*<<< orphan*/  inode_tree; int /*<<< orphan*/  subdirs; } ;
struct TYPE_4__ {TYPE_1__ s_dir; } ;

/* Variables and functions */
 scalar_t__ SYSFS_DIR ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sysfs_type (struct sysfs_dirent*) ; 

__attribute__((used)) static void sysfs_unlink_sibling(struct sysfs_dirent *sd)
{
	if (sysfs_type(sd) == SYSFS_DIR)
		sd->s_parent->s_dir.subdirs--;

	rb_erase(&sd->inode_node, &sd->s_parent->s_dir.inode_tree);
	rb_erase(&sd->name_node, &sd->s_parent->s_dir.name_tree);
}