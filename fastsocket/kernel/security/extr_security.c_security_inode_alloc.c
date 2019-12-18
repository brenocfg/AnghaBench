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
struct inode {int /*<<< orphan*/ * i_security; } ;
struct TYPE_2__ {int (* inode_alloc_security ) (struct inode*) ;} ;

/* Variables and functions */
 int ima_inode_alloc (struct inode*) ; 
 int /*<<< orphan*/  security_inode_free (struct inode*) ; 
 TYPE_1__* security_ops ; 
 int stub1 (struct inode*) ; 

int security_inode_alloc(struct inode *inode)
{
	int ret;

	inode->i_security = NULL;
	ret =  security_ops->inode_alloc_security(inode);
	if (ret)
		return ret;
	ret = ima_inode_alloc(inode);
	if (ret)
		security_inode_free(inode);
	return ret;
}