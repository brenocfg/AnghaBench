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
struct inode {TYPE_1__* i_op; int /*<<< orphan*/  i_mutex; } ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int (* mkdir ) (struct inode*,struct dentry*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int stub1 (struct inode*,struct dentry*,int) ; 
 int /*<<< orphan*/  vfs_dq_init (struct inode*) ; 

__attribute__((used)) static int xattr_mkdir(struct inode *dir, struct dentry *dentry, int mode)
{
	BUG_ON(!mutex_is_locked(&dir->i_mutex));
	vfs_dq_init(dir);
	return dir->i_op->mkdir(dir, dentry, mode);
}