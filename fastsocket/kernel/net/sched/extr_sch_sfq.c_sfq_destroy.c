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
struct sfq_sched_data {int /*<<< orphan*/  perturb_timer; scalar_t__ perturb_period; int /*<<< orphan*/  filter_list; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct sfq_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  tcf_destroy_chain (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sfq_destroy(struct Qdisc *sch)
{
	struct sfq_sched_data *q = qdisc_priv(sch);

	tcf_destroy_chain(&q->filter_list);
	q->perturb_period = 0;
	del_timer_sync(&q->perturb_timer);
}