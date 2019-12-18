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
struct gfs2_sbd {TYPE_1__* sd_vfs; } ;
struct gfs2_inode {int dummy; } ;
struct gfs2_glock {scalar_t__ gl_demote_state; scalar_t__ gl_state; int /*<<< orphan*/  gl_delete; struct gfs2_sbd* gl_sbd; scalar_t__ gl_object; } ;
struct TYPE_2__ {int s_flags; } ;

/* Variables and functions */
 scalar_t__ LM_ST_SHARED ; 
 scalar_t__ LM_ST_UNLOCKED ; 
 int MS_RDONLY ; 
 int /*<<< orphan*/  gfs2_delete_workqueue ; 
 int /*<<< orphan*/  gfs2_glock_hold (struct gfs2_glock*) ; 
 int /*<<< orphan*/  gfs2_glock_put_nolock (struct gfs2_glock*) ; 
 scalar_t__ queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iopen_go_callback(struct gfs2_glock *gl, bool remote)
{
	struct gfs2_inode *ip = (struct gfs2_inode *)gl->gl_object;
	struct gfs2_sbd *sdp = gl->gl_sbd;

	if (!remote || (sdp->sd_vfs->s_flags & MS_RDONLY))
		return;

	if (gl->gl_demote_state == LM_ST_UNLOCKED &&
	    gl->gl_state == LM_ST_SHARED && ip) {
		gfs2_glock_hold(gl);
		if (queue_work(gfs2_delete_workqueue, &gl->gl_delete) == 0)
			gfs2_glock_put_nolock(gl);
	}
}