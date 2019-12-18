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
struct work_struct {int dummy; } ;

/* Variables and functions */
 unsigned int WORK_BUSY_PENDING ; 
 unsigned int WORK_BUSY_RUNNING ; 
 scalar_t__ find_worker_executing_work (int /*<<< orphan*/ ,struct work_struct*) ; 
 int /*<<< orphan*/  gcwq ; 
 scalar_t__ work_pending (struct work_struct*) ; 

unsigned int work_busy(struct work_struct *work)
{
	unsigned int ret = 0;

	if (work_pending(work))
		ret |= WORK_BUSY_PENDING;
#if 0 /* Not in RHEL */
	if (find_worker_executing_work(gcwq, work))
		ret |= WORK_BUSY_RUNNING;
#endif
	return ret;
}