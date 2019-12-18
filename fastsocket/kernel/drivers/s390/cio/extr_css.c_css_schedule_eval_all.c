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
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cio_work_q ; 
 int /*<<< orphan*/  css_eval_scheduled ; 
 int /*<<< orphan*/  idset_fill (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slow_path_work ; 
 int /*<<< orphan*/  slow_subchannel_lock ; 
 int /*<<< orphan*/  slow_subchannel_set ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void css_schedule_eval_all(void)
{
	unsigned long flags;

	spin_lock_irqsave(&slow_subchannel_lock, flags);
	idset_fill(slow_subchannel_set);
	atomic_set(&css_eval_scheduled, 1);
	queue_work(cio_work_q, &slow_path_work);
	spin_unlock_irqrestore(&slow_subchannel_lock, flags);
}