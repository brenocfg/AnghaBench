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
struct list_blocks_struct {scalar_t__ first_pblock; scalar_t__ last_pblock; scalar_t__ last_block; scalar_t__ first_block; } ;
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  scalar_t__ ext4_lblk_t ;
typedef  scalar_t__ ext4_fsblk_t ;

/* Variables and functions */
 int finish_range (int /*<<< orphan*/ *,struct inode*,struct list_blocks_struct*) ; 

__attribute__((used)) static int update_extent_range(handle_t *handle, struct inode *inode,
				ext4_fsblk_t pblock, ext4_lblk_t blk_num,
				struct list_blocks_struct *lb)
{
	int retval;
	/*
	 * See if we can add on to the existing range (if it exists)
	 */
	if (lb->first_pblock &&
		(lb->last_pblock+1 == pblock) &&
		(lb->last_block+1 == blk_num)) {
		lb->last_pblock = pblock;
		lb->last_block = blk_num;
		return 0;
	}
	/*
	 * Start a new range.
	 */
	retval = finish_range(handle, inode, lb);
	lb->first_pblock = lb->last_pblock = pblock;
	lb->first_block = lb->last_block = blk_num;

	return retval;
}