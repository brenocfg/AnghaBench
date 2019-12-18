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
struct cpu_stopper {int /*<<< orphan*/  lock; int /*<<< orphan*/  thread; int /*<<< orphan*/  works; scalar_t__ enabled; } ;
struct cpu_stop_work {int /*<<< orphan*/  done; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_stop_signal_done (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpu_stop_queue_work(struct cpu_stopper *stopper,
				struct cpu_stop_work *work)
{
	unsigned long flags;

	spin_lock_irqsave(&stopper->lock, flags);

	if (stopper->enabled) {
		list_add_tail(&work->list, &stopper->works);
		wake_up_process(stopper->thread);
	} else
		cpu_stop_signal_done(work->done, false);

	spin_unlock_irqrestore(&stopper->lock, flags);
}