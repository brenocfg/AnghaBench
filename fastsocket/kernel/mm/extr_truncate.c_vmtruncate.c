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
struct inode {TYPE_1__* i_op; } ;
typedef  int /*<<< orphan*/  loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* truncate ) (struct inode*) ;} ;

/* Variables and functions */
 int inode_newsize_ok (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct inode*) ; 
 int /*<<< orphan*/  truncate_setsize (struct inode*,int /*<<< orphan*/ ) ; 

int vmtruncate(struct inode *inode, loff_t newsize)
{
	int error;

	error = inode_newsize_ok(inode, newsize);
	if (error)
		return error;

	truncate_setsize(inode, newsize);
	if (inode->i_op->truncate)
		inode->i_op->truncate(inode);
	return 0;
}