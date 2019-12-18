#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {unsigned long num_counters; int /*<<< orphan*/  (* cpu_setup ) (TYPE_1__*) ;int /*<<< orphan*/  (* reg_setup ) (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_10__ {scalar_t__ enabled; } ;
struct TYPE_9__ {unsigned long enable; } ;

/* Variables and functions */
 TYPE_3__* ctr ; 
 TYPE_7__* model ; 
 int /*<<< orphan*/  op_handle_interrupt ; 
 int /*<<< orphan*/  perf_irq ; 
 TYPE_1__ reg ; 
 int /*<<< orphan*/  save_perf_irq ; 
 int /*<<< orphan*/  smp_call_function (int /*<<< orphan*/  (*) (TYPE_1__*),TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 
 int /*<<< orphan*/  sys ; 

__attribute__((used)) static int
op_axp_setup(void)
{
	unsigned long i, e;

	/* Install our interrupt handler into the existing hook.  */
	save_perf_irq = perf_irq;
	perf_irq = op_handle_interrupt;

	/* Compute the mask of enabled counters.  */
	for (i = e = 0; i < model->num_counters; ++i)
		if (ctr[i].enabled)
			e |= 1 << i;
	reg.enable = e;

	/* Pre-compute the values to stuff in the hardware registers.  */
	model->reg_setup(&reg, ctr, &sys);

	/* Configure the registers on all cpus.  */
	(void)smp_call_function(model->cpu_setup, &reg, 1);
	model->cpu_setup(&reg);
	return 0;
}