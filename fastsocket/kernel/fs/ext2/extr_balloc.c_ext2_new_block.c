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
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  ext2_fsblk_t ;

/* Variables and functions */
 int /*<<< orphan*/  ext2_new_blocks (struct inode*,unsigned long,unsigned long*,int*) ; 

ext2_fsblk_t ext2_new_block(struct inode *inode, unsigned long goal, int *errp)
{
	unsigned long count = 1;

	return ext2_new_blocks(inode, goal, &count, errp);
}