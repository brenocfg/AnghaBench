#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct super_block {int dummy; } ;
struct inode {int i_ino; int i_size; struct super_block* i_sb; } ;
struct buffer_head {unsigned long b_state; int b_blocknr; } ;
struct TYPE_6__ {void* next; void* size; void* sequence; void* key; void* ptype; } ;
struct TYPE_5__ {int mmu_private; } ;
struct TYPE_4__ {int s_data_blksize; } ;

/* Variables and functions */
 scalar_t__ AFFS_DATA (struct buffer_head*) ; 
 TYPE_3__* AFFS_DATA_HEAD (struct buffer_head*) ; 
 TYPE_2__* AFFS_I (struct inode*) ; 
 TYPE_1__* AFFS_SB (struct super_block*) ; 
 unsigned long BH_New ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IS_ERR (struct buffer_head*) ; 
 int PTR_ERR (struct buffer_head*) ; 
 int T_DATA ; 
 int /*<<< orphan*/  affs_adjust_checksum (struct buffer_head*,int) ; 
 struct buffer_head* affs_bread_ino (struct inode*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  affs_brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  affs_fix_checksum (struct super_block*,struct buffer_head*) ; 
 struct buffer_head* affs_getzeroblk_ino (struct inode*,int) ; 
 int /*<<< orphan*/  affs_warning (struct super_block*,char*,char*,int,int) ; 
 int /*<<< orphan*/  be32_add_cpu (void**,int) ; 
 int be32_to_cpu (void*) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (struct buffer_head*,struct inode*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int) ; 

__attribute__((used)) static int
affs_extent_file_ofs(struct inode *inode, u32 newsize)
{
	struct super_block *sb = inode->i_sb;
	struct buffer_head *bh, *prev_bh;
	u32 bidx, boff;
	u32 size, bsize;
	u32 tmp;

	pr_debug("AFFS: extent_file(%u, %d)\n", (u32)inode->i_ino, newsize);
	bsize = AFFS_SB(sb)->s_data_blksize;
	bh = NULL;
	size = AFFS_I(inode)->mmu_private;
	bidx = size / bsize;
	boff = size % bsize;
	if (boff) {
		bh = affs_bread_ino(inode, bidx, 0);
		if (IS_ERR(bh))
			return PTR_ERR(bh);
		tmp = min(bsize - boff, newsize - size);
		BUG_ON(boff + tmp > bsize || tmp > bsize);
		memset(AFFS_DATA(bh) + boff, 0, tmp);
		be32_add_cpu(&AFFS_DATA_HEAD(bh)->size, tmp);
		affs_fix_checksum(sb, bh);
		mark_buffer_dirty_inode(bh, inode);
		size += tmp;
		bidx++;
	} else if (bidx) {
		bh = affs_bread_ino(inode, bidx - 1, 0);
		if (IS_ERR(bh))
			return PTR_ERR(bh);
	}

	while (size < newsize) {
		prev_bh = bh;
		bh = affs_getzeroblk_ino(inode, bidx);
		if (IS_ERR(bh))
			goto out;
		tmp = min(bsize, newsize - size);
		BUG_ON(tmp > bsize);
		AFFS_DATA_HEAD(bh)->ptype = cpu_to_be32(T_DATA);
		AFFS_DATA_HEAD(bh)->key = cpu_to_be32(inode->i_ino);
		AFFS_DATA_HEAD(bh)->sequence = cpu_to_be32(bidx);
		AFFS_DATA_HEAD(bh)->size = cpu_to_be32(tmp);
		affs_fix_checksum(sb, bh);
		bh->b_state &= ~(1UL << BH_New);
		mark_buffer_dirty_inode(bh, inode);
		if (prev_bh) {
			u32 tmp = be32_to_cpu(AFFS_DATA_HEAD(prev_bh)->next);
			if (tmp)
				affs_warning(sb, "extent_file_ofs", "next block already set for %d (%d)", bidx, tmp);
			AFFS_DATA_HEAD(prev_bh)->next = cpu_to_be32(bh->b_blocknr);
			affs_adjust_checksum(prev_bh, bh->b_blocknr - tmp);
			mark_buffer_dirty_inode(prev_bh, inode);
			affs_brelse(prev_bh);
		}
		size += bsize;
		bidx++;
	}
	affs_brelse(bh);
	inode->i_size = AFFS_I(inode)->mmu_private = newsize;
	return 0;

out:
	inode->i_size = AFFS_I(inode)->mmu_private = newsize;
	return PTR_ERR(bh);
}