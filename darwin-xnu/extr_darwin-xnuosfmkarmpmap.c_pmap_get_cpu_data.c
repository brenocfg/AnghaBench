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
typedef  int /*<<< orphan*/  pmap_cpu_data_t ;
struct TYPE_2__ {int /*<<< orphan*/  cpu_pmap_cpu_data; } ;

/* Variables and functions */
 TYPE_1__* getCpuDatap () ; 

pmap_cpu_data_t *
pmap_get_cpu_data(void)
{
	pmap_cpu_data_t * pmap_cpu_data = NULL;

	pmap_cpu_data = &getCpuDatap()->cpu_pmap_cpu_data;

	return pmap_cpu_data;
}