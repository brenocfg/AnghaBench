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
struct dentry {TYPE_1__* d_inode; } ;
struct c4iw_dev {int /*<<< orphan*/  debugfs_root; } ;
struct TYPE_2__ {int i_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IWUSR ; 
 struct dentry* debugfs_create_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qp_debugfs_fops ; 
 int /*<<< orphan*/  stag_debugfs_fops ; 

__attribute__((used)) static int setup_debugfs(struct c4iw_dev *devp)
{
	struct dentry *de;

	if (!devp->debugfs_root)
		return -1;

	de = debugfs_create_file("qps", S_IWUSR, devp->debugfs_root,
				 (void *)devp, &qp_debugfs_fops);
	if (de && de->d_inode)
		de->d_inode->i_size = 4096;

	de = debugfs_create_file("stags", S_IWUSR, devp->debugfs_root,
				 (void *)devp, &stag_debugfs_fops);
	if (de && de->d_inode)
		de->d_inode->i_size = 4096;
	return 0;
}