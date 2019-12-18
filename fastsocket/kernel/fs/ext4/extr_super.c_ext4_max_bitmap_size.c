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
typedef  int /*<<< orphan*/  u64 ;
typedef  int loff_t ;
typedef  int /*<<< orphan*/  blkcnt_t ;

/* Variables and functions */
 int EXT4_NDIR_BLOCKS ; 
 int MAX_LFS_FILESIZE ; 

__attribute__((used)) static loff_t ext4_max_bitmap_size(int bits, int has_huge_files)
{
	loff_t res = EXT4_NDIR_BLOCKS;
	int meta_blocks;
	loff_t upper_limit;
	/* This is calculated to be the largest file size for a dense, block
	 * mapped file such that the file's total number of 512-byte sectors,
	 * including data and all indirect blocks, does not exceed (2^48 - 1).
	 *
	 * __u32 i_blocks_lo and _u16 i_blocks_high represent the total
	 * number of 512-byte sectors of the file.
	 */

	if (!has_huge_files || sizeof(blkcnt_t) < sizeof(u64)) {
		/*
		 * !has_huge_files or CONFIG_LBDAF not enabled implies that
		 * the inode i_block field represents total file blocks in
		 * 2^32 512-byte sectors == size of vfs inode i_blocks * 8
		 */
		upper_limit = (1LL << 32) - 1;

		/* total blocks in file system block size */
		upper_limit >>= (bits - 9);

	} else {
		/*
		 * We use 48 bit ext4_inode i_blocks
		 * With EXT4_HUGE_FILE_FL set the i_blocks
		 * represent total number of blocks in
		 * file system block size
		 */
		upper_limit = (1LL << 48) - 1;

	}

	/* indirect blocks */
	meta_blocks = 1;
	/* double indirect blocks */
	meta_blocks += 1 + (1LL << (bits-2));
	/* tripple indirect blocks */
	meta_blocks += 1 + (1LL << (bits-2)) + (1LL << (2*(bits-2)));

	upper_limit -= meta_blocks;
	upper_limit <<= bits;

	res += 1LL << (bits-2);
	res += 1LL << (2*(bits-2));
	res += 1LL << (3*(bits-2));
	res <<= bits;
	if (res > upper_limit)
		res = upper_limit;

	if (res > MAX_LFS_FILESIZE)
		res = MAX_LFS_FILESIZE;

	return res;
}