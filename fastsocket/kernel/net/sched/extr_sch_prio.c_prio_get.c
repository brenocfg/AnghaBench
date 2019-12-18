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
typedef  int /*<<< orphan*/  u32 ;
struct prio_sched_data {unsigned long bands; } ;
struct Qdisc {int dummy; } ;

/* Variables and functions */
 unsigned long TC_H_MIN (int /*<<< orphan*/ ) ; 
 struct prio_sched_data* qdisc_priv (struct Qdisc*) ; 

__attribute__((used)) static unsigned long prio_get(struct Qdisc *sch, u32 classid)
{
	struct prio_sched_data *q = qdisc_priv(sch);
	unsigned long band = TC_H_MIN(classid);

	if (band - 1 >= q->bands)
		return 0;
	return band;
}