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
struct inode {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;
struct TYPE_2__ {int (* inode_link ) (struct dentry*,struct inode*,struct dentry*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IS_PRIVATE (int /*<<< orphan*/ ) ; 
 TYPE_1__* security_ops ; 
 int stub1 (struct dentry*,struct inode*,struct dentry*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int security_inode_link(struct dentry *old_dentry, struct inode *dir,
			 struct dentry *new_dentry)
{
	if (unlikely(IS_PRIVATE(old_dentry->d_inode)))
		return 0;
	return security_ops->inode_link(old_dentry, dir, new_dentry);
}