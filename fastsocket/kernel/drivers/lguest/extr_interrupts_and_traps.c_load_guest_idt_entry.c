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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/ * idt; } ;
struct lg_cpu {TYPE_1__ arch; int /*<<< orphan*/  changed; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CHANGED_IDT ; 
 unsigned int LGUEST_TRAP_ENTRY ; 
 int /*<<< orphan*/  kill_guest (struct lg_cpu*,char*,unsigned int) ; 
 int /*<<< orphan*/  set_trap (struct lg_cpu*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void load_guest_idt_entry(struct lg_cpu *cpu, unsigned int num, u32 lo, u32 hi)
{
	/*
	 * Guest never handles: NMI, doublefault, spurious interrupt or
	 * hypercall.  We ignore when it tries to set them.
	 */
	if (num == 2 || num == 8 || num == 15 || num == LGUEST_TRAP_ENTRY)
		return;

	/*
	 * Mark the IDT as changed: next time the Guest runs we'll know we have
	 * to copy this again.
	 */
	cpu->changed |= CHANGED_IDT;

	/* Check that the Guest doesn't try to step outside the bounds. */
	if (num >= ARRAY_SIZE(cpu->arch.idt))
		kill_guest(cpu, "Setting idt entry %u", num);
	else
		set_trap(cpu, &cpu->arch.idt[num], num, lo, hi);
}