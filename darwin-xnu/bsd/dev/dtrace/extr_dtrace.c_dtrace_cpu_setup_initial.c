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
typedef  int /*<<< orphan*/  processorid_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_CONFIG ; 
 int /*<<< orphan*/  dtrace_cpu_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dtrace_cpu_setup_initial(processorid_t cpu)
{
	(void) dtrace_cpu_setup(CPU_CONFIG, cpu);
}