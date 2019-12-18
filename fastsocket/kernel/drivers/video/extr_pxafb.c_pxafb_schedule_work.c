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
typedef  scalar_t__ u_int ;
struct pxafb_info {scalar_t__ task_state; int /*<<< orphan*/  task; } ;

/* Variables and functions */
 scalar_t__ C_DISABLE ; 
 scalar_t__ C_ENABLE ; 
 scalar_t__ C_REENABLE ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void pxafb_schedule_work(struct pxafb_info *fbi, u_int state)
{
	unsigned long flags;

	local_irq_save(flags);
	/*
	 * We need to handle two requests being made at the same time.
	 * There are two important cases:
	 *  1. When we are changing VT (C_REENABLE) while unblanking
	 *     (C_ENABLE) We must perform the unblanking, which will
	 *     do our REENABLE for us.
	 *  2. When we are blanking, but immediately unblank before
	 *     we have blanked.  We do the "REENABLE" thing here as
	 *     well, just to be sure.
	 */
	if (fbi->task_state == C_ENABLE && state == C_REENABLE)
		state = (u_int) -1;
	if (fbi->task_state == C_DISABLE && state == C_ENABLE)
		state = C_REENABLE;

	if (state != (u_int)-1) {
		fbi->task_state = state;
		schedule_work(&fbi->task);
	}
	local_irq_restore(flags);
}