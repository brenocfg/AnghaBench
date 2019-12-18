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
 int /*<<< orphan*/  write_c0_perfcontrol (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rm9000_cpu_stop(void *args)
{
	/* Stop all counters on current CPU */
	write_c0_perfcontrol(0);
}