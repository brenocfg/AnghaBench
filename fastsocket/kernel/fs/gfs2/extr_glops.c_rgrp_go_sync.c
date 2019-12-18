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
struct gfs2_rgrpd {int dummy; } ;
struct gfs2_glock {scalar_t__ gl_state; int /*<<< orphan*/  gl_spin; struct gfs2_rgrpd* gl_object; int /*<<< orphan*/  gl_sbd; int /*<<< orphan*/  gl_flags; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GLF_DIRTY ; 
 scalar_t__ LM_ST_EXCLUSIVE ; 
 int filemap_fdatawait (struct address_space*) ; 
 int /*<<< orphan*/  filemap_fdatawrite (struct address_space*) ; 
 int /*<<< orphan*/  gfs2_ail_empty_gl (struct gfs2_glock*) ; 
 int /*<<< orphan*/  gfs2_free_clones (struct gfs2_rgrpd*) ; 
 struct address_space* gfs2_glock2aspace (struct gfs2_glock*) ; 
 int /*<<< orphan*/  gfs2_log_flush (int /*<<< orphan*/ ,struct gfs2_glock*) ; 
 int /*<<< orphan*/  mapping_set_error (struct address_space*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rgrp_go_sync(struct gfs2_glock *gl)
{
	struct address_space *metamapping = gfs2_glock2aspace(gl);
	struct gfs2_rgrpd *rgd;
	int error;

	if (!test_and_clear_bit(GLF_DIRTY, &gl->gl_flags))
		return;
	BUG_ON(gl->gl_state != LM_ST_EXCLUSIVE);

	gfs2_log_flush(gl->gl_sbd, gl);
	filemap_fdatawrite(metamapping);
	error = filemap_fdatawait(metamapping);
        mapping_set_error(metamapping, error);
	gfs2_ail_empty_gl(gl);

	spin_lock(&gl->gl_spin);
	rgd = gl->gl_object;
	if (rgd)
		gfs2_free_clones(rgd);
	spin_unlock(&gl->gl_spin);
}