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
struct qdisc_watchdog {TYPE_1__* qdisc; int /*<<< orphan*/  timer; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCQ_F_THROTTLED ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 

void qdisc_watchdog_cancel(struct qdisc_watchdog *wd)
{
	hrtimer_cancel(&wd->timer);
	wd->qdisc->flags &= ~TCQ_F_THROTTLED;
}