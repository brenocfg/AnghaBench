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
struct gfs2_sbd {int /*<<< orphan*/  sd_log_flush_wait; int /*<<< orphan*/  sd_log_in_flight; } ;
struct buffer_head {struct gfs2_sbd* b_private; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  end_buffer_write_sync (struct buffer_head*,int) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gfs2_log_write_endio(struct buffer_head *bh, int uptodate)
{
	struct gfs2_sbd *sdp = bh->b_private;
	bh->b_private = NULL;

	end_buffer_write_sync(bh, uptodate);
	if (atomic_dec_and_test(&sdp->sd_log_in_flight))
		wake_up(&sdp->sd_log_flush_wait);
}