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
struct dentry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* d_instantiate ) (struct dentry*,struct inode*) ;} ;

/* Variables and functions */
 scalar_t__ IS_PRIVATE (struct inode*) ; 
 TYPE_1__* security_ops ; 
 int /*<<< orphan*/  stub1 (struct dentry*,struct inode*) ; 
 scalar_t__ unlikely (int) ; 

void security_d_instantiate(struct dentry *dentry, struct inode *inode)
{
	if (unlikely(inode && IS_PRIVATE(inode)))
		return;
	security_ops->d_instantiate(dentry, inode);
}