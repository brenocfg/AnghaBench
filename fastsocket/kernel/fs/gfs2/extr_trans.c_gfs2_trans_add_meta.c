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
struct gfs2_sbd {int dummy; } ;
struct gfs2_glock {struct gfs2_sbd* gl_sbd; } ;
struct gfs2_bufdata {struct gfs2_glock* bd_gl; } ;
struct buffer_head {int /*<<< orphan*/  b_page; struct gfs2_bufdata* b_private; } ;

/* Variables and functions */
 struct gfs2_bufdata* gfs2_alloc_bufdata (struct gfs2_glock*,struct buffer_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_assert (struct gfs2_sbd*,int) ; 
 int /*<<< orphan*/  gfs2_buf_lops ; 
 int /*<<< orphan*/  gfs2_log_lock (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_log_unlock (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  lock_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meta_lo_add (struct gfs2_sbd*,struct gfs2_bufdata*) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  unlock_page (int /*<<< orphan*/ ) ; 

void gfs2_trans_add_meta(struct gfs2_glock *gl, struct buffer_head *bh)
{

	struct gfs2_sbd *sdp = gl->gl_sbd;
	struct gfs2_bufdata *bd;

	lock_buffer(bh);
	gfs2_log_lock(sdp);
	bd = bh->b_private;
	if (bd == NULL) {
		gfs2_log_unlock(sdp);
		unlock_buffer(bh);
		lock_page(bh->b_page);
		if (bh->b_private == NULL)
			bd = gfs2_alloc_bufdata(gl, bh, &gfs2_buf_lops);
		unlock_page(bh->b_page);
		lock_buffer(bh);
		gfs2_log_lock(sdp);
	}
	gfs2_assert(sdp, bd->bd_gl == gl);
	meta_lo_add(sdp, bd);
	gfs2_log_unlock(sdp);
	unlock_buffer(bh);
}