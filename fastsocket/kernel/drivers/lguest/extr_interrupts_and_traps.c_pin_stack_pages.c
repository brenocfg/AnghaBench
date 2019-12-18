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
struct lg_cpu {int esp1; TYPE_1__* lg; } ;
struct TYPE_2__ {unsigned int stack_pages; } ;

/* Variables and functions */
 unsigned int PAGE_SIZE ; 
 int /*<<< orphan*/  pin_page (struct lg_cpu*,int) ; 

void pin_stack_pages(struct lg_cpu *cpu)
{
	unsigned int i;

	/*
	 * Depending on the CONFIG_4KSTACKS option, the Guest can have one or
	 * two pages of stack space.
	 */
	for (i = 0; i < cpu->lg->stack_pages; i++)
		/*
		 * The stack grows *upwards*, so the address we're given is the
		 * start of the page after the kernel stack.  Subtract one to
		 * get back onto the first stack page, and keep subtracting to
		 * get to the rest of the stack pages.
		 */
		pin_page(cpu, cpu->esp1 - 1 - i * PAGE_SIZE);
}