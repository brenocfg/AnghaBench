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
 int kperf_kdebug_cswitch ; 
 int /*<<< orphan*/  kperf_on_cpu_update () ; 

int
kperf_kdbg_cswitch_set(int newval)
{
	kperf_kdebug_cswitch = newval;
	kperf_on_cpu_update();

	return 0;
}