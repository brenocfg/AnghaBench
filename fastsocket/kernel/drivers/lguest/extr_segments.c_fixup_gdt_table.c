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
struct TYPE_3__ {TYPE_2__* gdt; } ;
struct lg_cpu {TYPE_1__ arch; } ;
struct TYPE_4__ {int b; } ;

/* Variables and functions */
 int GUEST_PL ; 
 scalar_t__ ignored_gdt (unsigned int) ; 

__attribute__((used)) static void fixup_gdt_table(struct lg_cpu *cpu, unsigned start, unsigned end)
{
	unsigned int i;

	for (i = start; i < end; i++) {
		/*
		 * We never copy these ones to real GDT, so we don't care what
		 * they say
		 */
		if (ignored_gdt(i))
			continue;

		/*
		 * Segment descriptors contain a privilege level: the Guest is
		 * sometimes careless and leaves this as 0, even though it's
		 * running at privilege level 1.  If so, we fix it here.
		 */
		if ((cpu->arch.gdt[i].b & 0x00006000) == 0)
			cpu->arch.gdt[i].b |= (GUEST_PL << 13);

		/*
		 * Each descriptor has an "accessed" bit.  If we don't set it
		 * now, the CPU will try to set it when the Guest first loads
		 * that entry into a segment register.  But the GDT isn't
		 * writable by the Guest, so bad things can happen.
		 */
		cpu->arch.gdt[i].b |= 0x00000100;
	}
}