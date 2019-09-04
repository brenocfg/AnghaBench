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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */
 scalar_t__* cpu_phys_ids ; 
 int ml_get_max_cpu_number () ; 

int
ml_get_cpu_number(uint32_t phys_id)
{
	for (int log_id = 0; log_id <= ml_get_max_cpu_number(); ++log_id) {
		if (cpu_phys_ids[log_id] == phys_id)
			return log_id;
	}
	return -1;
}