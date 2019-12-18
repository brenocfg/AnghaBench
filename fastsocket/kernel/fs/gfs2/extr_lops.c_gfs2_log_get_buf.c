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
typedef  int /*<<< orphan*/  u64 ;
struct gfs2_sbd {int /*<<< orphan*/  sd_log_in_flight; int /*<<< orphan*/  sd_vfs; int /*<<< orphan*/  sd_log_flush_head; } ;
struct buffer_head {int /*<<< orphan*/  b_end_io; struct gfs2_sbd* b_private; int /*<<< orphan*/  b_size; int /*<<< orphan*/  b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  gfs2_log_bmap (struct gfs2_sbd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_log_incr_head (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_log_write_endio ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct buffer_head* sb_getblk (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 

__attribute__((used)) static struct buffer_head *gfs2_log_get_buf(struct gfs2_sbd *sdp)
{
	u64 blkno = gfs2_log_bmap(sdp, sdp->sd_log_flush_head);
	struct buffer_head *bh;

	bh = sb_getblk(sdp->sd_vfs, blkno);
	lock_buffer(bh);
	memset(bh->b_data, 0, bh->b_size);
	set_buffer_uptodate(bh);
	clear_buffer_dirty(bh);
	gfs2_log_incr_head(sdp);
	atomic_inc(&sdp->sd_log_in_flight);
	bh->b_private = sdp;
	bh->b_end_io = gfs2_log_write_endio;

	return bh;
}