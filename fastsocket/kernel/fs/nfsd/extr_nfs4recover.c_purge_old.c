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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 scalar_t__ nfs4_has_reclaimed_state (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int vfs_rmdir (int /*<<< orphan*/ ,struct dentry*) ; 

__attribute__((used)) static int
purge_old(struct dentry *parent, struct dentry *child)
{
	int status;

	/* note: we currently use this path only for minorversion 0 */
	if (nfs4_has_reclaimed_state(child->d_name.name, false))
		return 0;

	status = vfs_rmdir(parent->d_inode, child);
	if (status)
		printk("failed to remove client recovery directory %s\n",
				child->d_name.name);
	/* Keep trying, success or failure: */
	return 0;
}