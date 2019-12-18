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
struct qdisc_rate_table {struct qdisc_rate_table* next; scalar_t__ refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct qdisc_rate_table*) ; 
 struct qdisc_rate_table* qdisc_rtab_list ; 

void qdisc_put_rtab(struct qdisc_rate_table *tab)
{
	struct qdisc_rate_table *rtab, **rtabp;

	if (!tab || --tab->refcnt)
		return;

	for (rtabp = &qdisc_rtab_list; (rtab=*rtabp) != NULL; rtabp = &rtab->next) {
		if (rtab == tab) {
			*rtabp = rtab->next;
			kfree(rtab);
			return;
		}
	}
}