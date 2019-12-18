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
struct tc_netem_corr {int /*<<< orphan*/  dup_corr; int /*<<< orphan*/  loss_corr; int /*<<< orphan*/  delay_corr; } ;
struct nlattr {int dummy; } ;
struct netem_sched_data {int /*<<< orphan*/  dup_cor; int /*<<< orphan*/  loss_cor; int /*<<< orphan*/  delay_cor; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_crandom (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct tc_netem_corr* nla_data (struct nlattr const*) ; 
 struct netem_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static void get_correlation(struct Qdisc *sch, const struct nlattr *attr)
{
	struct netem_sched_data *q = qdisc_priv(sch);
	const struct tc_netem_corr *c = nla_data(attr);

	init_crandom(&q->delay_cor, c->delay_corr);
	init_crandom(&q->loss_cor, c->loss_corr);
	init_crandom(&q->dup_cor, c->dup_corr);
}