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
 int /*<<< orphan*/  prom_cpu0_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_call_function (int /*<<< orphan*/  (*) (int /*<<< orphan*/ *),int /*<<< orphan*/ *,int) ; 
 scalar_t__ smp_processor_id () ; 

__attribute__((used)) static void prom_exit(void)
{
#ifdef CONFIG_SMP
	if (smp_processor_id())
		/* CPU 1 */
		smp_call_function(prom_cpu0_exit, NULL, 1);
#endif
	prom_cpu0_exit(NULL);
}