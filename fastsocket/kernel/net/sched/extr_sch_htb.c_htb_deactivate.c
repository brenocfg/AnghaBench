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
struct htb_sched {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  drop_list; } ;
struct TYPE_4__ {TYPE_1__ leaf; } ;
struct htb_class {TYPE_2__ un; scalar_t__ prio_activity; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  htb_deactivate_prios (struct htb_sched*,struct htb_class*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void htb_deactivate(struct htb_sched *q, struct htb_class *cl)
{
	WARN_ON(!cl->prio_activity);

	htb_deactivate_prios(q, cl);
	cl->prio_activity = 0;
	list_del_init(&cl->un.leaf.drop_list);
}