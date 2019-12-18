#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  TYPE_1__* pset_node_t ;
typedef  TYPE_2__* processor_set_t ;
struct TYPE_7__ {scalar_t__ pset_cluster_id; struct TYPE_7__* pset_list; } ;
struct TYPE_6__ {TYPE_2__* psets; struct TYPE_6__* node_list; } ;

/* Variables and functions */
 TYPE_1__ pset_node0 ; 
 int /*<<< orphan*/  pset_node_lock ; 
 int /*<<< orphan*/  simple_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 

processor_set_t
pset_find(
	uint32_t cluster_id,
	processor_set_t default_pset)
{
	simple_lock(&pset_node_lock);
	pset_node_t node = &pset_node0;
	processor_set_t pset = NULL;

	do {
		pset = node->psets;
		while (pset != NULL) {
			if (pset->pset_cluster_id == cluster_id)
				break;
			pset = pset->pset_list;
		}
	} while ((node = node->node_list) != NULL);
	simple_unlock(&pset_node_lock);
	if (pset == NULL)
		return default_pset;
	return (pset);
}