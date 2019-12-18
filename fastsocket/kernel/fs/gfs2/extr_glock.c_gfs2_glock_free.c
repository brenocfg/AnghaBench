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
struct gfs2_sbd {int /*<<< orphan*/  sd_glock_wait; int /*<<< orphan*/  sd_glock_disposal; } ;
struct gfs2_glock {int /*<<< orphan*/  gl_rcu; struct gfs2_sbd* gl_sbd; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_glock_dealloc ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void gfs2_glock_free(struct gfs2_glock *gl)
{
	struct gfs2_sbd *sdp = gl->gl_sbd;

	call_rcu(&gl->gl_rcu, gfs2_glock_dealloc);
	if (atomic_dec_and_test(&sdp->sd_glock_disposal))
		wake_up(&sdp->sd_glock_wait);
}