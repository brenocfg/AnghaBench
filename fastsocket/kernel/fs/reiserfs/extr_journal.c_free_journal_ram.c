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
struct super_block {int dummy; } ;
struct reiserfs_journal {scalar_t__ j_header_bh; int /*<<< orphan*/  j_list_bitmap; struct reiserfs_journal* j_cnode_free_orig; int /*<<< orphan*/  j_num_lists; int /*<<< orphan*/  j_current_jl; } ;

/* Variables and functions */
 struct reiserfs_journal* SB_JOURNAL (struct super_block*) ; 
 int /*<<< orphan*/  brelse (scalar_t__) ; 
 int /*<<< orphan*/  free_bitmap_nodes (struct super_block*) ; 
 int /*<<< orphan*/  free_list_bitmaps (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_journal_dev (struct super_block*,struct reiserfs_journal*) ; 
 int /*<<< orphan*/  vfree (struct reiserfs_journal*) ; 

__attribute__((used)) static void free_journal_ram(struct super_block *sb)
{
	struct reiserfs_journal *journal = SB_JOURNAL(sb);
	kfree(journal->j_current_jl);
	journal->j_num_lists--;

	vfree(journal->j_cnode_free_orig);
	free_list_bitmaps(sb, journal->j_list_bitmap);
	free_bitmap_nodes(sb);	/* must be after free_list_bitmaps */
	if (journal->j_header_bh) {
		brelse(journal->j_header_bh);
	}
	/* j_header_bh is on the journal dev, make sure not to release the journal
	 * dev until we brelse j_header_bh
	 */
	release_journal_dev(sb, journal);
	vfree(journal);
}