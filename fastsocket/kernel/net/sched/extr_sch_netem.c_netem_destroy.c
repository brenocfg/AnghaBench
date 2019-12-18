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
struct netem_sched_data {int /*<<< orphan*/  delay_dist; int /*<<< orphan*/  qdisc; int /*<<< orphan*/  watchdog; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_destroy (int /*<<< orphan*/ ) ; 
 struct netem_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_watchdog_cancel (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void netem_destroy(struct Qdisc *sch)
{
	struct netem_sched_data *q = qdisc_priv(sch);

	qdisc_watchdog_cancel(&q->watchdog);
	qdisc_destroy(q->qdisc);
	kfree(q->delay_dist);
}