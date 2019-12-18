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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ TLBSTATE_LAZY ; 
 int /*<<< orphan*/  __flush_tlb_all () ; 
 TYPE_1__ cpu_tlbstate ; 
 int /*<<< orphan*/  leave_mm (unsigned long) ; 
 scalar_t__ percpu_read (int /*<<< orphan*/ ) ; 
 unsigned long smp_processor_id () ; 

__attribute__((used)) static void do_flush_tlb_all(void *info)
{
	unsigned long cpu = smp_processor_id();

	__flush_tlb_all();
	if (percpu_read(cpu_tlbstate.state) == TLBSTATE_LAZY)
		leave_mm(cpu);
}