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
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int EXT4_ADDR_PER_BLOCK (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_indirect_trans_blocks(struct inode *inode, int nrblocks,
				      int chunk)
{
	int indirects;

	/* if nrblocks are contiguous */
	if (chunk) {
		/*
		 * With N contiguous data blocks, it need at most
		 * N/EXT4_ADDR_PER_BLOCK(inode->i_sb) indirect blocks
		 * 2 dindirect blocks
		 * 1 tindirect block
		 */
		indirects = nrblocks / EXT4_ADDR_PER_BLOCK(inode->i_sb);
		return indirects + 3;
	}
	/*
	 * if nrblocks are not contiguous, worse case, each block touch
	 * a indirect block, and each indirect block touch a double indirect
	 * block, plus a triple indirect block
	 */
	indirects = nrblocks * 2 + 1;
	return indirects;
}