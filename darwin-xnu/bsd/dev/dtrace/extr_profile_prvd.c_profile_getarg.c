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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  dtrace_id_t ;

/* Variables and functions */

__attribute__((used)) static uint64_t
profile_getarg(void *arg, dtrace_id_t id, void *parg, int argno, int aframes)
{
#pragma unused(arg, id, parg, argno, aframes)
	/*
	 * All the required arguments for the profile probe are passed directly
	 * to dtrace_probe, and we do not go through dtrace_getarg which doesn't
	 * know how to hop to the kernel stack from the interrupt stack like
	 * dtrace_getpcstack
	 */
	return 0;
}