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
struct TYPE_2__ {struct desc_struct* idt; } ;
struct lg_cpu {TYPE_1__ arch; } ;
struct desc_struct {int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct desc_struct*) ; 
 int /*<<< orphan*/  default_idt_entry (struct desc_struct*,unsigned int,unsigned long const,struct desc_struct const*) ; 
 int /*<<< orphan*/  direct_trap (unsigned int) ; 
 int idt_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void copy_traps(const struct lg_cpu *cpu, struct desc_struct *idt,
		const unsigned long *def)
{
	unsigned int i;

	/*
	 * We can simply copy the direct traps, otherwise we use the default
	 * ones in the Switcher: they will return to the Host.
	 */
	for (i = 0; i < ARRAY_SIZE(cpu->arch.idt); i++) {
		const struct desc_struct *gidt = &cpu->arch.idt[i];

		/* If no Guest can ever override this trap, leave it alone. */
		if (!direct_trap(i))
			continue;

		/*
		 * Only trap gates (type 15) can go direct to the Guest.
		 * Interrupt gates (type 14) disable interrupts as they are
		 * entered, which we never let the Guest do.  Not present
		 * entries (type 0x0) also can't go direct, of course.
		 *
		 * If it can't go direct, we still need to copy the priv. level:
		 * they might want to give userspace access to a software
		 * interrupt.
		 */
		if (idt_type(gidt->a, gidt->b) == 0xF)
			idt[i] = *gidt;
		else
			default_idt_entry(&idt[i], i, def[i], gidt);
	}
}