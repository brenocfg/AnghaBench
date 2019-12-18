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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  p_pid; } ;

/* Variables and functions */
 int BSDDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BSD_MEMSTAT_FAST_JETSAM ; 
 int /*<<< orphan*/  DBG_BSD_MEMSTAT ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  DBG_MACH_SCHED ; 
 int /*<<< orphan*/  DBG_THROTTLE ; 
 int FSDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IO_THROTTLE_DISABLE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_CPU_THROTTLE_DISABLE ; 
#define  SYS_OVERRIDE_CPU_THROTTLE 130 
#define  SYS_OVERRIDE_FAST_JETSAM 129 
#define  SYS_OVERRIDE_IO_THROTTLE 128 
 TYPE_1__* current_proc () ; 
 int /*<<< orphan*/  memorystatus_fast_jetsam_override (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  sys_override_cpu_throttle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sys_override_io_throttle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
system_override_callouts(uint64_t flags, boolean_t enable_override)
{
	switch (flags) {
		case SYS_OVERRIDE_IO_THROTTLE:
			if (enable_override) {
				KERNEL_DEBUG_CONSTANT(FSDBG_CODE(DBG_THROTTLE, IO_THROTTLE_DISABLE) | DBG_FUNC_START, 
					current_proc()->p_pid, 0, 0, 0, 0);
			} else {
				KERNEL_DEBUG_CONSTANT(FSDBG_CODE(DBG_THROTTLE, IO_THROTTLE_DISABLE) | DBG_FUNC_END, 
					current_proc()->p_pid, 0, 0, 0, 0);
			}
			sys_override_io_throttle(enable_override);
			break;

		case SYS_OVERRIDE_CPU_THROTTLE:
			if (enable_override) {
				KERNEL_DEBUG_CONSTANT(MACHDBG_CODE(DBG_MACH_SCHED, MACH_CPU_THROTTLE_DISABLE) | DBG_FUNC_START, 
					current_proc()->p_pid, 0, 0, 0, 0);
			} else {
				KERNEL_DEBUG_CONSTANT(MACHDBG_CODE(DBG_MACH_SCHED, MACH_CPU_THROTTLE_DISABLE) | DBG_FUNC_END, 
					current_proc()->p_pid, 0, 0, 0, 0);
			}
			sys_override_cpu_throttle(enable_override);
			break;

		case SYS_OVERRIDE_FAST_JETSAM:
			if (enable_override) {
				KERNEL_DEBUG_CONSTANT(BSDDBG_CODE(DBG_BSD_MEMSTAT, BSD_MEMSTAT_FAST_JETSAM) | DBG_FUNC_START, 
					current_proc()->p_pid, 0, 0, 0, 0);
			} else {
				KERNEL_DEBUG_CONSTANT(BSDDBG_CODE(DBG_BSD_MEMSTAT, BSD_MEMSTAT_FAST_JETSAM) | DBG_FUNC_END, 
					current_proc()->p_pid, 0, 0, 0, 0);
			}
#if CONFIG_JETSAM
			memorystatus_fast_jetsam_override(enable_override);
#endif /* CONFIG_JETSAM */
			break;

		default:
			panic("Unknown option to system_override_callouts(): %llu\n", flags);
	}
}