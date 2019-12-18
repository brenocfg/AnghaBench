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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 size_t atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cpu_in_kgdb ; 
 int /*<<< orphan*/  kgdb_active ; 
 int /*<<< orphan*/  kgdb_wait (struct pt_regs*) ; 

int kgdb_nmicallback(int cpu, void *regs)
{
#ifdef CONFIG_SMP
	if (!atomic_read(&cpu_in_kgdb[cpu]) &&
			atomic_read(&kgdb_active) != cpu &&
			atomic_read(&cpu_in_kgdb[atomic_read(&kgdb_active)])) {
		kgdb_wait((struct pt_regs *)regs);
		return 0;
	}
#endif
	return 1;
}