#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_3__ {int /*<<< orphan*/  sb_bsize; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_log_in_flight; TYPE_2__* sd_vfs; TYPE_1__ sd_sb; int /*<<< orphan*/  sd_log_flush_head; } ;
struct buffer_head {int b_state; int /*<<< orphan*/  b_end_io; struct buffer_head* b_private; int /*<<< orphan*/  b_bdev; int /*<<< orphan*/  b_size; int /*<<< orphan*/  b_blocknr; int /*<<< orphan*/  b_page; int /*<<< orphan*/  b_count; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_bdev; } ;

/* Variables and functions */
 int BH_Lock ; 
 int BH_Mapped ; 
 int BH_Uptodate ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bh_offset (struct buffer_head*) ; 
 int /*<<< orphan*/  gfs2_bh_pool ; 
 int /*<<< orphan*/  gfs2_fake_write_endio ; 
 int /*<<< orphan*/  gfs2_log_bmap (struct gfs2_sbd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_log_incr_head (struct gfs2_sbd*) ; 
 struct buffer_head* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bh_page (struct buffer_head*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  submit_bh (int /*<<< orphan*/ ,struct buffer_head*) ; 

__attribute__((used)) static void gfs2_log_write_buf(struct gfs2_sbd *sdp, struct buffer_head *real)
{
	u64 blkno = gfs2_log_bmap(sdp, sdp->sd_log_flush_head);
	struct buffer_head *bh;

	bh = mempool_alloc(gfs2_bh_pool, GFP_NOFS);
	atomic_set(&bh->b_count, 1);
	bh->b_state = (1 << BH_Mapped) | (1 << BH_Uptodate) | (1 << BH_Lock);
	set_bh_page(bh, real->b_page, bh_offset(real));
	bh->b_blocknr = blkno;
	bh->b_size = sdp->sd_sb.sb_bsize;
	bh->b_bdev = sdp->sd_vfs->s_bdev;
	bh->b_private = real;
	bh->b_end_io = gfs2_fake_write_endio;

	gfs2_log_incr_head(sdp);
	atomic_inc(&sdp->sd_log_in_flight);

	submit_bh(WRITE, bh);
}