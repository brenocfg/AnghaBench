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
struct nlattr {int dummy; } ;
struct netem_sched_data {int /*<<< orphan*/  qdisc; int /*<<< orphan*/  watchdog; } ;
struct Qdisc {int /*<<< orphan*/  handle; int /*<<< orphan*/  dev_queue; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  TC_H_MAKE (int /*<<< orphan*/ ,int) ; 
 int netem_change (struct Qdisc*,struct nlattr*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  qdisc_create_dflt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_dev (struct Qdisc*) ; 
 struct netem_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  qdisc_watchdog_init (int /*<<< orphan*/ *,struct Qdisc*) ; 
 int /*<<< orphan*/  tfifo_qdisc_ops ; 

__attribute__((used)) static int netem_init(struct Qdisc *sch, struct nlattr *opt)
{
	struct netem_sched_data *q = qdisc_priv(sch);
	int ret;

	if (!opt)
		return -EINVAL;

	qdisc_watchdog_init(&q->watchdog, sch);

	q->qdisc = qdisc_create_dflt(qdisc_dev(sch), sch->dev_queue,
				     &tfifo_qdisc_ops,
				     TC_H_MAKE(sch->handle, 1));
	if (!q->qdisc) {
		pr_debug("netem: qdisc create failed\n");
		return -ENOMEM;
	}

	ret = netem_change(sch, opt);
	if (ret) {
		pr_debug("netem: change failed\n");
		qdisc_destroy(q->qdisc);
	}
	return ret;
}