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
struct multiq_sched_data {int bands; int /*<<< orphan*/ * queues; int /*<<< orphan*/  filter_list; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qdisc_destroy (int /*<<< orphan*/ ) ; 
 struct multiq_sched_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  tcf_destroy_chain (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
multiq_destroy(struct Qdisc *sch)
{
	int band;
	struct multiq_sched_data *q = qdisc_priv(sch);

	tcf_destroy_chain(&q->filter_list);
	for (band = 0; band < q->bands; band++)
		qdisc_destroy(q->queues[band]);

	kfree(q->queues);
}