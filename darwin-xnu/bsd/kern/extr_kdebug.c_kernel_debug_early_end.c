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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {scalar_t__ oldest_time; } ;
struct TYPE_3__ {int /*<<< orphan*/  arg4; int /*<<< orphan*/  arg3; int /*<<< orphan*/  arg2; int /*<<< orphan*/  arg1; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  debugid; } ;

/* Variables and functions */
 int /*<<< orphan*/  KDBG_RELEASE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRACE_LOST_EVENTS ; 
 int /*<<< orphan*/  TRACE_TIMESTAMPS ; 
 scalar_t__ cpu_number () ; 
 TYPE_2__ kd_ctrl_page ; 
 TYPE_1__* kd_early_buffer ; 
 int kd_early_done ; 
 unsigned int kd_early_index ; 
 scalar_t__ kd_early_overflow ; 
 int /*<<< orphan*/  kernel_debug_enter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_debug_string_early (char*) ; 
 scalar_t__ master_cpu ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  tsc_at_boot ; 
 int tsc_rebase_abs_time ; 

__attribute__((used)) static void
kernel_debug_early_end(void)
{
	if (cpu_number() != master_cpu) {
		panic("kernel_debug_early_end() not call on boot processor");
	}

	/* reset the current oldest time to allow early events */
	kd_ctrl_page.oldest_time = 0;

#if !CONFIG_EMBEDDED
	/* Fake sentinel marking the start of kernel time relative to TSC */
	kernel_debug_enter(0,
			TRACE_TIMESTAMPS,
			0,
			(uint32_t)(tsc_rebase_abs_time >> 32),
			(uint32_t)tsc_rebase_abs_time,
			tsc_at_boot,
			0,
			0);
#endif
	for (unsigned int i = 0; i < kd_early_index; i++) {
		kernel_debug_enter(0,
			kd_early_buffer[i].debugid,
			kd_early_buffer[i].timestamp,
			kd_early_buffer[i].arg1,
			kd_early_buffer[i].arg2,
			kd_early_buffer[i].arg3,
			kd_early_buffer[i].arg4,
			0);
	}

	/* Cut events-lost event on overflow */
	if (kd_early_overflow) {
		KDBG_RELEASE(TRACE_LOST_EVENTS, 1);
	}

	kd_early_done = true;

	/* This trace marks the start of kernel tracing */
	kernel_debug_string_early("early trace done");
}