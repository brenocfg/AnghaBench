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
typedef  int /*<<< orphan*/  u8 ;
struct tc_gred_qopt {int /*<<< orphan*/  Scell_log; int /*<<< orphan*/  Plog; int /*<<< orphan*/  Wlog; int /*<<< orphan*/  qth_max; int /*<<< orphan*/  qth_min; int /*<<< orphan*/  limit; } ;
struct gred_sched_data {int DP; int prio; scalar_t__ backlog; int /*<<< orphan*/  parms; int /*<<< orphan*/  limit; } ;
struct gred_sched {struct gred_sched_data** tab; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct gred_sched_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct gred_sched* qdisc_priv (struct Qdisc*) ; 
 int /*<<< orphan*/  red_end_of_idle_period (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  red_set_parms (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int gred_change_vq(struct Qdisc *sch, int dp,
				 struct tc_gred_qopt *ctl, int prio, u8 *stab)
{
	struct gred_sched *table = qdisc_priv(sch);
	struct gred_sched_data *q;

	if (table->tab[dp] == NULL) {
		table->tab[dp] = kzalloc(sizeof(*q), GFP_KERNEL);
		if (table->tab[dp] == NULL)
			return -ENOMEM;
	}

	q = table->tab[dp];
	q->DP = dp;
	q->prio = prio;
	q->limit = ctl->limit;

	if (q->backlog == 0)
		red_end_of_idle_period(&q->parms);

	red_set_parms(&q->parms,
		      ctl->qth_min, ctl->qth_max, ctl->Wlog, ctl->Plog,
		      ctl->Scell_log, stab);

	return 0;
}