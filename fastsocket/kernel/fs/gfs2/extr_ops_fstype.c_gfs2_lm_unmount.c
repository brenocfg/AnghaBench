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
struct lm_lockops {int /*<<< orphan*/  (* lm_unmount ) (struct gfs2_sbd*) ;} ;
struct TYPE_2__ {struct lm_lockops* ls_ops; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_flags; TYPE_1__ sd_lockstruct; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDF_SHUTDOWN ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  stub1 (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void gfs2_lm_unmount(struct gfs2_sbd *sdp)
{
	const struct lm_lockops *lm = sdp->sd_lockstruct.ls_ops;
	if (likely(!test_bit(SDF_SHUTDOWN, &sdp->sd_flags)) &&
	    lm->lm_unmount)
		lm->lm_unmount(sdp);
}