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
 int __cpu_find_by (int /*<<< orphan*/ ,void*,int*,int*) ; 
 int /*<<< orphan*/  cpu_instance_compare ; 

int cpu_find_by_instance(int instance, int *prom_node, int *mid)
{
	return __cpu_find_by(cpu_instance_compare, (void *)instance,
			     prom_node, mid);
}