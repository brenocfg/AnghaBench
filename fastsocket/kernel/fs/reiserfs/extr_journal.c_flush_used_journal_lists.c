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
struct TYPE_2__ {int /*<<< orphan*/ * next; } ;
struct reiserfs_journal_list {scalar_t__ j_trans_id; TYPE_1__ j_list; int /*<<< orphan*/  j_state; int /*<<< orphan*/  j_nonzerolen; int /*<<< orphan*/  j_commit_left; } ;
struct reiserfs_journal {int /*<<< orphan*/  j_journal_list; } ;

/* Variables and functions */
 struct reiserfs_journal_list* JOURNAL_LIST_ENTRY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_TOUCHED ; 
 struct reiserfs_journal* SB_JOURNAL (struct super_block*) ; 
 unsigned long atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_journal_list (struct super_block*,struct reiserfs_journal_list*,int) ; 
 int kupdate_transactions (struct super_block*,struct reiserfs_journal_list*,struct reiserfs_journal_list**,unsigned int*,unsigned long,int) ; 
 scalar_t__ reiserfs_data_log (struct super_block*) ; 

__attribute__((used)) static int flush_used_journal_lists(struct super_block *s,
				    struct reiserfs_journal_list *jl)
{
	unsigned long len = 0;
	unsigned long cur_len;
	int ret;
	int i;
	int limit = 256;
	struct reiserfs_journal_list *tjl;
	struct reiserfs_journal_list *flush_jl;
	unsigned int trans_id;
	struct reiserfs_journal *journal = SB_JOURNAL(s);

	flush_jl = tjl = jl;

	/* in data logging mode, try harder to flush a lot of blocks */
	if (reiserfs_data_log(s))
		limit = 1024;
	/* flush for 256 transactions or limit blocks, whichever comes first */
	for (i = 0; i < 256 && len < limit; i++) {
		if (atomic_read(&tjl->j_commit_left) ||
		    tjl->j_trans_id < jl->j_trans_id) {
			break;
		}
		cur_len = atomic_read(&tjl->j_nonzerolen);
		if (cur_len > 0) {
			tjl->j_state &= ~LIST_TOUCHED;
		}
		len += cur_len;
		flush_jl = tjl;
		if (tjl->j_list.next == &journal->j_journal_list)
			break;
		tjl = JOURNAL_LIST_ENTRY(tjl->j_list.next);
	}
	/* try to find a group of blocks we can flush across all the
	 ** transactions, but only bother if we've actually spanned
	 ** across multiple lists
	 */
	if (flush_jl != jl) {
		ret = kupdate_transactions(s, jl, &tjl, &trans_id, len, i);
	}
	flush_journal_list(s, flush_jl, 1);
	return 0;
}