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
struct TYPE_2__ {int x86_model; } ;

/* Variables and functions */
 unsigned int P4_EVENT_INSTR_COMPLETED ; 
 TYPE_1__ boot_cpu_data ; 

__attribute__((used)) static bool p4_event_match_cpu_model(unsigned int event_idx)
{
	/* INSTR_COMPLETED event only exist for model 3, 4, 6 (Prescott) */
	if (event_idx == P4_EVENT_INSTR_COMPLETED) {
		if (boot_cpu_data.x86_model != 3 &&
			boot_cpu_data.x86_model != 4 &&
			boot_cpu_data.x86_model != 6)
			return false;
	}

	/*
	 * For info
	 * - IQ_ESCR0, IQ_ESCR1 only for models 1 and 2
	 */

	return true;
}