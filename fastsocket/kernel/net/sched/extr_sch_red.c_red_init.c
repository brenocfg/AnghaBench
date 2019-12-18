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
struct red_sched_data {int /*<<< orphan*/ * qdisc; } ;
struct nlattr {int dummy; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  noop_qdisc ; 
 struct red_sched_data* qdisc_priv (struct Qdisc*) ; 
 int red_change (struct Qdisc*,struct nlattr*) ; 

__attribute__((used)) static int red_init(struct Qdisc* sch, struct nlattr *opt)
{
	struct red_sched_data *q = qdisc_priv(sch);

	q->qdisc = &noop_qdisc;
	return red_change(sch, opt);
}