#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* usimple_lock_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_8__ {int /*<<< orphan*/  lock_data; } ;
struct TYPE_9__ {TYPE_1__ interlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NMIPI_panic (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPINLOCK_TIMEOUT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  cpu_signal_handler (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_cpumask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  mach_absolute_time () ; 
 scalar_t__ ml_get_interrupts_enabled () ; 
 scalar_t__ mp_spin_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,TYPE_2__*,uintptr_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdtsc64 () ; 
 int /*<<< orphan*/  simple_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  simple_lock_try (TYPE_2__*) ; 
 TYPE_2__* spinlock_timed_out ; 
 int /*<<< orphan*/  spinlock_timeout_NMI (uintptr_t) ; 

boolean_t
mp_safe_spin_lock(usimple_lock_t lock)
{
	if (ml_get_interrupts_enabled()) {
		simple_lock(lock);
		return TRUE;
	} else {
		uint64_t tsc_spin_start = rdtsc64();
		while (!simple_lock_try(lock)) {
			cpu_signal_handler(NULL);
			if (mp_spin_timeout(tsc_spin_start)) {
				uint32_t lock_cpu;
				uintptr_t lowner = (uintptr_t)
						   lock->interlock.lock_data;
				spinlock_timed_out = lock;
				lock_cpu = spinlock_timeout_NMI(lowner);
				NMIPI_panic(cpu_to_cpumask(lock_cpu), SPINLOCK_TIMEOUT);
				panic("mp_safe_spin_lock() timed out, lock: %p, owner thread: 0x%lx, current_thread: %p, owner on CPU 0x%x, time: %llu",
				      lock, lowner, current_thread(), lock_cpu, mach_absolute_time());
			}
		}
		return FALSE;
	} 
}