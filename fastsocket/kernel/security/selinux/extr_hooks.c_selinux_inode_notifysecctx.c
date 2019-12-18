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
typedef  int /*<<< orphan*/  u32 ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XATTR_SELINUX_SUFFIX ; 
 int selinux_inode_setsecurity (struct inode*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int selinux_inode_notifysecctx(struct inode *inode, void *ctx, u32 ctxlen)
{
	return selinux_inode_setsecurity(inode, XATTR_SELINUX_SUFFIX, ctx, ctxlen, 0);
}