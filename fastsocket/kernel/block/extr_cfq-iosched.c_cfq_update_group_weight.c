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
struct cfq_group {int needs_update; int /*<<< orphan*/  new_weight; int /*<<< orphan*/  weight; int /*<<< orphan*/  rb_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  RB_EMPTY_NODE (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cfq_update_group_weight(struct cfq_group *cfqg)
{
	BUG_ON(!RB_EMPTY_NODE(&cfqg->rb_node));
	if (cfqg->needs_update) {
		cfqg->weight = cfqg->new_weight;
		cfqg->needs_update = false;
	}
}