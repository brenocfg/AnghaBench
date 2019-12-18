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
typedef  scalar_t__ boolean_t ;
struct TYPE_2__ {scalar_t__ cpu_tlb_invalid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CR3_MARK_ACTIVE () ; 
 int /*<<< orphan*/  CPU_CR3_MARK_INACTIVE () ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* current_cpu_datap () ; 
 scalar_t__ get_preemption_level () ; 
 int /*<<< orphan*/  mfence () ; 
 scalar_t__ ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  process_pmap_updates () ; 

void x86_filter_TLB_coherency_interrupts(boolean_t dofilter) {
	assert(ml_get_interrupts_enabled() == 0 || get_preemption_level() != 0);

	if (dofilter) {
		CPU_CR3_MARK_INACTIVE();
	} else {
		CPU_CR3_MARK_ACTIVE();
		mfence();
		if (current_cpu_datap()->cpu_tlb_invalid)
			process_pmap_updates();
	}
}