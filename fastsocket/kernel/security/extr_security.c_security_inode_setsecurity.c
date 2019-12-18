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
struct TYPE_2__ {int (* inode_setsecurity ) (struct inode*,char const*,void const*,size_t,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IS_PRIVATE (struct inode*) ; 
 TYPE_1__* security_ops ; 
 int stub1 (struct inode*,char const*,void const*,size_t,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int security_inode_setsecurity(struct inode *inode, const char *name, const void *value, size_t size, int flags)
{
	if (unlikely(IS_PRIVATE(inode)))
		return 0;
	return security_ops->inode_setsecurity(inode, name, value, size, flags);
}