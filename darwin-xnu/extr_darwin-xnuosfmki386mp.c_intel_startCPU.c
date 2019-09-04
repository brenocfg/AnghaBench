#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  cpu_running; } ;
struct TYPE_4__ {int target_cpu; int target_lapic; int /*<<< orphan*/  starter_cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,int) ; 
 int /*<<< orphan*/  DBGLOG_CPU_INIT (int) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IdlePTD ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* cpu_datap (int) ; 
 int /*<<< orphan*/  cpu_desc_init (TYPE_2__*) ; 
 int /*<<< orphan*/  cpu_number () ; 
 int* cpu_to_lapic ; 
 int /*<<< orphan*/  delay (int) ; 
 int get_cpu_number () ; 
 int /*<<< orphan*/  halt_cpu () ; 
 int /*<<< orphan*/  kprintf (char*,int,...) ; 
 int /*<<< orphan*/  lck_mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_cpu_boot_lock ; 
 int /*<<< orphan*/  mp_rendezvous_no_intrs (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  start_cpu ; 
 TYPE_1__ start_info ; 
 int tsc_entry_barrier ; 
 int tsc_exit_barrier ; 

kern_return_t
intel_startCPU(
	int	slot_num)
{
	int		lapic = cpu_to_lapic[slot_num];
	boolean_t	istate;

	assert(lapic != -1);

	DBGLOG_CPU_INIT(slot_num);

	DBG("intel_startCPU(%d) lapic_id=%d\n", slot_num, lapic);
	DBG("IdlePTD(%p): 0x%x\n", &IdlePTD, (int) (uintptr_t)IdlePTD);

	/*
	 * Initialize (or re-initialize) the descriptor tables for this cpu.
	 * Propagate processor mode to slave.
	 */
	cpu_desc_init(cpu_datap(slot_num));

	/* Serialize use of the slave boot stack, etc. */
	lck_mtx_lock(&mp_cpu_boot_lock);

	istate = ml_set_interrupts_enabled(FALSE);
	if (slot_num == get_cpu_number()) {
		ml_set_interrupts_enabled(istate);
		lck_mtx_unlock(&mp_cpu_boot_lock);
		return KERN_SUCCESS;
	}

	start_info.starter_cpu  = cpu_number();
	start_info.target_cpu   = slot_num;
	start_info.target_lapic = lapic;
	tsc_entry_barrier = 2;
	tsc_exit_barrier = 2;

	/*
	 * Perform the processor startup sequence with all running
	 * processors rendezvous'ed. This is required during periods when
	 * the cache-disable bit is set for MTRR/PAT initialization.
	 */
	mp_rendezvous_no_intrs(start_cpu, (void *) &start_info);

	start_info.target_cpu = 0;

	ml_set_interrupts_enabled(istate);
	lck_mtx_unlock(&mp_cpu_boot_lock);

	if (!cpu_datap(slot_num)->cpu_running) {
		kprintf("Failed to start CPU %02d\n", slot_num);
		printf("Failed to start CPU %02d, rebooting...\n", slot_num);
		delay(1000000);
		halt_cpu();
		return KERN_SUCCESS;
	} else {
		kprintf("Started cpu %d (lapic id %08x)\n", slot_num, lapic);
		return KERN_SUCCESS;
	}
}