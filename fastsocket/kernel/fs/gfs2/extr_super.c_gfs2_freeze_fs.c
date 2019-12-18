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
struct gfs2_sbd {int /*<<< orphan*/  sd_freeze_lock; int /*<<< orphan*/  sd_freeze_count; int /*<<< orphan*/  sd_freeze_gh; } ;

/* Variables and functions */
 int gfs2_lock_fs_check_clean (struct gfs2_sbd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int gfs2_freeze_fs(struct gfs2_sbd *sdp)
{
	int error = 0;

	mutex_lock(&sdp->sd_freeze_lock);

	if (!sdp->sd_freeze_count++) {
		error = gfs2_lock_fs_check_clean(sdp, &sdp->sd_freeze_gh);
		if (error)
			sdp->sd_freeze_count--;
	}

	mutex_unlock(&sdp->sd_freeze_lock);

	return error;
}