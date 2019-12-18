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
struct buffer_head {int /*<<< orphan*/  b_end_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_journal_new (struct buffer_head*) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  reiserfs_end_buffer_io_sync ; 
 int /*<<< orphan*/  submit_bh (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int /*<<< orphan*/  test_clear_buffer_journal_test (struct buffer_head*) ; 

__attribute__((used)) static void submit_logged_buffer(struct buffer_head *bh)
{
	get_bh(bh);
	bh->b_end_io = reiserfs_end_buffer_io_sync;
	clear_buffer_journal_new(bh);
	clear_buffer_dirty(bh);
	if (!test_clear_buffer_journal_test(bh))
		BUG();
	if (!buffer_uptodate(bh))
		BUG();
	submit_bh(WRITE, bh);
}