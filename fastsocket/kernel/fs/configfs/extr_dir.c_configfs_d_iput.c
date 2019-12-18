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
struct inode {int dummy; } ;
struct dentry {struct configfs_dirent* d_fsdata; } ;
struct configfs_dirent {struct dentry* s_dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  configfs_put (struct configfs_dirent*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 

__attribute__((used)) static void configfs_d_iput(struct dentry * dentry,
			    struct inode * inode)
{
	struct configfs_dirent * sd = dentry->d_fsdata;

	if (sd) {
		BUG_ON(sd->s_dentry != dentry);
		sd->s_dentry = NULL;
		configfs_put(sd);
	}
	iput(inode);
}