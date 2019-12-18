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
typedef  int /*<<< orphan*/  transaction_t ;
struct journal_head {scalar_t__ b_cp_transaction; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BJ_Forget ; 
 int /*<<< orphan*/  JBUFFER_TRACE (struct journal_head*,char*) ; 
 int /*<<< orphan*/  __brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  __journal_file_buffer (struct journal_head*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __journal_unfile_buffer (struct journal_head*) ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 struct buffer_head* jh2bh (struct journal_head*) ; 
 int /*<<< orphan*/  journal_remove_journal_head (struct buffer_head*) ; 

__attribute__((used)) static int __dispose_buffer(struct journal_head *jh, transaction_t *transaction)
{
	int may_free = 1;
	struct buffer_head *bh = jh2bh(jh);

	__journal_unfile_buffer(jh);

	if (jh->b_cp_transaction) {
		JBUFFER_TRACE(jh, "on running+cp transaction");
		/*
		 * We don't want to write the buffer anymore, clear the
		 * bit so that we don't confuse checks in
		 * __journal_file_buffer
		 */
		clear_buffer_dirty(bh);
		__journal_file_buffer(jh, transaction, BJ_Forget);
		may_free = 0;
	} else {
		JBUFFER_TRACE(jh, "on running transaction");
		journal_remove_journal_head(bh);
		__brelse(bh);
	}
	return may_free;
}