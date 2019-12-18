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
struct super_block {int dummy; } ;
struct reiserfs_journal_desc {int dummy; } ;
struct reiserfs_journal_commit {int dummy; } ;
struct buffer_head {unsigned long b_blocknr; scalar_t__ b_data; } ;
struct TYPE_2__ {unsigned long j_trans_max; } ;

/* Variables and functions */
 int /*<<< orphan*/  JOURNAL_DESC_MAGIC ; 
 int /*<<< orphan*/  REISERFS_DEBUG_CODE ; 
 TYPE_1__* SB_JOURNAL (struct super_block*) ; 
 unsigned long SB_ONDISK_JOURNAL_1st_BLOCK (struct super_block*) ; 
 unsigned long SB_ONDISK_JOURNAL_SIZE (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 unsigned long get_commit_trans_id (struct reiserfs_journal_commit*) ; 
 unsigned int get_commit_trans_len (struct reiserfs_journal_commit*) ; 
 unsigned long get_desc_mount_id (struct reiserfs_journal_desc*) ; 
 unsigned int get_desc_trans_id (struct reiserfs_journal_desc*) ; 
 unsigned long get_desc_trans_len (struct reiserfs_journal_desc*) ; 
 int /*<<< orphan*/  get_journal_desc_magic (struct buffer_head*) ; 
 struct buffer_head* journal_bread (struct super_block*,unsigned long) ; 
 scalar_t__ journal_compare_desc_commit (struct super_block*,struct reiserfs_journal_desc*,struct reiserfs_journal_commit*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  reiserfs_debug (struct super_block*,int /*<<< orphan*/ ,char*,unsigned long,...) ; 
 int /*<<< orphan*/  reiserfs_warning (struct super_block*,char*,char*,unsigned long) ; 

__attribute__((used)) static int journal_transaction_is_valid(struct super_block *sb,
					struct buffer_head *d_bh,
					unsigned int *oldest_invalid_trans_id,
					unsigned long *newest_mount_id)
{
	struct reiserfs_journal_desc *desc;
	struct reiserfs_journal_commit *commit;
	struct buffer_head *c_bh;
	unsigned long offset;

	if (!d_bh)
		return 0;

	desc = (struct reiserfs_journal_desc *)d_bh->b_data;
	if (get_desc_trans_len(desc) > 0
	    && !memcmp(get_journal_desc_magic(d_bh), JOURNAL_DESC_MAGIC, 8)) {
		if (oldest_invalid_trans_id && *oldest_invalid_trans_id
		    && get_desc_trans_id(desc) > *oldest_invalid_trans_id) {
			reiserfs_debug(sb, REISERFS_DEBUG_CODE,
				       "journal-986: transaction "
				       "is valid returning because trans_id %d is greater than "
				       "oldest_invalid %lu",
				       get_desc_trans_id(desc),
				       *oldest_invalid_trans_id);
			return 0;
		}
		if (newest_mount_id
		    && *newest_mount_id > get_desc_mount_id(desc)) {
			reiserfs_debug(sb, REISERFS_DEBUG_CODE,
				       "journal-1087: transaction "
				       "is valid returning because mount_id %d is less than "
				       "newest_mount_id %lu",
				       get_desc_mount_id(desc),
				       *newest_mount_id);
			return -1;
		}
		if (get_desc_trans_len(desc) > SB_JOURNAL(sb)->j_trans_max) {
			reiserfs_warning(sb, "journal-2018",
					 "Bad transaction length %d "
					 "encountered, ignoring transaction",
					 get_desc_trans_len(desc));
			return -1;
		}
		offset = d_bh->b_blocknr - SB_ONDISK_JOURNAL_1st_BLOCK(sb);

		/* ok, we have a journal description block, lets see if the transaction was valid */
		c_bh =
		    journal_bread(sb,
				  SB_ONDISK_JOURNAL_1st_BLOCK(sb) +
				  ((offset + get_desc_trans_len(desc) +
				    1) % SB_ONDISK_JOURNAL_SIZE(sb)));
		if (!c_bh)
			return 0;
		commit = (struct reiserfs_journal_commit *)c_bh->b_data;
		if (journal_compare_desc_commit(sb, desc, commit)) {
			reiserfs_debug(sb, REISERFS_DEBUG_CODE,
				       "journal_transaction_is_valid, commit offset %ld had bad "
				       "time %d or length %d",
				       c_bh->b_blocknr -
				       SB_ONDISK_JOURNAL_1st_BLOCK(sb),
				       get_commit_trans_id(commit),
				       get_commit_trans_len(commit));
			brelse(c_bh);
			if (oldest_invalid_trans_id) {
				*oldest_invalid_trans_id =
				    get_desc_trans_id(desc);
				reiserfs_debug(sb, REISERFS_DEBUG_CODE,
					       "journal-1004: "
					       "transaction_is_valid setting oldest invalid trans_id "
					       "to %d",
					       get_desc_trans_id(desc));
			}
			return -1;
		}
		brelse(c_bh);
		reiserfs_debug(sb, REISERFS_DEBUG_CODE,
			       "journal-1006: found valid "
			       "transaction start offset %llu, len %d id %d",
			       d_bh->b_blocknr -
			       SB_ONDISK_JOURNAL_1st_BLOCK(sb),
			       get_desc_trans_len(desc),
			       get_desc_trans_id(desc));
		return 1;
	} else {
		return 0;
	}
}