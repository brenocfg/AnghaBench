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

/* Variables and functions */
 scalar_t__ DEBUGGER_NO_CPU ; 
 int /*<<< orphan*/  OSMemoryBarrier () ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ cpu_number () ; 
 scalar_t__ debugger_cpu ; 

__attribute__((used)) static void
DebuggerUnlock()
{
	assert(debugger_cpu == cpu_number());

	/*
	 * We don't do an atomic exchange here in case
	 * there's another CPU spinning to acquire the debugger_lock
	 * and we never get a chance to update it. We already have the
	 * lock so we can simply store DEBUGGER_NO_CPU and follow with
	 * a barrier.
	 */
	debugger_cpu = DEBUGGER_NO_CPU;
	OSMemoryBarrier();

	return;
}