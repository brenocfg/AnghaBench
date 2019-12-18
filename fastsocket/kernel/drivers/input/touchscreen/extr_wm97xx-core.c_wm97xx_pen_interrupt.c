#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wm97xx {int /*<<< orphan*/  pen_event_work; int /*<<< orphan*/  ts_workq; TYPE_1__* mach_ops; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* irq_enable ) (struct wm97xx*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct wm97xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  work_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t wm97xx_pen_interrupt(int irq, void *dev_id)
{
	struct wm97xx *wm = dev_id;

	if (!work_pending(&wm->pen_event_work)) {
		wm->mach_ops->irq_enable(wm, 0);
		queue_work(wm->ts_workq, &wm->pen_event_work);
	}

	return IRQ_HANDLED;
}