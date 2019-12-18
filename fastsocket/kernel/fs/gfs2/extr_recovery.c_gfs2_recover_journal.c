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
struct gfs2_jdesc {int /*<<< orphan*/  jd_flags; int /*<<< orphan*/  jd_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  JDF_RECOVERY ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  gfs2_recovery_wait ; 
 int slow_work_enqueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_on_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int gfs2_recover_journal(struct gfs2_jdesc *jd)
{
	int rv;
	rv = slow_work_enqueue(&jd->jd_work);
	if (rv)
		return rv;
	wait_on_bit(&jd->jd_flags, JDF_RECOVERY, gfs2_recovery_wait, TASK_UNINTERRUPTIBLE);
	return 0;
}