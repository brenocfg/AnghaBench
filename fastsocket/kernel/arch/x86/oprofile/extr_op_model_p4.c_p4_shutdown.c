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
struct op_msrs {TYPE_2__* controls; TYPE_1__* counters; } ;
struct TYPE_4__ {scalar_t__ addr; } ;
struct TYPE_3__ {scalar_t__ addr; } ;

/* Variables and functions */
 int num_controls ; 
 int num_counters ; 
 int /*<<< orphan*/  release_evntsel_nmi (scalar_t__) ; 
 int /*<<< orphan*/  release_perfctr_nmi (scalar_t__) ; 

__attribute__((used)) static void p4_shutdown(struct op_msrs const * const msrs)
{
	int i;

	for (i = 0; i < num_counters; ++i) {
		if (msrs->counters[i].addr)
			release_perfctr_nmi(msrs->counters[i].addr);
	}
	/*
	 * some of the control registers are specially reserved in
	 * conjunction with the counter registers (hence the starting offset).
	 * This saves a few bits.
	 */
	for (i = num_counters; i < num_controls; ++i) {
		if (msrs->controls[i].addr)
			release_evntsel_nmi(msrs->controls[i].addr);
	}
}