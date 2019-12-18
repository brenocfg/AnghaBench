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
struct cfq_rb_root {int /*<<< orphan*/  rb; } ;
struct cfq_queue {int dummy; } ;
struct cfq_data {int /*<<< orphan*/  rq_queued; int /*<<< orphan*/  serving_type; int /*<<< orphan*/  serving_prio; int /*<<< orphan*/  serving_group; } ;

/* Variables and functions */
 scalar_t__ RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 struct cfq_queue* cfq_rb_first (struct cfq_rb_root*) ; 
 struct cfq_rb_root* service_tree_for (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cfq_queue *cfq_get_next_queue(struct cfq_data *cfqd)
{
	struct cfq_rb_root *service_tree =
		service_tree_for(cfqd->serving_group, cfqd->serving_prio,
					cfqd->serving_type);

	if (!cfqd->rq_queued)
		return NULL;

	/* There is nothing to dispatch */
	if (!service_tree)
		return NULL;
	if (RB_EMPTY_ROOT(&service_tree->rb))
		return NULL;
	return cfq_rb_first(service_tree);
}