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
struct Qdisc {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  __QDISC_STATE_RUNNING ; 
 int /*<<< orphan*/  __netif_schedule (struct Qdisc*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 scalar_t__ need_resched () ; 
 scalar_t__ qdisc_restart (struct Qdisc*) ; 

void __qdisc_run(struct Qdisc *q)
{
	unsigned long start_time = jiffies;

	while (qdisc_restart(q)) {
		/*
		 * Postpone processing if
		 * 1. another process needs the CPU;
		 * 2. we've been doing it for too long.
		 */
		if (need_resched() || jiffies != start_time) {
			__netif_schedule(q);
			break;
		}
	}

	clear_bit(__QDISC_STATE_RUNNING, &q->state);
}