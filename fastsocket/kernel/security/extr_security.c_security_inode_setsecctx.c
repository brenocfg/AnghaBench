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
typedef  int /*<<< orphan*/  u32 ;
struct dentry {int dummy; } ;
struct TYPE_2__ {int (* inode_setsecctx ) (struct dentry*,void*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__* security_ops ; 
 int stub1 (struct dentry*,void*,int /*<<< orphan*/ ) ; 

int security_inode_setsecctx(struct dentry *dentry, void *ctx, u32 ctxlen)
{
	return security_ops->inode_setsecctx(dentry, ctx, ctxlen);
}