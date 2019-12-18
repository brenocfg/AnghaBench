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
struct lm_lockstruct {int /*<<< orphan*/  ls_dlm; } ;
struct TYPE_4__ {int /*<<< orphan*/  sb_lkid; } ;
struct gfs2_glock {TYPE_2__ gl_lksb; TYPE_1__* gl_sbd; } ;
struct TYPE_3__ {struct lm_lockstruct sd_lockstruct; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_LKF_CANCEL ; 
 int /*<<< orphan*/  dlm_unlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct gfs2_glock*) ; 

__attribute__((used)) static void gdlm_cancel(struct gfs2_glock *gl)
{
	struct lm_lockstruct *ls = &gl->gl_sbd->sd_lockstruct;
	dlm_unlock(ls->ls_dlm, gl->gl_lksb.sb_lkid, DLM_LKF_CANCEL, NULL, gl);
}