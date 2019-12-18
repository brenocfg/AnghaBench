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
struct lm_lockstruct {int /*<<< orphan*/ * ls_dlm; } ;
struct gfs2_sbd {struct lm_lockstruct sd_lockstruct; } ;

/* Variables and functions */
 int /*<<< orphan*/  dlm_release_lockspace (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void gdlm_unmount(struct gfs2_sbd *sdp)
{
	struct lm_lockstruct *ls = &sdp->sd_lockstruct;

	if (ls->ls_dlm) {
		dlm_release_lockspace(ls->ls_dlm, 2);
		ls->ls_dlm = NULL;
	}
}