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
typedef  int /*<<< orphan*/  handle_t ;
typedef  int /*<<< orphan*/  ext3_fsblk_t ;

/* Variables and functions */
 int /*<<< orphan*/  ext3_new_blocks (int /*<<< orphan*/ *,struct inode*,int /*<<< orphan*/ ,unsigned long*,int*) ; 

ext3_fsblk_t ext3_new_block(handle_t *handle, struct inode *inode,
			ext3_fsblk_t goal, int *errp)
{
	unsigned long count = 1;

	return ext3_new_blocks(handle, inode, goal, &count, errp);
}