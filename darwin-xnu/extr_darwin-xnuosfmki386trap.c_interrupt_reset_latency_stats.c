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
typedef  size_t uint32_t ;
struct TYPE_2__ {scalar_t__ cpu_max_observed_int_latency_vector; scalar_t__ cpu_max_observed_int_latency; } ;

/* Variables and functions */
 TYPE_1__** cpu_data_ptr ; 
 size_t real_ncpus ; 

void interrupt_reset_latency_stats(void) {
	uint32_t i;
	for (i = 0; i < real_ncpus; i++) {
		cpu_data_ptr[i]->cpu_max_observed_int_latency =
		    cpu_data_ptr[i]->cpu_max_observed_int_latency_vector = 0;
	}
}