#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  q; } ;
struct TYPE_4__ {TYPE_1__ leaf; } ;
struct htb_class {int /*<<< orphan*/  filter_list; int /*<<< orphan*/  ceil; int /*<<< orphan*/  rate; int /*<<< orphan*/  rate_est; int /*<<< orphan*/  bstats; TYPE_2__ un; int /*<<< orphan*/  level; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  gen_kill_estimator (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct htb_class*) ; 
 int /*<<< orphan*/  qdisc_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qdisc_put_rtab (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcf_destroy_chain (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void htb_destroy_class(struct Qdisc *sch, struct htb_class *cl)
{
	if (!cl->level) {
		WARN_ON(!cl->un.leaf.q);
		qdisc_destroy(cl->un.leaf.q);
	}
	gen_kill_estimator(&cl->bstats, &cl->rate_est);
	qdisc_put_rtab(cl->rate);
	qdisc_put_rtab(cl->ceil);

	tcf_destroy_chain(&cl->filter_list);
	kfree(cl);
}