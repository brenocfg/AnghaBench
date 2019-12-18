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
struct page {unsigned int index; } ;
struct inode {int i_ino; int i_size; struct super_block* i_sb; } ;
struct file {int dummy; } ;
struct buffer_head {unsigned long b_state; int b_blocknr; } ;
struct address_space {struct inode* host; } ;
typedef  int loff_t ;
struct TYPE_6__ {void* size; void* next; void* sequence; void* key; void* ptype; } ;
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
 unsigned int PAGE_CACHE_SHIFT ; 
 int PAGE_CACHE_SIZE ; 
 int PTR_ERR (struct buffer_head*) ; 
 int /*<<< orphan*/  SetPageUptodate (struct page*) ; 
 int T_DATA ; 
 int /*<<< orphan*/  affs_adjust_checksum (struct buffer_head*,int) ; 
 struct buffer_head* affs_bread_ino (struct inode*,int,int) ; 
 int /*<<< orphan*/  affs_brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  affs_fix_checksum (struct super_block*,struct buffer_head*) ; 
 struct buffer_head* affs_getemptyblk_ino (struct inode*,int) ; 
 int /*<<< orphan*/  affs_warning (struct super_block*,char*,char*,int,int) ; 
 int /*<<< orphan*/  be32_add_cpu (void**,int) ; 
 int be32_to_cpu (void*) ; 
 scalar_t__ buffer_new (struct buffer_head*) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  mark_buffer_dirty_inode (struct buffer_head*,struct inode*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char*,int) ; 
 int min (int,unsigned int) ; 
 char* page_address (struct page*) ; 
 int /*<<< orphan*/  page_cache_release (struct page*) ; 
 int /*<<< orphan*/  pr_debug (char*,int,unsigned long long,unsigned long long) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

__attribute__((used)) static int affs_write_end_ofs(struct file *file, struct address_space *mapping,
				loff_t pos, unsigned len, unsigned copied,
				struct page *page, void *fsdata)
{
	struct inode *inode = mapping->host;
	struct super_block *sb = inode->i_sb;
	struct buffer_head *bh, *prev_bh;
	char *data;
	u32 bidx, boff, bsize;
	unsigned from, to;
	u32 tmp;
	int written;

	from = pos & (PAGE_CACHE_SIZE - 1);
	to = pos + len;
	/*
	 * XXX: not sure if this can handle short copies (len < copied), but
	 * we don't have to, because the page should always be uptodate here,
	 * due to write_begin.
	 */

	pr_debug("AFFS: write_begin(%u, %llu, %llu)\n", (u32)inode->i_ino, (unsigned long long)pos, (unsigned long long)pos + len);
	bsize = AFFS_SB(sb)->s_data_blksize;
	data = page_address(page);

	bh = NULL;
	written = 0;
	tmp = (page->index << PAGE_CACHE_SHIFT) + from;
	bidx = tmp / bsize;
	boff = tmp % bsize;
	if (boff) {
		bh = affs_bread_ino(inode, bidx, 0);
		if (IS_ERR(bh))
			return PTR_ERR(bh);
		tmp = min(bsize - boff, to - from);
		BUG_ON(boff + tmp > bsize || tmp > bsize);
		memcpy(AFFS_DATA(bh) + boff, data + from, tmp);
		be32_add_cpu(&AFFS_DATA_HEAD(bh)->size, tmp);
		affs_fix_checksum(sb, bh);
		mark_buffer_dirty_inode(bh, inode);
		written += tmp;
		from += tmp;
		bidx++;
	} else if (bidx) {
		bh = affs_bread_ino(inode, bidx - 1, 0);
		if (IS_ERR(bh))
			return PTR_ERR(bh);
	}
	while (from + bsize <= to) {
		prev_bh = bh;
		bh = affs_getemptyblk_ino(inode, bidx);
		if (IS_ERR(bh))
			goto out;
		memcpy(AFFS_DATA(bh), data + from, bsize);
		if (buffer_new(bh)) {
			AFFS_DATA_HEAD(bh)->ptype = cpu_to_be32(T_DATA);
			AFFS_DATA_HEAD(bh)->key = cpu_to_be32(inode->i_ino);
			AFFS_DATA_HEAD(bh)->sequence = cpu_to_be32(bidx);
			AFFS_DATA_HEAD(bh)->size = cpu_to_be32(bsize);
			AFFS_DATA_HEAD(bh)->next = 0;
			bh->b_state &= ~(1UL << BH_New);
			if (prev_bh) {
				u32 tmp = be32_to_cpu(AFFS_DATA_HEAD(prev_bh)->next);
				if (tmp)
					affs_warning(sb, "commit_write_ofs", "next block already set for %d (%d)", bidx, tmp);
				AFFS_DATA_HEAD(prev_bh)->next = cpu_to_be32(bh->b_blocknr);
				affs_adjust_checksum(prev_bh, bh->b_blocknr - tmp);
				mark_buffer_dirty_inode(prev_bh, inode);
			}
		}
		affs_brelse(prev_bh);
		affs_fix_checksum(sb, bh);
		mark_buffer_dirty_inode(bh, inode);
		written += bsize;
		from += bsize;
		bidx++;
	}
	if (from < to) {
		prev_bh = bh;
		bh = affs_bread_ino(inode, bidx, 1);
		if (IS_ERR(bh))
			goto out;
		tmp = min(bsize, to - from);
		BUG_ON(tmp > bsize);
		memcpy(AFFS_DATA(bh), data + from, tmp);
		if (buffer_new(bh)) {
			AFFS_DATA_HEAD(bh)->ptype = cpu_to_be32(T_DATA);
			AFFS_DATA_HEAD(bh)->key = cpu_to_be32(inode->i_ino);
			AFFS_DATA_HEAD(bh)->sequence = cpu_to_be32(bidx);
			AFFS_DATA_HEAD(bh)->size = cpu_to_be32(tmp);
			AFFS_DATA_HEAD(bh)->next = 0;
			bh->b_state &= ~(1UL << BH_New);
			if (prev_bh) {
				u32 tmp = be32_to_cpu(AFFS_DATA_HEAD(prev_bh)->next);
				if (tmp)
					affs_warning(sb, "commit_write_ofs", "next block already set for %d (%d)", bidx, tmp);
				AFFS_DATA_HEAD(prev_bh)->next = cpu_to_be32(bh->b_blocknr);
				affs_adjust_checksum(prev_bh, bh->b_blocknr - tmp);
				mark_buffer_dirty_inode(prev_bh, inode);
			}
		} else if (be32_to_cpu(AFFS_DATA_HEAD(bh)->size) < tmp)
			AFFS_DATA_HEAD(bh)->size = cpu_to_be32(tmp);
		affs_brelse(prev_bh);
		affs_fix_checksum(sb, bh);
		mark_buffer_dirty_inode(bh, inode);
		written += tmp;
		from += tmp;
		bidx++;
	}
	SetPageUptodate(page);

done:
	affs_brelse(bh);
	tmp = (page->index << PAGE_CACHE_SHIFT) + from;
	if (tmp > inode->i_size)
		inode->i_size = AFFS_I(inode)->mmu_private = tmp;

	unlock_page(page);
	page_cache_release(page);

	return written;

out:
	bh = prev_bh;
	if (!written)
		written = PTR_ERR(bh);
	goto done;
}