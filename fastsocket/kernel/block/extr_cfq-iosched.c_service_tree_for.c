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
struct cfq_rb_root {int dummy; } ;
struct cfq_group {struct cfq_rb_root** service_trees; struct cfq_rb_root service_tree_idle; } ;
typedef  enum wl_type_t { ____Placeholder_wl_type_t } wl_type_t ;
typedef  enum wl_prio_t { ____Placeholder_wl_prio_t } wl_prio_t ;

/* Variables and functions */
 int IDLE_WORKLOAD ; 

__attribute__((used)) static struct cfq_rb_root *service_tree_for(struct cfq_group *cfqg,
					    enum wl_prio_t prio,
					    enum wl_type_t type)
{
	if (!cfqg)
		return NULL;

	if (prio == IDLE_WORKLOAD)
		return &cfqg->service_tree_idle;

	return &cfqg->service_trees[prio][type];
}