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
struct cfq_rb_root {int /*<<< orphan*/  total_weight; } ;
struct cfq_group {scalar_t__ weight; int /*<<< orphan*/  rb_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __cfq_group_service_tree_add (struct cfq_rb_root*,struct cfq_group*) ; 
 int /*<<< orphan*/  cfq_update_group_weight (struct cfq_group*) ; 

__attribute__((used)) static void
cfq_group_service_tree_add(struct cfq_rb_root *st, struct cfq_group *cfqg)
{
	BUG_ON(!RB_EMPTY_NODE(&cfqg->rb_node));

	cfq_update_group_weight(cfqg);
	__cfq_group_service_tree_add(st, cfqg);
	st->total_weight += cfqg->weight;
}