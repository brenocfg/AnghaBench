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
struct op_msrs {struct op_msr* controls; struct op_msr* counters; } ;
struct op_msr {int /*<<< orphan*/  saved; scalar_t__ addr; } ;
struct TYPE_2__ {unsigned int num_controls; unsigned int num_counters; } ;

/* Variables and functions */
 TYPE_1__* model ; 
 int /*<<< orphan*/  wrmsrl (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nmi_cpu_restore_registers(struct op_msrs *msrs)
{
	struct op_msr *counters = msrs->counters;
	struct op_msr *controls = msrs->controls;
	unsigned int i;

	for (i = 0; i < model->num_controls; ++i) {
		if (controls[i].addr)
			wrmsrl(controls[i].addr, controls[i].saved);
	}

	for (i = 0; i < model->num_counters; ++i) {
		if (counters[i].addr)
			wrmsrl(counters[i].addr, counters[i].saved);
	}
}