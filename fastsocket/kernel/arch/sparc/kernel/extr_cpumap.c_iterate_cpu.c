#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cpuinfo_tree {TYPE_1__* nodes; } ;
struct TYPE_2__ {int level; int rover; } ;

/* Variables and functions */
 int CPUINFO_LVL_MAX ; 
 int const ROVER_INC_ON_VISIT ; 
#define  SUN4V_CHIP_NIAGARA1 129 
#define  SUN4V_CHIP_NIAGARA2 128 
 int* generic_iterate_method ; 
 int /*<<< orphan*/  increment_rover (struct cpuinfo_tree*,int,unsigned int,int const*) ; 
 int* niagara_iterate_method ; 
 int sun4v_chip_type ; 

__attribute__((used)) static int iterate_cpu(struct cpuinfo_tree *t, unsigned int root_index)
{
	const int *rover_inc_table;
	int level, new_index, index = root_index;

	switch (sun4v_chip_type) {
	case SUN4V_CHIP_NIAGARA1:
	case SUN4V_CHIP_NIAGARA2:
		rover_inc_table = niagara_iterate_method;
		break;
	default:
		rover_inc_table = generic_iterate_method;
	}

	for (level = t->nodes[root_index].level; level < CPUINFO_LVL_MAX;
	     level++) {
		new_index = t->nodes[index].rover;
		if (rover_inc_table[level] & ROVER_INC_ON_VISIT)
			increment_rover(t, index, root_index, rover_inc_table);

		index = new_index;
	}
	return index;
}