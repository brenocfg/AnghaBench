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
struct TYPE_2__ {int /*<<< orphan*/  (* inode_free_security ) (struct inode*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ima_inode_free (struct inode*) ; 
 TYPE_1__* security_ops ; 
 int /*<<< orphan*/  stub1 (struct inode*) ; 

void security_inode_free(struct inode *inode)
{
	ima_inode_free(inode);
	security_ops->inode_free_security(inode);
}