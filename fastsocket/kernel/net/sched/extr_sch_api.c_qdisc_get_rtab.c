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
struct tc_ratespec {scalar_t__ rate; scalar_t__ cell_log; } ;
struct qdisc_rate_table {int refcnt; struct qdisc_rate_table* next; int /*<<< orphan*/  data; struct tc_ratespec rate; } ;
struct nlattr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ TC_RTAB_SIZE ; 
 struct qdisc_rate_table* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (struct tc_ratespec*,struct tc_ratespec*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_data (struct nlattr*) ; 
 scalar_t__ nla_len (struct nlattr*) ; 
 struct qdisc_rate_table* qdisc_rtab_list ; 

struct qdisc_rate_table *qdisc_get_rtab(struct tc_ratespec *r, struct nlattr *tab)
{
	struct qdisc_rate_table *rtab;

	for (rtab = qdisc_rtab_list; rtab; rtab = rtab->next) {
		if (memcmp(&rtab->rate, r, sizeof(struct tc_ratespec)) == 0) {
			rtab->refcnt++;
			return rtab;
		}
	}

	if (tab == NULL || r->rate == 0 || r->cell_log == 0 ||
	    nla_len(tab) != TC_RTAB_SIZE)
		return NULL;

	rtab = kmalloc(sizeof(*rtab), GFP_KERNEL);
	if (rtab) {
		rtab->rate = *r;
		rtab->refcnt = 1;
		memcpy(rtab->data, nla_data(tab), 1024);
		rtab->next = qdisc_rtab_list;
		qdisc_rtab_list = rtab;
	}
	return rtab;
}