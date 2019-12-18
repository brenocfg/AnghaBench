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
struct cfq_group {int /*<<< orphan*/  rb_node; scalar_t__ weight; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cfq_rb_erase (int /*<<< orphan*/ *,struct cfq_rb_root*) ; 

__attribute__((used)) static void
cfq_group_service_tree_del(struct cfq_rb_root *st, struct cfq_group *cfqg)
{
	st->total_weight -= cfqg->weight;
	if (!RB_EMPTY_NODE(&cfqg->rb_node))
		cfq_rb_erase(&cfqg->rb_node, st);
}