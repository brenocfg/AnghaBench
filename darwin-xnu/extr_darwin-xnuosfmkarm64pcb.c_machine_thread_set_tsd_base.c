#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  TYPE_2__* thread_t ;
typedef  int mach_vm_offset_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_6__ {int cthread_self; } ;
struct TYPE_7__ {scalar_t__ task; TYPE_1__ machine; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int MACHDEP_CPUNUM_MASK ; 
 int UINT32_MAX ; 
 TYPE_2__* current_thread () ; 
 int get_tpidrro () ; 
 scalar_t__ kernel_task ; 
 int /*<<< orphan*/  mp_disable_preemption () ; 
 int /*<<< orphan*/  mp_enable_preemption () ; 
 int /*<<< orphan*/  set_tpidrro (int) ; 
 scalar_t__ thread_is_64bit_addr (TYPE_2__*) ; 
 int vm_map_max (int /*<<< orphan*/ ) ; 

kern_return_t
machine_thread_set_tsd_base(
	thread_t			thread,
	mach_vm_offset_t	tsd_base)
{

	if (thread->task == kernel_task) {
		return KERN_INVALID_ARGUMENT;
	}

	if (tsd_base & MACHDEP_CPUNUM_MASK) {
		return KERN_INVALID_ARGUMENT;
	}

	if (thread_is_64bit_addr(thread)) {
		if (tsd_base > vm_map_max(thread->map))
			tsd_base = 0ULL;
	} else {
		if (tsd_base > UINT32_MAX)
			tsd_base = 0ULL;
	}

	thread->machine.cthread_self = tsd_base;

	/* For current thread, make the TSD base active immediately */
	if (thread == current_thread()) {
		uint64_t cpunum, tpidrro_el0;

		mp_disable_preemption();
		tpidrro_el0 = get_tpidrro();
		cpunum = tpidrro_el0 & (MACHDEP_CPUNUM_MASK);
		set_tpidrro(tsd_base | cpunum);
		mp_enable_preemption();

	}

	return KERN_SUCCESS;
}