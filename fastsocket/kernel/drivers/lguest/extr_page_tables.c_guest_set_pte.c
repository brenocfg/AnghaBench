#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct lg_cpu {TYPE_1__* lg; } ;
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_4__ {scalar_t__ pgdir; } ;
struct TYPE_3__ {unsigned long kernel_address; TYPE_2__* pgdirs; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  do_set_pte (struct lg_cpu*,int,unsigned long,int /*<<< orphan*/ ) ; 
 int find_pgdir (TYPE_1__*,unsigned long) ; 

void guest_set_pte(struct lg_cpu *cpu,
		   unsigned long gpgdir, unsigned long vaddr, pte_t gpte)
{
	/*
	 * Kernel mappings must be changed on all top levels.  Slow, but doesn't
	 * happen often.
	 */
	if (vaddr >= cpu->lg->kernel_address) {
		unsigned int i;
		for (i = 0; i < ARRAY_SIZE(cpu->lg->pgdirs); i++)
			if (cpu->lg->pgdirs[i].pgdir)
				do_set_pte(cpu, i, vaddr, gpte);
	} else {
		/* Is this page table one we have a shadow for? */
		int pgdir = find_pgdir(cpu->lg, gpgdir);
		if (pgdir != ARRAY_SIZE(cpu->lg->pgdirs))
			/* If so, do the update. */
			do_set_pte(cpu, pgdir, vaddr, gpte);
	}
}