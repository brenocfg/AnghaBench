#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_6__ {scalar_t__ cpu_hibernate; } ;
typedef  TYPE_1__ cpu_data_t ;
typedef  scalar_t__ boolean_t ;
typedef  int /*<<< orphan*/  acpi_sleep_callback ;
typedef  void acpi_hibernate_callback_data_t ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  DBG_HIBERNATE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IOCPURunPlatformActiveActions () ; 
 int IOKDBG_CODE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KDBG (int,...) ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  acpi_hibernate ; 
 scalar_t__ acpi_sleep_abstime ; 
 int /*<<< orphan*/  acpi_sleep_cpu (int /*<<< orphan*/ ,void*) ; 
 scalar_t__ acpi_wake_abstime ; 
 scalar_t__ acpi_wake_postrebase_abstime ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clear_ts () ; 
 unsigned int cpu_number () ; 
 int /*<<< orphan*/  cpu_syscall_init (TYPE_1__*) ; 
 TYPE_1__* current_cpu_datap () ; 
 scalar_t__ disable_serial_output ; 
 int /*<<< orphan*/  hibernate_machine_init () ; 
 int /*<<< orphan*/  hibernate_rebuild_vm_structs () ; 
 int /*<<< orphan*/  hv_suspend () ; 
 int /*<<< orphan*/  init_fpu () ; 
 int /*<<< orphan*/  install_real_mode_bootstrap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kasan_unpoison_curstack (int) ; 
 scalar_t__ kdebug_enable ; 
 int /*<<< orphan*/  kdebug_trace_start (scalar_t__,int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  kprintf (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  lapic_configure () ; 
 scalar_t__ lapic_probe () ; 
 int /*<<< orphan*/  lapic_shutdown () ; 
 scalar_t__ mach_absolute_time () ; 
 int /*<<< orphan*/  mca_cpu_init () ; 
 int /*<<< orphan*/  mt_cpu_down (TYPE_1__*) ; 
 int /*<<< orphan*/  mtrr_update_cpu () ; 
 int /*<<< orphan*/  pal_serial_init () ; 
 int /*<<< orphan*/  panic (char*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  pat_init () ; 
 scalar_t__ pmCPUExitHaltToOff (unsigned int) ; 
 int /*<<< orphan*/  pmCPUMarkRunning (TYPE_1__*) ; 
 int /*<<< orphan*/  pmMarkAllCPUsOff () ; 
 int /*<<< orphan*/  pmTimerRestore () ; 
 int /*<<< orphan*/  pmTimerSave () ; 
 unsigned int real_ncpus ; 
 int /*<<< orphan*/  rtc_decrementer_configure () ; 
 int /*<<< orphan*/  rtc_nanotime_init (scalar_t__) ; 
 int /*<<< orphan*/  rtc_timer_start () ; 
 scalar_t__ save_kdebug_enable ; 
 int /*<<< orphan*/  slave_pstart ; 
 scalar_t__ trace_wrap ; 
 int /*<<< orphan*/  ucode_update_wake () ; 
 int /*<<< orphan*/  vmx_resume (scalar_t__) ; 
 int /*<<< orphan*/  vmx_suspend () ; 
 scalar_t__ wake_nkdbufs ; 
 int /*<<< orphan*/  x86_64_post_sleep (scalar_t__) ; 
 scalar_t__ x86_64_pre_sleep () ; 

void
acpi_sleep_kernel(acpi_sleep_callback func, void *refcon)
{
#if HIBERNATION
	acpi_hibernate_callback_data_t data;
#endif
	boolean_t did_hibernate;
	cpu_data_t *cdp = current_cpu_datap();
	unsigned int	cpu;
	kern_return_t	rc;
	unsigned int	my_cpu;
	uint64_t	start;
	uint64_t	elapsed = 0;
	uint64_t	elapsed_trace_start = 0;

	my_cpu = cpu_number();
	kprintf("acpi_sleep_kernel hib=%d, cpu=%d\n", cdp->cpu_hibernate,
			my_cpu);

	/* Get all CPUs to be in the "off" state */
	for (cpu = 0; cpu < real_ncpus; cpu += 1) {
		if (cpu == my_cpu)
			continue;
		rc = pmCPUExitHaltToOff(cpu);
		if (rc != KERN_SUCCESS)
			panic("Error %d trying to transition CPU %d to OFF",
			      rc, cpu);
	}

	/* shutdown local APIC before passing control to firmware */
	lapic_shutdown();

#if HIBERNATION
	data.func = func;
	data.refcon = refcon;
#endif

#if MONOTONIC
	mt_cpu_down(cdp);
#endif /* MONOTONIC */

	/* Save power management timer state */
	pmTimerSave();

#if HYPERVISOR
	/* Notify hypervisor that we are about to sleep */
	hv_suspend();
#endif

	/*
	 * Enable FPU/SIMD unit for potential hibernate acceleration
	 */
	clear_ts(); 

	KDBG(IOKDBG_CODE(DBG_HIBERNATE, 0) | DBG_FUNC_START);

	save_kdebug_enable = kdebug_enable;
	kdebug_enable = 0;

	acpi_sleep_abstime = mach_absolute_time();

#if CONFIG_SLEEP
	/*
	 * Save master CPU state and sleep platform.
	 * Will not return until platform is woken up,
	 * or if sleep failed.
	 */
	uint64_t old_cr3 = x86_64_pre_sleep();
#if HIBERNATION
	acpi_sleep_cpu(acpi_hibernate, &data);
#else
#if CONFIG_VMX
	vmx_suspend();
#endif
	acpi_sleep_cpu(func, refcon);
#endif

	acpi_wake_abstime = mach_absolute_time();
	/* Rebase TSC->absolute time conversion, using timestamp
	 * recorded before sleep.
	 */
	rtc_nanotime_init(acpi_sleep_abstime);
	acpi_wake_postrebase_abstime = start = mach_absolute_time();
	assert(start >= acpi_sleep_abstime);

	x86_64_post_sleep(old_cr3);

#endif /* CONFIG_SLEEP */

	/* Reset UART if kprintf is enabled.
	 * However kprintf should not be used before rtc_sleep_wakeup()
	 * for compatibility with firewire kprintf.
	 */

	if (FALSE == disable_serial_output)
		pal_serial_init();

#if HIBERNATION
	if (current_cpu_datap()->cpu_hibernate) {
		did_hibernate = TRUE;

	} else
#endif 
	{
		did_hibernate = FALSE;
	}

	/* Re-enable fast syscall */
	cpu_syscall_init(current_cpu_datap());

#if CONFIG_MCA
	/* Re-enable machine check handling */
	mca_cpu_init();
#endif

#if CONFIG_MTRR
	/* restore MTRR settings */
	mtrr_update_cpu();
#endif

	/* update CPU microcode */
	ucode_update_wake();

#if CONFIG_MTRR
	/* set up PAT following boot processor power up */
	pat_init();
#endif

#if CONFIG_VMX
	/* 
	 * Restore VT mode
	 */
	vmx_resume(did_hibernate);
#endif

	/*
	 * Go through all of the CPUs and mark them as requiring
	 * a full restart.
	 */
	pmMarkAllCPUsOff();


	/* re-enable and re-init local apic (prior to starting timers) */
	if (lapic_probe())
		lapic_configure();

#if KASAN
	/*
	 * The sleep implementation uses indirect noreturn calls, so we miss stack
	 * unpoisoning. Do it explicitly.
	 */
	kasan_unpoison_curstack(true);
#endif

#if HIBERNATION
	hibernate_rebuild_vm_structs();
#endif

	elapsed += mach_absolute_time() - start;

	rtc_decrementer_configure();
	kdebug_enable = save_kdebug_enable;

	if (kdebug_enable == 0) {
		if (wake_nkdbufs) {
			start = mach_absolute_time();
			kdebug_trace_start(wake_nkdbufs, NULL, trace_wrap != 0, TRUE);
			elapsed_trace_start += mach_absolute_time() - start;
		}
	}
	start = mach_absolute_time();

	/* Reconfigure FP/SIMD unit */
	init_fpu();
	clear_ts();

	IOCPURunPlatformActiveActions();

#if HIBERNATION
	if (did_hibernate) {
		KDBG(IOKDBG_CODE(DBG_HIBERNATE, 2) | DBG_FUNC_START);
		hibernate_machine_init();
		KDBG(IOKDBG_CODE(DBG_HIBERNATE, 2) | DBG_FUNC_END);

		current_cpu_datap()->cpu_hibernate = 0;
	}
#endif /* HIBERNATION */

	KDBG(IOKDBG_CODE(DBG_HIBERNATE, 0) | DBG_FUNC_END, start, elapsed,
			elapsed_trace_start, acpi_wake_abstime);

	/* Restore power management register state */
	pmCPUMarkRunning(current_cpu_datap());

	/* Restore power management timer state */
	pmTimerRestore();

	/* Restart timer interrupts */
	rtc_timer_start();

#if HIBERNATION

	kprintf("ret from acpi_sleep_cpu hib=%d\n", did_hibernate);
#endif

#if CONFIG_SLEEP
	/* Becase we don't save the bootstrap page, and we share it
	 * between sleep and mp slave init, we need to recreate it 
	 * after coming back from sleep or hibernate */
	install_real_mode_bootstrap(slave_pstart);
#endif
}