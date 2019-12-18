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
struct tcf_common {struct tcf_common* tcfc_next; } ;
struct tcf_police {scalar_t__ tcfp_P_tab; scalar_t__ tcfp_R_tab; int /*<<< orphan*/  tcf_rate_est; int /*<<< orphan*/  tcf_bstats; struct tcf_common* tcf_next; struct tcf_common common; int /*<<< orphan*/  tcf_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  POL_TAB_MASK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  gen_kill_estimator (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct tcf_police*) ; 
 int /*<<< orphan*/  police_lock ; 
 int /*<<< orphan*/  qdisc_put_rtab (scalar_t__) ; 
 unsigned int tcf_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tcf_common** tcf_police_ht ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void tcf_police_destroy(struct tcf_police *p)
{
	unsigned int h = tcf_hash(p->tcf_index, POL_TAB_MASK);
	struct tcf_common **p1p;

	for (p1p = &tcf_police_ht[h]; *p1p; p1p = &(*p1p)->tcfc_next) {
		if (*p1p == &p->common) {
			write_lock_bh(&police_lock);
			*p1p = p->tcf_next;
			write_unlock_bh(&police_lock);
			gen_kill_estimator(&p->tcf_bstats,
					   &p->tcf_rate_est);
			if (p->tcfp_R_tab)
				qdisc_put_rtab(p->tcfp_R_tab);
			if (p->tcfp_P_tab)
				qdisc_put_rtab(p->tcfp_P_tab);
			kfree(p);
			return;
		}
	}
	WARN_ON(1);
}