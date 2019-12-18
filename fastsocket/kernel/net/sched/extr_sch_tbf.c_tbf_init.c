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
struct tbf_sched_data {int /*<<< orphan*/ * qdisc; int /*<<< orphan*/  watchdog; int /*<<< orphan*/  t_c; } ;
struct nlattr {int dummy; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  noop_qdisc ; 
 int /*<<< orphan*/  psched_get_time () ; 
 struct tbf_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_watchdog_init (int /*<<< orphan*/ *,struct Qdisc*) ; 
 int tbf_change (struct Qdisc*,struct nlattr*) ; 

__attribute__((used)) static int tbf_init(struct Qdisc* sch, struct nlattr *opt)
{
	struct tbf_sched_data *q = qdisc_priv(sch);

	if (opt == NULL)
		return -EINVAL;

	q->t_c = psched_get_time();
	qdisc_watchdog_init(&q->watchdog, sch);
	q->qdisc = &noop_qdisc;

	return tbf_change(sch, opt);
}