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
struct cardstate {int /*<<< orphan*/  lock; int /*<<< orphan*/  event_tasklet; scalar_t__ running; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void gigaset_schedule_event(struct cardstate *cs)
{
	unsigned long flags;
	spin_lock_irqsave(&cs->lock, flags);
	if (cs->running)
		tasklet_schedule(&cs->event_tasklet);
	spin_unlock_irqrestore(&cs->lock, flags);
}