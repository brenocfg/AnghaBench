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

/* Variables and functions */
 scalar_t__ MAX_NUMNODES ; 
 int NID_INVAL ; 
 int /*<<< orphan*/  __acpi_map_pxm_to_node (int,int) ; 
 int first_unset_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  node_set (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nodes_found_map ; 
 scalar_t__ nodes_weight (int /*<<< orphan*/ ) ; 
 int* pxm_to_node_map ; 

int acpi_map_pxm_to_node(int pxm)
{
	int node = pxm_to_node_map[pxm];

	if (node < 0){
		if (nodes_weight(nodes_found_map) >= MAX_NUMNODES)
			return NID_INVAL;
		node = first_unset_node(nodes_found_map);
		__acpi_map_pxm_to_node(pxm, node);
		node_set(node, nodes_found_map);
	}

	return node;
}