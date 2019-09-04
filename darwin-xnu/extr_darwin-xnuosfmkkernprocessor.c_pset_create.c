#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pset_node_t ;
typedef  TYPE_2__* processor_set_t ;
struct TYPE_11__ {struct TYPE_11__* pset_list; } ;
struct TYPE_10__ {TYPE_2__* psets; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 TYPE_2__* PROCESSOR_SET_NULL ; 
 scalar_t__ SCHED (int /*<<< orphan*/ ) ; 
 TYPE_2__* kalloc (int) ; 
 int /*<<< orphan*/  master_processor ; 
 int /*<<< orphan*/  multiple_psets_enabled ; 
 TYPE_2__* processor_pset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pset_init (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  pset_node_lock ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 

processor_set_t
pset_create(
	pset_node_t			node)
{
	/* some schedulers do not support multiple psets */
	if (SCHED(multiple_psets_enabled) == FALSE)
		return processor_pset(master_processor);

	processor_set_t		*prev, pset = kalloc(sizeof (*pset));

	if (pset != PROCESSOR_SET_NULL) {
		pset_init(pset, node);

		simple_lock(&pset_node_lock);

		prev = &node->psets;
		while (*prev != PROCESSOR_SET_NULL)
			prev = &(*prev)->pset_list;

		*prev = pset;

		simple_unlock(&pset_node_lock);
	}

	return (pset);
}