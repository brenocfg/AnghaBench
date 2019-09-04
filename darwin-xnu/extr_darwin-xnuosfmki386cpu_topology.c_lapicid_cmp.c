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
struct TYPE_2__ {scalar_t__ cpu_phys_number; } ;
typedef  TYPE_1__ cpu_data_t ;

/* Variables and functions */
 int /*<<< orphan*/  TOPO_DBG (char*,void const*,void const*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
lapicid_cmp(const void *x, const void *y)
{
	cpu_data_t	*cpu_x = *((cpu_data_t **)(uintptr_t)x);
	cpu_data_t	*cpu_y = *((cpu_data_t **)(uintptr_t)y);

	TOPO_DBG("lapicid_cmp(%p,%p) (%d,%d)\n",
		x, y, cpu_x->cpu_phys_number, cpu_y->cpu_phys_number);
	if (cpu_x->cpu_phys_number < cpu_y->cpu_phys_number)
		return -1;
	if (cpu_x->cpu_phys_number == cpu_y->cpu_phys_number)
		return 0;
	return 1;
}