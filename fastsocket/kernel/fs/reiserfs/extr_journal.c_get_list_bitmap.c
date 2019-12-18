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
struct reiserfs_list_bitmap {struct reiserfs_journal_list* journal_list; } ;
struct reiserfs_journal_list {int dummy; } ;
struct reiserfs_journal {int j_list_bitmap_index; struct reiserfs_list_bitmap* j_list_bitmap; } ;

/* Variables and functions */
 int JOURNAL_NUM_BITMAPS ; 
 struct reiserfs_journal* SB_JOURNAL (struct super_block*) ; 
 int /*<<< orphan*/  flush_commit_list (struct super_block*,struct reiserfs_journal_list*,int) ; 

__attribute__((used)) static struct reiserfs_list_bitmap *get_list_bitmap(struct super_block *sb,
						    struct reiserfs_journal_list
						    *jl)
{
	int i, j;
	struct reiserfs_journal *journal = SB_JOURNAL(sb);
	struct reiserfs_list_bitmap *jb = NULL;

	for (j = 0; j < (JOURNAL_NUM_BITMAPS * 3); j++) {
		i = journal->j_list_bitmap_index;
		journal->j_list_bitmap_index = (i + 1) % JOURNAL_NUM_BITMAPS;
		jb = journal->j_list_bitmap + i;
		if (journal->j_list_bitmap[i].journal_list) {
			flush_commit_list(sb,
					  journal->j_list_bitmap[i].
					  journal_list, 1);
			if (!journal->j_list_bitmap[i].journal_list) {
				break;
			}
		} else {
			break;
		}
	}
	if (jb->journal_list) {	/* double check to make sure if flushed correctly */
		return NULL;
	}
	jb->journal_list = jl;
	return jb;
}