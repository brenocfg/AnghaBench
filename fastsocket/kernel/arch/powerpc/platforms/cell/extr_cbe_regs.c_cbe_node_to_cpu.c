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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  cpumask_t ;

/* Variables and functions */
 int /*<<< orphan*/ * cbe_local_mask ; 
 int /*<<< orphan*/  find_first_bit (unsigned long*,int) ; 

u32 cbe_node_to_cpu(int node)
{
	return find_first_bit( (unsigned long *) &cbe_local_mask[node], sizeof(cpumask_t));
}