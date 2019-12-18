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
struct buffer_head {int /*<<< orphan*/  b_end_io; int /*<<< orphan*/  b_count; } ;

/* Variables and functions */
 int EIO ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ buffer_eopnotsupp (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_buffer_eopnotsupp (struct buffer_head*) ; 
 int /*<<< orphan*/  end_buffer_write_sync ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int submit_bh (int,struct buffer_head*) ; 
 scalar_t__ test_clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

int __sync_dirty_buffer(struct buffer_head *bh, int rw)
{
	int ret = 0;

	WARN_ON(atomic_read(&bh->b_count) < 1);
	lock_buffer(bh);
	if (test_clear_buffer_dirty(bh)) {
		get_bh(bh);
		bh->b_end_io = end_buffer_write_sync;
		ret = submit_bh(rw, bh);
		wait_on_buffer(bh);
		if (buffer_eopnotsupp(bh)) {
			clear_buffer_eopnotsupp(bh);
			ret = -EOPNOTSUPP;
		}
		if (!ret && !buffer_uptodate(bh))
			ret = -EIO;
	} else {
		unlock_buffer(bh);
	}
	return ret;
}