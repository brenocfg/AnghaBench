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

/* Variables and functions */
 scalar_t__ curr_ticks ; 
 int /*<<< orphan*/  lock ; 
 unsigned long next_event_time ; 
 scalar_t__ prev_event_time ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ ticks_offs ; 
 scalar_t__ tmr_ctr ; 
 scalar_t__ tmr_offs ; 

__attribute__((used)) static void
tmr_reset(void)
{
	unsigned long   flags;

	spin_lock_irqsave(&lock,flags);
	tmr_offs = 0;
	ticks_offs = 0;
	tmr_ctr = 0;
	next_event_time = (unsigned long) -1;
	prev_event_time = 0;
	curr_ticks = 0;
	spin_unlock_irqrestore(&lock,flags);
}