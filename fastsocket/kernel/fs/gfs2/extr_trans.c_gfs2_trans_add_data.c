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
struct gfs2_trans {int tr_touched; int /*<<< orphan*/  tr_num_databuf_new; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_log_le_databuf; int /*<<< orphan*/  sd_log_num_databuf; } ;
struct gfs2_inode {int dummy; } ;
struct gfs2_glock {int /*<<< orphan*/  gl_flags; struct gfs2_sbd* gl_sbd; } ;
struct gfs2_bufdata {int /*<<< orphan*/  bd_list; int /*<<< orphan*/  bd_bh; struct gfs2_glock* bd_gl; } ;
struct buffer_head {struct gfs2_bufdata* b_private; TYPE_1__* b_page; } ;
struct address_space {int /*<<< orphan*/  host; } ;
struct TYPE_4__ {struct gfs2_trans* journal_info; } ;
struct TYPE_3__ {struct address_space* mapping; } ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLF_DIRTY ; 
 int /*<<< orphan*/  GLF_LFLUSH ; 
 TYPE_2__* current ; 
 struct gfs2_bufdata* gfs2_alloc_bufdata (struct gfs2_glock*,struct buffer_head*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_assert (struct gfs2_sbd*,int) ; 
 int /*<<< orphan*/  gfs2_databuf_lops ; 
 int /*<<< orphan*/  gfs2_is_jdata (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_log_lock (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_log_unlock (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_ordered_add_inode (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_pin (struct gfs2_sbd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

void gfs2_trans_add_data(struct gfs2_glock *gl, struct buffer_head *bh)
{
	struct gfs2_trans *tr = current->journal_info;
	struct gfs2_sbd *sdp = gl->gl_sbd;
	struct address_space *mapping = bh->b_page->mapping;
	struct gfs2_inode *ip = GFS2_I(mapping->host);
	struct gfs2_bufdata *bd;

	if (!gfs2_is_jdata(ip)) {
		gfs2_ordered_add_inode(ip);
		return;
	}

	lock_buffer(bh);
	gfs2_log_lock(sdp);
	bd = bh->b_private;
	if (bd == NULL) {
		gfs2_log_unlock(sdp);
		unlock_buffer(bh);
		if (bh->b_private == NULL)
			bd = gfs2_alloc_bufdata(gl, bh, &gfs2_databuf_lops);
		lock_buffer(bh);
		gfs2_log_lock(sdp);
	}
	gfs2_assert(sdp, bd->bd_gl == gl);
	tr->tr_touched = 1;
	if (list_empty(&bd->bd_list)) {
		set_bit(GLF_LFLUSH, &bd->bd_gl->gl_flags);
		set_bit(GLF_DIRTY, &bd->bd_gl->gl_flags);
		gfs2_pin(sdp, bd->bd_bh);
		tr->tr_num_databuf_new++;
		sdp->sd_log_num_databuf++;
		list_add_tail(&bd->bd_list, &sdp->sd_log_le_databuf);
	}
	gfs2_log_unlock(sdp);
	unlock_buffer(bh);
}