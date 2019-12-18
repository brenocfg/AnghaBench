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
typedef  int /*<<< orphan*/  apm_event_t ;

/* Variables and functions */
 int /*<<< orphan*/  kapmd_queue ; 
 int /*<<< orphan*/  kapmd_queue_lock ; 
 int /*<<< orphan*/  kapmd_wait ; 
 int /*<<< orphan*/  queue_add_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void apm_queue_event(apm_event_t event)
{
	unsigned long flags;

	spin_lock_irqsave(&kapmd_queue_lock, flags);
	queue_add_event(&kapmd_queue, event);
	spin_unlock_irqrestore(&kapmd_queue_lock, flags);

	wake_up_interruptible(&kapmd_wait);
}