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
struct inode {scalar_t__ i_blocks; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ino; } ;
struct buffer_head {int dummy; } ;
typedef  scalar_t__ sector_t ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ __adfs_block_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  map_bh (struct buffer_head*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
adfs_get_block(struct inode *inode, sector_t block, struct buffer_head *bh,
	       int create)
{
	if (!create) {
		if (block >= inode->i_blocks)
			goto abort_toobig;

		block = __adfs_block_map(inode->i_sb, inode->i_ino, block);
		if (block)
			map_bh(bh, inode->i_sb, block);
		return 0;
	}
	/* don't support allocation of blocks yet */
	return -EIO;

abort_toobig:
	return 0;
}