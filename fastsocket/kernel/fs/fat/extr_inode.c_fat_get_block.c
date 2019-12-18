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
struct super_block {unsigned long s_blocksize_bits; } ;
struct inode {unsigned long i_blkbits; struct super_block* i_sb; } ;
struct buffer_head {unsigned long b_size; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int __fat_get_block (struct inode*,int /*<<< orphan*/ ,unsigned long*,struct buffer_head*,int) ; 

__attribute__((used)) static int fat_get_block(struct inode *inode, sector_t iblock,
			 struct buffer_head *bh_result, int create)
{
	struct super_block *sb = inode->i_sb;
	unsigned long max_blocks = bh_result->b_size >> inode->i_blkbits;
	int err;

	err = __fat_get_block(inode, iblock, &max_blocks, bh_result, create);
	if (err)
		return err;
	bh_result->b_size = max_blocks << sb->s_blocksize_bits;
	return 0;
}