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
struct gfs2_inode {struct gfs2_glock* i_gl; } ;
struct gfs2_glock {int /*<<< orphan*/  gl_spin; int /*<<< orphan*/  gl_flags; int /*<<< orphan*/  gl_sbd; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLF_LOCK ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_assert_withdraw (int /*<<< orphan*/ ,int) ; 
 int gfs2_truncatei_resume (struct gfs2_inode*) ; 
 int /*<<< orphan*/  run_queue (struct gfs2_glock*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void gfs2_glock_finish_truncate(struct gfs2_inode *ip)
{
	struct gfs2_glock *gl = ip->i_gl;
	int ret;

	ret = gfs2_truncatei_resume(ip);
	gfs2_assert_withdraw(gl->gl_sbd, ret == 0);

	spin_lock(&gl->gl_spin);
	clear_bit(GLF_LOCK, &gl->gl_flags);
	run_queue(gl, 1);
	spin_unlock(&gl->gl_spin);
}