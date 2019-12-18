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
struct journal_head {scalar_t__ b_jlist; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 scalar_t__ BJ_None ; 
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int /*<<< orphan*/  JBUFFER_TRACE (struct journal_head*,char*) ; 
 int /*<<< orphan*/  __brelse (struct buffer_head*) ; 
 int __jbd2_journal_remove_checkpoint (struct journal_head*) ; 
 int /*<<< orphan*/  buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_locked (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_write_io_error (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd2_journal_remove_journal_head (struct buffer_head*) ; 
 int /*<<< orphan*/  jbd_unlock_bh_state (struct buffer_head*) ; 
 struct buffer_head* jh2bh (struct journal_head*) ; 

__attribute__((used)) static int __try_to_free_cp_buf(struct journal_head *jh)
{
	int ret = 0;
	struct buffer_head *bh = jh2bh(jh);

	if (jh->b_jlist == BJ_None && !buffer_locked(bh) &&
	    !buffer_dirty(bh) && !buffer_write_io_error(bh)) {
		JBUFFER_TRACE(jh, "remove from checkpoint list");
		ret = __jbd2_journal_remove_checkpoint(jh) + 1;
		jbd_unlock_bh_state(bh);
		jbd2_journal_remove_journal_head(bh);
		BUFFER_TRACE(bh, "release");
		__brelse(bh);
	} else {
		jbd_unlock_bh_state(bh);
	}
	return ret;
}