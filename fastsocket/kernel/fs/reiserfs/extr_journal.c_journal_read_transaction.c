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
struct super_block {int /*<<< orphan*/  s_blocksize; } ;
struct reiserfs_journal_desc {int /*<<< orphan*/ * j_realblock; } ;
struct reiserfs_journal_commit {int /*<<< orphan*/ * j_realblock; } ;
struct reiserfs_journal {unsigned long j_start; unsigned int j_last_flush_trans_id; unsigned int j_trans_id; } ;
struct buffer_head {unsigned int b_blocknr; int /*<<< orphan*/  b_size; scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  READ ; 
 int /*<<< orphan*/  REISERFS_DEBUG_CODE ; 
 scalar_t__ SB_BLOCK_COUNT (struct super_block*) ; 
 struct reiserfs_journal* SB_JOURNAL (struct super_block*) ; 
 unsigned long SB_ONDISK_JOURNAL_1st_BLOCK (struct super_block*) ; 
 unsigned int SB_ONDISK_JOURNAL_SIZE (struct super_block*) ; 
 int /*<<< orphan*/  SWRITE ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  brelse_array (struct buffer_head**,int) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  get_commit_trans_id (struct reiserfs_journal_commit*) ; 
 int /*<<< orphan*/  get_commit_trans_len (struct reiserfs_journal_commit*) ; 
 unsigned long get_desc_mount_id (struct reiserfs_journal_desc*) ; 
 unsigned int get_desc_trans_id (struct reiserfs_journal_desc*) ; 
 unsigned int get_desc_trans_len (struct reiserfs_journal_desc*) ; 
 scalar_t__ is_block_in_log_or_reserved_area (struct super_block*,scalar_t__) ; 
 struct buffer_head* journal_bread (struct super_block*,unsigned int) ; 
 scalar_t__ journal_compare_desc_commit (struct super_block*,struct reiserfs_journal_desc*,struct reiserfs_journal_commit*) ; 
 struct buffer_head* journal_getblk (struct super_block*,unsigned int) ; 
 int journal_trans_half (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct buffer_head**) ; 
 struct buffer_head** kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ll_rw_block (int /*<<< orphan*/ ,int,struct buffer_head**) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_debug (struct super_block*,int /*<<< orphan*/ ,char*,unsigned long,...) ; 
 int /*<<< orphan*/  reiserfs_warning (struct super_block*,char*,char*) ; 
 struct buffer_head* sb_getblk (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

__attribute__((used)) static int journal_read_transaction(struct super_block *sb,
				    unsigned long cur_dblock,
				    unsigned long oldest_start,
				    unsigned int oldest_trans_id,
				    unsigned long newest_mount_id)
{
	struct reiserfs_journal *journal = SB_JOURNAL(sb);
	struct reiserfs_journal_desc *desc;
	struct reiserfs_journal_commit *commit;
	unsigned int trans_id = 0;
	struct buffer_head *c_bh;
	struct buffer_head *d_bh;
	struct buffer_head **log_blocks = NULL;
	struct buffer_head **real_blocks = NULL;
	unsigned int trans_offset;
	int i;
	int trans_half;

	d_bh = journal_bread(sb, cur_dblock);
	if (!d_bh)
		return 1;
	desc = (struct reiserfs_journal_desc *)d_bh->b_data;
	trans_offset = d_bh->b_blocknr - SB_ONDISK_JOURNAL_1st_BLOCK(sb);
	reiserfs_debug(sb, REISERFS_DEBUG_CODE, "journal-1037: "
		       "journal_read_transaction, offset %llu, len %d mount_id %d",
		       d_bh->b_blocknr - SB_ONDISK_JOURNAL_1st_BLOCK(sb),
		       get_desc_trans_len(desc), get_desc_mount_id(desc));
	if (get_desc_trans_id(desc) < oldest_trans_id) {
		reiserfs_debug(sb, REISERFS_DEBUG_CODE, "journal-1039: "
			       "journal_read_trans skipping because %lu is too old",
			       cur_dblock -
			       SB_ONDISK_JOURNAL_1st_BLOCK(sb));
		brelse(d_bh);
		return 1;
	}
	if (get_desc_mount_id(desc) != newest_mount_id) {
		reiserfs_debug(sb, REISERFS_DEBUG_CODE, "journal-1146: "
			       "journal_read_trans skipping because %d is != "
			       "newest_mount_id %lu", get_desc_mount_id(desc),
			       newest_mount_id);
		brelse(d_bh);
		return 1;
	}
	c_bh = journal_bread(sb, SB_ONDISK_JOURNAL_1st_BLOCK(sb) +
			     ((trans_offset + get_desc_trans_len(desc) + 1) %
			      SB_ONDISK_JOURNAL_SIZE(sb)));
	if (!c_bh) {
		brelse(d_bh);
		return 1;
	}
	commit = (struct reiserfs_journal_commit *)c_bh->b_data;
	if (journal_compare_desc_commit(sb, desc, commit)) {
		reiserfs_debug(sb, REISERFS_DEBUG_CODE,
			       "journal_read_transaction, "
			       "commit offset %llu had bad time %d or length %d",
			       c_bh->b_blocknr -
			       SB_ONDISK_JOURNAL_1st_BLOCK(sb),
			       get_commit_trans_id(commit),
			       get_commit_trans_len(commit));
		brelse(c_bh);
		brelse(d_bh);
		return 1;
	}
	trans_id = get_desc_trans_id(desc);
	/* now we know we've got a good transaction, and it was inside the valid time ranges */
	log_blocks = kmalloc(get_desc_trans_len(desc) *
			     sizeof(struct buffer_head *), GFP_NOFS);
	real_blocks = kmalloc(get_desc_trans_len(desc) *
			      sizeof(struct buffer_head *), GFP_NOFS);
	if (!log_blocks || !real_blocks) {
		brelse(c_bh);
		brelse(d_bh);
		kfree(log_blocks);
		kfree(real_blocks);
		reiserfs_warning(sb, "journal-1169",
				 "kmalloc failed, unable to mount FS");
		return -1;
	}
	/* get all the buffer heads */
	trans_half = journal_trans_half(sb->s_blocksize);
	for (i = 0; i < get_desc_trans_len(desc); i++) {
		log_blocks[i] =
		    journal_getblk(sb,
				   SB_ONDISK_JOURNAL_1st_BLOCK(sb) +
				   (trans_offset + 1 +
				    i) % SB_ONDISK_JOURNAL_SIZE(sb));
		if (i < trans_half) {
			real_blocks[i] =
			    sb_getblk(sb,
				      le32_to_cpu(desc->j_realblock[i]));
		} else {
			real_blocks[i] =
			    sb_getblk(sb,
				      le32_to_cpu(commit->
						  j_realblock[i - trans_half]));
		}
		if (real_blocks[i]->b_blocknr > SB_BLOCK_COUNT(sb)) {
			reiserfs_warning(sb, "journal-1207",
					 "REPLAY FAILURE fsck required! "
					 "Block to replay is outside of "
					 "filesystem");
			goto abort_replay;
		}
		/* make sure we don't try to replay onto log or reserved area */
		if (is_block_in_log_or_reserved_area
		    (sb, real_blocks[i]->b_blocknr)) {
			reiserfs_warning(sb, "journal-1204",
					 "REPLAY FAILURE fsck required! "
					 "Trying to replay onto a log block");
		      abort_replay:
			brelse_array(log_blocks, i);
			brelse_array(real_blocks, i);
			brelse(c_bh);
			brelse(d_bh);
			kfree(log_blocks);
			kfree(real_blocks);
			return -1;
		}
	}
	/* read in the log blocks, memcpy to the corresponding real block */
	ll_rw_block(READ, get_desc_trans_len(desc), log_blocks);
	for (i = 0; i < get_desc_trans_len(desc); i++) {
		wait_on_buffer(log_blocks[i]);
		if (!buffer_uptodate(log_blocks[i])) {
			reiserfs_warning(sb, "journal-1212",
					 "REPLAY FAILURE fsck required! "
					 "buffer write failed");
			brelse_array(log_blocks + i,
				     get_desc_trans_len(desc) - i);
			brelse_array(real_blocks, get_desc_trans_len(desc));
			brelse(c_bh);
			brelse(d_bh);
			kfree(log_blocks);
			kfree(real_blocks);
			return -1;
		}
		memcpy(real_blocks[i]->b_data, log_blocks[i]->b_data,
		       real_blocks[i]->b_size);
		set_buffer_uptodate(real_blocks[i]);
		brelse(log_blocks[i]);
	}
	/* flush out the real blocks */
	for (i = 0; i < get_desc_trans_len(desc); i++) {
		set_buffer_dirty(real_blocks[i]);
		ll_rw_block(SWRITE, 1, real_blocks + i);
	}
	for (i = 0; i < get_desc_trans_len(desc); i++) {
		wait_on_buffer(real_blocks[i]);
		if (!buffer_uptodate(real_blocks[i])) {
			reiserfs_warning(sb, "journal-1226",
					 "REPLAY FAILURE, fsck required! "
					 "buffer write failed");
			brelse_array(real_blocks + i,
				     get_desc_trans_len(desc) - i);
			brelse(c_bh);
			brelse(d_bh);
			kfree(log_blocks);
			kfree(real_blocks);
			return -1;
		}
		brelse(real_blocks[i]);
	}
	cur_dblock =
	    SB_ONDISK_JOURNAL_1st_BLOCK(sb) +
	    ((trans_offset + get_desc_trans_len(desc) +
	      2) % SB_ONDISK_JOURNAL_SIZE(sb));
	reiserfs_debug(sb, REISERFS_DEBUG_CODE,
		       "journal-1095: setting journal " "start to offset %ld",
		       cur_dblock - SB_ONDISK_JOURNAL_1st_BLOCK(sb));

	/* init starting values for the first transaction, in case this is the last transaction to be replayed. */
	journal->j_start = cur_dblock - SB_ONDISK_JOURNAL_1st_BLOCK(sb);
	journal->j_last_flush_trans_id = trans_id;
	journal->j_trans_id = trans_id + 1;
	/* check for trans_id overflow */
	if (journal->j_trans_id == 0)
		journal->j_trans_id = 10;
	brelse(c_bh);
	brelse(d_bh);
	kfree(log_blocks);
	kfree(real_blocks);
	return 0;
}