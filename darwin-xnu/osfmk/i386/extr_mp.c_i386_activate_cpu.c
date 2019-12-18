#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* cpu_running; } ;
typedef  TYPE_1__ cpu_data_t ;

/* Variables and functions */
 void* TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* current_cpu_datap () ; 
 int /*<<< orphan*/  flush_tlb_raw () ; 
 int /*<<< orphan*/  ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  mp_safe_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_initialized ; 
 int /*<<< orphan*/  started_cpu () ; 
 int /*<<< orphan*/  x86_topo_lock ; 

void
i386_activate_cpu(void)
{
	cpu_data_t	*cdp = current_cpu_datap();

	assert(!ml_get_interrupts_enabled());

	if (!smp_initialized) {
		cdp->cpu_running = TRUE;
		return;
	}

	mp_safe_spin_lock(&x86_topo_lock);
	cdp->cpu_running = TRUE;
	started_cpu();
	simple_unlock(&x86_topo_lock);
	flush_tlb_raw();
}