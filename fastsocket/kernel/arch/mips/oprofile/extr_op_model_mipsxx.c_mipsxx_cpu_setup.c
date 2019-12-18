#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int num_counters; } ;
struct TYPE_3__ {int /*<<< orphan*/ * counter; } ;

/* Variables and functions */
 TYPE_2__ op_model_mipsxx_ops ; 
 TYPE_1__ reg ; 
 int /*<<< orphan*/  w_c0_perfcntr0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_c0_perfcntr1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_c0_perfcntr2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_c0_perfcntr3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_c0_perfctrl0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_c0_perfctrl1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_c0_perfctrl2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_c0_perfctrl3 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mipsxx_cpu_setup(void *args)
{
	unsigned int counters = op_model_mipsxx_ops.num_counters;

	switch (counters) {
	case 4:
		w_c0_perfctrl3(0);
		w_c0_perfcntr3(reg.counter[3]);
	case 3:
		w_c0_perfctrl2(0);
		w_c0_perfcntr2(reg.counter[2]);
	case 2:
		w_c0_perfctrl1(0);
		w_c0_perfcntr1(reg.counter[1]);
	case 1:
		w_c0_perfctrl0(0);
		w_c0_perfcntr0(reg.counter[0]);
	}
}