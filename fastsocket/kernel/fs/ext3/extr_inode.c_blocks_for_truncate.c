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
struct inode {int i_blocks; TYPE_1__* i_sb; } ;
struct TYPE_2__ {int s_blocksize_bits; } ;

/* Variables and functions */
 unsigned long EXT3_DATA_TRANS_BLOCKS (TYPE_1__*) ; 
 unsigned long EXT3_MAX_TRANS_DATA ; 

__attribute__((used)) static unsigned long blocks_for_truncate(struct inode *inode)
{
	unsigned long needed;

	needed = inode->i_blocks >> (inode->i_sb->s_blocksize_bits - 9);

	/* Give ourselves just enough room to cope with inodes in which
	 * i_blocks is corrupt: we've seen disk corruptions in the past
	 * which resulted in random data in an inode which looked enough
	 * like a regular file for ext3 to try to delete it.  Things
	 * will go a bit crazy if that happens, but at least we should
	 * try not to panic the whole kernel. */
	if (needed < 2)
		needed = 2;

	/* But we need to bound the transaction so we don't overflow the
	 * journal. */
	if (needed > EXT3_MAX_TRANS_DATA)
		needed = EXT3_MAX_TRANS_DATA;

	return EXT3_DATA_TRANS_BLOCKS(inode->i_sb) + needed;
}