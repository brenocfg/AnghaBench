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
struct super_operations {void (* drop_inode ) (struct inode*) ;} ;
struct inode {TYPE_1__* i_sb; } ;
struct TYPE_2__ {struct super_operations* s_op; } ;

/* Variables and functions */
 void generic_drop_inode (struct inode*) ; 

__attribute__((used)) static inline void iput_final(struct inode *inode)
{
	const struct super_operations *op = inode->i_sb->s_op;
	void (*drop)(struct inode *) = generic_drop_inode;

	if (op && op->drop_inode)
		drop = op->drop_inode;
	drop(inode);
}