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
 int /*<<< orphan*/  end_buffer_write_sync ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  submit_bh (int,struct buffer_head*) ; 
 int /*<<< orphan*/  test_clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

void write_dirty_buffer(struct buffer_head *bh, int rw)
{
	lock_buffer(bh);
	if (!test_clear_buffer_dirty(bh)) {
		unlock_buffer(bh);
		return;
	}
	bh->b_end_io = end_buffer_write_sync;
	get_bh(bh);
	submit_bh(rw, bh);
}