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
struct TYPE_2__ {int cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPI_handler (int) ; 
 TYPE_1__* current_thread_info () ; 

int smp_sigio_handler(void)
{
#ifdef CONFIG_SMP
	int cpu = current_thread_info()->cpu;
	IPI_handler(cpu);
	if (cpu != 0)
		return 1;
#endif
	return 0;
}