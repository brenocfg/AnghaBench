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
struct mpu_config {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ curr_clocks ; 
 scalar_t__ curr_ticks ; 
 unsigned long next_event_time ; 
 scalar_t__ prev_event_time ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void tmr_reset(struct mpu_config *devc)
{
	unsigned long flags;

	spin_lock_irqsave(&devc->lock,flags);
	next_event_time = (unsigned long) -1;
	prev_event_time = 0;
	curr_ticks = curr_clocks = 0;
	spin_unlock_irqrestore(&devc->lock,flags);
}