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
 int /*<<< orphan*/  i386_send_NMI (int) ; 
 scalar_t__ smp_initialized ; 

void
cpu_NMI_interrupt(int cpu)
{
	if (smp_initialized) {
		i386_send_NMI(cpu);
	}
}