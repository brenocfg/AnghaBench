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
struct TYPE_2__ {unsigned int num_counters; } ;

/* Variables and functions */
 TYPE_1__ op_model_mipsxx_ops ; 
 int /*<<< orphan*/  w_c0_perfctrl0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_c0_perfctrl1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_c0_perfctrl2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  w_c0_perfctrl3 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mipsxx_cpu_stop(void *args)
{
	unsigned int counters = op_model_mipsxx_ops.num_counters;

	switch (counters) {
	case 4:
		w_c0_perfctrl3(0);
	case 3:
		w_c0_perfctrl2(0);
	case 2:
		w_c0_perfctrl1(0);
	case 1:
		w_c0_perfctrl0(0);
	}
}