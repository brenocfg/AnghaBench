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
struct dsmark_qdisc_data {int /*<<< orphan*/  mask; int /*<<< orphan*/  q; int /*<<< orphan*/  filter_list; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct Qdisc*,struct dsmark_qdisc_data*) ; 
 int /*<<< orphan*/  qdisc_destroy (int /*<<< orphan*/ ) ; 
 struct dsmark_qdisc_data* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  tcf_destroy_chain (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dsmark_destroy(struct Qdisc *sch)
{
	struct dsmark_qdisc_data *p = qdisc_priv(sch);

	pr_debug("dsmark_destroy(sch %p,[qdisc %p])\n", sch, p);

	tcf_destroy_chain(&p->filter_list);
	qdisc_destroy(p->q);
	kfree(p->mask);
}