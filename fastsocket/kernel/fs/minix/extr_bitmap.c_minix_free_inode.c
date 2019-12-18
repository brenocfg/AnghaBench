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
struct super_block {int s_blocksize_bits; } ;
struct minix_sb_info {unsigned long s_ninodes; unsigned long s_imap_blocks; struct buffer_head** s_imap; } ;
struct inode {unsigned long i_ino; struct super_block* i_sb; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  bitmap_lock ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  minix_clear_inode (struct inode*) ; 
 struct minix_sb_info* minix_sb (struct super_block*) ; 
 int /*<<< orphan*/  minix_test_and_clear_bit (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void minix_free_inode(struct inode * inode)
{
	struct super_block *sb = inode->i_sb;
	struct minix_sb_info *sbi = minix_sb(inode->i_sb);
	struct buffer_head *bh;
	int k = sb->s_blocksize_bits + 3;
	unsigned long ino, bit;

	ino = inode->i_ino;
	if (ino < 1 || ino > sbi->s_ninodes) {
		printk("minix_free_inode: inode 0 or nonexistent inode\n");
		goto out;
	}
	bit = ino & ((1<<k) - 1);
	ino >>= k;
	if (ino >= sbi->s_imap_blocks) {
		printk("minix_free_inode: nonexistent imap in superblock\n");
		goto out;
	}

	minix_clear_inode(inode);	/* clear on-disk copy */

	bh = sbi->s_imap[ino];
	spin_lock(&bitmap_lock);
	if (!minix_test_and_clear_bit(bit, bh->b_data))
		printk("minix_free_inode: bit %lu already cleared\n", bit);
	spin_unlock(&bitmap_lock);
	mark_buffer_dirty(bh);
 out:
	clear_inode(inode);		/* clear in-memory copy */
}