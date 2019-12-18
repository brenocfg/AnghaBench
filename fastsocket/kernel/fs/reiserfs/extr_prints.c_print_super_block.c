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
struct reiserfs_super_block {int dummy; } ;
struct buffer_head {int b_blocknr; int /*<<< orphan*/  b_bdev; scalar_t__ b_data; } ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 scalar_t__ REISERFS_VERSION_2 ; 
 int /*<<< orphan*/  bdevname (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_reiserfs_3_5 (struct reiserfs_super_block*) ; 
 scalar_t__ is_reiserfs_3_6 (struct reiserfs_super_block*) ; 
 scalar_t__ is_reiserfs_jr (struct reiserfs_super_block*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int reiserfs_hashname (int /*<<< orphan*/ ) ; 
 int sb_block_count (struct reiserfs_super_block*) ; 
 int sb_blocksize (struct reiserfs_super_block*) ; 
 int sb_bmap_nr (struct reiserfs_super_block*) ; 
 int sb_free_blocks (struct reiserfs_super_block*) ; 
 int sb_fs_state (struct reiserfs_super_block*) ; 
 int /*<<< orphan*/  sb_hash_function_code (struct reiserfs_super_block*) ; 
 int sb_jp_journal_1st_block (struct reiserfs_super_block*) ; 
 int sb_jp_journal_dev (struct reiserfs_super_block*) ; 
 int sb_jp_journal_size (struct reiserfs_super_block*) ; 
 int sb_reserved_for_journal (struct reiserfs_super_block*) ; 
 int sb_root_block (struct reiserfs_super_block*) ; 
 int sb_tree_height (struct reiserfs_super_block*) ; 
 scalar_t__ sb_version (struct reiserfs_super_block*) ; 

__attribute__((used)) static int print_super_block(struct buffer_head *bh)
{
	struct reiserfs_super_block *rs =
	    (struct reiserfs_super_block *)(bh->b_data);
	int skipped, data_blocks;
	char *version;
	char b[BDEVNAME_SIZE];

	if (is_reiserfs_3_5(rs)) {
		version = "3.5";
	} else if (is_reiserfs_3_6(rs)) {
		version = "3.6";
	} else if (is_reiserfs_jr(rs)) {
		version = ((sb_version(rs) == REISERFS_VERSION_2) ?
			   "3.6" : "3.5");
	} else {
		return 1;
	}

	printk("%s\'s super block is in block %llu\n", bdevname(bh->b_bdev, b),
	       (unsigned long long)bh->b_blocknr);
	printk("Reiserfs version %s\n", version);
	printk("Block count %u\n", sb_block_count(rs));
	printk("Blocksize %d\n", sb_blocksize(rs));
	printk("Free blocks %u\n", sb_free_blocks(rs));
	// FIXME: this would be confusing if
	// someone stores reiserfs super block in some data block ;)
//    skipped = (bh->b_blocknr * bh->b_size) / sb_blocksize(rs);
	skipped = bh->b_blocknr;
	data_blocks = sb_block_count(rs) - skipped - 1 - sb_bmap_nr(rs) -
	    (!is_reiserfs_jr(rs) ? sb_jp_journal_size(rs) +
	     1 : sb_reserved_for_journal(rs)) - sb_free_blocks(rs);
	printk
	    ("Busy blocks (skipped %d, bitmaps - %d, journal (or reserved) blocks - %d\n"
	     "1 super block, %d data blocks\n", skipped, sb_bmap_nr(rs),
	     (!is_reiserfs_jr(rs) ? (sb_jp_journal_size(rs) + 1) :
	      sb_reserved_for_journal(rs)), data_blocks);
	printk("Root block %u\n", sb_root_block(rs));
	printk("Journal block (first) %d\n", sb_jp_journal_1st_block(rs));
	printk("Journal dev %d\n", sb_jp_journal_dev(rs));
	printk("Journal orig size %d\n", sb_jp_journal_size(rs));
	printk("FS state %d\n", sb_fs_state(rs));
	printk("Hash function \"%s\"\n",
	       reiserfs_hashname(sb_hash_function_code(rs)));

	printk("Tree height %d\n", sb_tree_height(rs));
	return 0;
}