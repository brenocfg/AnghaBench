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
typedef  size_t u32 ;
struct lg_cpu {TYPE_2__* lg; } ;
typedef  int /*<<< orphan*/  pgd_t ;
struct TYPE_4__ {TYPE_1__* pgdirs; } ;
struct TYPE_3__ {int /*<<< orphan*/ * pgdir; } ;

/* Variables and functions */
 unsigned int SWITCHER_PGD_INDEX ; 
 int /*<<< orphan*/  kill_guest (struct lg_cpu*,char*) ; 
 unsigned int pgd_index (unsigned long) ; 

__attribute__((used)) static pgd_t *spgd_addr(struct lg_cpu *cpu, u32 i, unsigned long vaddr)
{
	unsigned int index = pgd_index(vaddr);

#ifndef CONFIG_X86_PAE
	/* We kill any Guest trying to touch the Switcher addresses. */
	if (index >= SWITCHER_PGD_INDEX) {
		kill_guest(cpu, "attempt to access switcher pages");
		index = 0;
	}
#endif
	/* Return a pointer index'th pgd entry for the i'th page table. */
	return &cpu->lg->pgdirs[i].pgdir[index];
}