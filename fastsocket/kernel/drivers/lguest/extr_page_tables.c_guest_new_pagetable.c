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
struct lg_cpu {int cpu_pgd; TYPE_1__* lg; } ;
struct TYPE_2__ {int /*<<< orphan*/  pgdirs; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int find_pgdir (TYPE_1__*,unsigned long) ; 
 int new_pgdir (struct lg_cpu*,unsigned long,int*) ; 
 int /*<<< orphan*/  pin_stack_pages (struct lg_cpu*) ; 

void guest_new_pagetable(struct lg_cpu *cpu, unsigned long pgtable)
{
	int newpgdir, repin = 0;

	/* Look to see if we have this one already. */
	newpgdir = find_pgdir(cpu->lg, pgtable);
	/*
	 * If not, we allocate or mug an existing one: if it's a fresh one,
	 * repin gets set to 1.
	 */
	if (newpgdir == ARRAY_SIZE(cpu->lg->pgdirs))
		newpgdir = new_pgdir(cpu, pgtable, &repin);
	/* Change the current pgd index to the new one. */
	cpu->cpu_pgd = newpgdir;
	/* If it was completely blank, we map in the Guest kernel stack */
	if (repin)
		pin_stack_pages(cpu);
}