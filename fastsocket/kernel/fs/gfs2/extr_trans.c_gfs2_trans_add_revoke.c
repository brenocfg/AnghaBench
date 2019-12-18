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
struct gfs2_trans {int tr_touched; int /*<<< orphan*/  tr_num_revoke; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_log_le_revoke; int /*<<< orphan*/  sd_log_num_revoke; } ;
struct gfs2_glock {int /*<<< orphan*/  gl_flags; int /*<<< orphan*/  gl_revokes; } ;
struct gfs2_bufdata {int /*<<< orphan*/  bd_list; int /*<<< orphan*/ * bd_ops; int /*<<< orphan*/  bd_ail_gl_list; int /*<<< orphan*/  bd_ail_st_list; struct gfs2_glock* bd_gl; } ;
struct TYPE_2__ {struct gfs2_trans* journal_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GLF_LFLUSH ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 TYPE_1__* current ; 
 int /*<<< orphan*/  gfs2_revoke_lops ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void gfs2_trans_add_revoke(struct gfs2_sbd *sdp, struct gfs2_bufdata *bd)
{
	struct gfs2_glock *gl = bd->bd_gl;
	struct gfs2_trans *tr = current->journal_info;

	BUG_ON(!list_empty(&bd->bd_list));
	BUG_ON(!list_empty(&bd->bd_ail_st_list));
	BUG_ON(!list_empty(&bd->bd_ail_gl_list));
	bd->bd_ops = &gfs2_revoke_lops;
	tr->tr_touched = 1;
	tr->tr_num_revoke++;
	sdp->sd_log_num_revoke++;
	atomic_inc(&gl->gl_revokes);
	set_bit(GLF_LFLUSH, &gl->gl_flags);
	list_add(&bd->bd_list, &sdp->sd_log_le_revoke);
}