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
typedef  int /*<<< orphan*/  umode_t ;
struct dentry {int /*<<< orphan*/ * d_op; int /*<<< orphan*/  d_fsdata; } ;
struct configfs_dirent {struct dentry* s_dentry; int /*<<< orphan*/  s_mode; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct configfs_dirent*) ; 
 int PTR_ERR (struct configfs_dirent*) ; 
 int /*<<< orphan*/  configfs_dentry_ops ; 
 int /*<<< orphan*/  configfs_get (struct configfs_dirent*) ; 
 struct configfs_dirent* configfs_new_dirent (struct configfs_dirent*,void*,int) ; 

int configfs_make_dirent(struct configfs_dirent * parent_sd,
			 struct dentry * dentry, void * element,
			 umode_t mode, int type)
{
	struct configfs_dirent * sd;

	sd = configfs_new_dirent(parent_sd, element, type);
	if (IS_ERR(sd))
		return PTR_ERR(sd);

	sd->s_mode = mode;
	sd->s_dentry = dentry;
	if (dentry) {
		dentry->d_fsdata = configfs_get(sd);
		dentry->d_op = &configfs_dentry_ops;
	}

	return 0;
}