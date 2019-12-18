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
typedef  int /*<<< orphan*/  dtrace_probedesc_t ;

/* Variables and functions */

__attribute__((used)) static void
fasttrap_pid_provide(void *arg, const dtrace_probedesc_t *desc)
{
#pragma unused(arg, desc)
	/*
	 * There are no "default" pid probes.
	 */
}