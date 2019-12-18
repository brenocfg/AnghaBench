#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  task_t ;

/* Variables and functions */
 scalar_t__ PBT_TIMEOUT_CYCLES ; 
 int /*<<< orphan*/  TRUE ; 
 int cpu_number () ; 
 int /*<<< orphan*/  current_task () ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  hw_atomic_add (scalar_t__*,int) ; 
 int /*<<< orphan*/  hw_atomic_sub (scalar_t__*,int) ; 
 int /*<<< orphan*/  hw_lock_to (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  hw_lock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic_display_system_configuration (int /*<<< orphan*/ ) ; 
 scalar_t__ pbtcnt ; 
 int pbtcpu ; 
 int /*<<< orphan*/  pbtlock ; 
 int /*<<< orphan*/  print_tasks_user_threads (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_thread_num_that_crashed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_threads_registers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_uuid_info (int /*<<< orphan*/ ) ; 
 scalar_t__ rdtsc64 () ; 

void print_launchd_info(void)
{
	task_t		task = current_task();
	thread_t	thread = current_thread();
	volatile	uint32_t *ppbtcnt = &pbtcnt;
	uint64_t	bt_tsc_timeout;
	int		cn = cpu_number();

	if(pbtcpu != cn) {
		hw_atomic_add(&pbtcnt, 1);
		/* Spin on print backtrace lock, which serializes output
		 * Continue anyway if a timeout occurs.
		 */
		hw_lock_to(&pbtlock, ~0U);
		pbtcpu = cn;
	}
	
	print_uuid_info(task);
	print_thread_num_that_crashed(task);
	print_threads_registers(thread);
	print_tasks_user_threads(task);

	panic_display_system_configuration(TRUE);
	
	/* Release print backtrace lock, to permit other callers in the
	 * event of panics on multiple processors.
	 */
	hw_lock_unlock(&pbtlock);
	hw_atomic_sub(&pbtcnt, 1);
	/* Wait for other processors to complete output
	 * Timeout and continue after PBT_TIMEOUT_CYCLES.
	 */
	bt_tsc_timeout = rdtsc64() + PBT_TIMEOUT_CYCLES;
	while(*ppbtcnt && (rdtsc64() < bt_tsc_timeout));

}