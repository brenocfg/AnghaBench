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
typedef  int /*<<< orphan*/  u64 ;
struct gfs2_trans {scalar_t__ tr_touched; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_flags; } ;
struct gfs2_glock {struct gfs2_sbd* gl_sbd; } ;
struct buffer_head {int /*<<< orphan*/  b_end_io; } ;
struct TYPE_2__ {struct gfs2_trans* journal_info; } ;

/* Variables and functions */
 int BIO_RW_META ; 
 int /*<<< orphan*/  CREATE ; 
 int DIO_WAIT ; 
 int EIO ; 
 int READ_SYNC ; 
 int /*<<< orphan*/  SDF_SHUTDOWN ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_uptodate (struct buffer_head*) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  end_buffer_read_sync ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 struct buffer_head* gfs2_getbuf (struct gfs2_glock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_io_error_bh (struct gfs2_sbd*,struct buffer_head*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  submit_bh (int,struct buffer_head*) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  wait_on_buffer (struct buffer_head*) ; 

int gfs2_meta_read(struct gfs2_glock *gl, u64 blkno, int flags,
		   struct buffer_head **bhp)
{
	struct gfs2_sbd *sdp = gl->gl_sbd;
	struct buffer_head *bh;

	if (unlikely(test_bit(SDF_SHUTDOWN, &sdp->sd_flags)))
		return -EIO;

	*bhp = bh = gfs2_getbuf(gl, blkno, CREATE);

	lock_buffer(bh);
	if (buffer_uptodate(bh)) {
		unlock_buffer(bh);
		return 0;
	}
	bh->b_end_io = end_buffer_read_sync;
	get_bh(bh);
	submit_bh(READ_SYNC | (1 << BIO_RW_META), bh);
	if (!(flags & DIO_WAIT))
		return 0;

	wait_on_buffer(bh);
	if (unlikely(!buffer_uptodate(bh))) {
		struct gfs2_trans *tr = current->journal_info;
		if (tr && tr->tr_touched)
			gfs2_io_error_bh(sdp, bh);
		brelse(bh);
		return -EIO;
	}

	return 0;
}