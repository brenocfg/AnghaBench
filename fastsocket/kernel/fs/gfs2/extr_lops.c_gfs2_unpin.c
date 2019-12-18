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
struct gfs2_sbd {int /*<<< orphan*/  sd_ail_lock; } ;
struct gfs2_glock {int /*<<< orphan*/  gl_flags; int /*<<< orphan*/  gl_ail_count; int /*<<< orphan*/  gl_ail_list; } ;
struct gfs2_bufdata {struct gfs2_glock* bd_gl; int /*<<< orphan*/  bd_ail_st_list; struct gfs2_ail* bd_ail; int /*<<< orphan*/  bd_ail_gl_list; } ;
struct gfs2_ail {int /*<<< orphan*/  ai_ail1_list; } ;
struct buffer_head {struct gfs2_bufdata* b_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GLF_LFLUSH ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ buffer_is_rgrp (struct gfs2_bufdata*) ; 
 int /*<<< orphan*/  buffer_pinned (struct buffer_head*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_buffer_pinned (struct buffer_head*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_buffer (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  maybe_release_space (struct gfs2_bufdata*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_gfs2_pin (struct gfs2_bufdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_buffer (struct buffer_head*) ; 

__attribute__((used)) static void gfs2_unpin(struct gfs2_sbd *sdp, struct buffer_head *bh,
		       struct gfs2_ail *ai)
{
	struct gfs2_bufdata *bd = bh->b_private;

	BUG_ON(!buffer_uptodate(bh));
	BUG_ON(!buffer_pinned(bh));

	lock_buffer(bh);
	mark_buffer_dirty(bh);
	clear_buffer_pinned(bh);

	if (buffer_is_rgrp(bd))
		maybe_release_space(bd);

	spin_lock(&sdp->sd_ail_lock);
	if (bd->bd_ail) {
		list_del(&bd->bd_ail_st_list);
		brelse(bh);
	} else {
		struct gfs2_glock *gl = bd->bd_gl;
		list_add(&bd->bd_ail_gl_list, &gl->gl_ail_list);
		atomic_inc(&gl->gl_ail_count);
	}
	bd->bd_ail = ai;
	list_add(&bd->bd_ail_st_list, &ai->ai_ail1_list);
	spin_unlock(&sdp->sd_ail_lock);

	clear_bit(GLF_LFLUSH, &bd->bd_gl->gl_flags);
	trace_gfs2_pin(bd, 0);
	unlock_buffer(bh);
}