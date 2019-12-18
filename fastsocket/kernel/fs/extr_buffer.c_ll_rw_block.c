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
 int SWRITE ; 
 int SWRITE_SYNC ; 
 int SWRITE_SYNC_PLUG ; 
 int WRITE ; 
 int WRITE_SYNC ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  end_buffer_read_sync ; 
 int /*<<< orphan*/  end_buffer_write_sync ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  submit_bh (int,struct buffer_head*) ; 
 scalar_t__ test_clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  trylock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

void ll_rw_block(int rw, int nr, struct buffer_head *bhs[])
{
	int i;

	for (i = 0; i < nr; i++) {
		struct buffer_head *bh = bhs[i];

		if (rw == SWRITE || rw == SWRITE_SYNC || rw == SWRITE_SYNC_PLUG)
			lock_buffer(bh);
		else if (!trylock_buffer(bh))
			continue;

		if (rw == WRITE || rw == SWRITE || rw == SWRITE_SYNC ||
		    rw == SWRITE_SYNC_PLUG) {
			if (test_clear_buffer_dirty(bh)) {
				bh->b_end_io = end_buffer_write_sync;
				get_bh(bh);
				if (rw == SWRITE_SYNC)
					submit_bh(WRITE_SYNC, bh);
				else
					submit_bh(WRITE, bh);
				continue;
			}
		} else {
			if (!buffer_uptodate(bh)) {
				bh->b_end_io = end_buffer_read_sync;
				get_bh(bh);
				submit_bh(rw, bh);
				continue;
			}
		}
		unlock_buffer(bh);
	}
}