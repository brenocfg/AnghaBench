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
struct TYPE_3__ {TYPE_2__* gdt; } ;
struct lg_cpu {int /*<<< orphan*/  changed; TYPE_1__ arch; } ;
struct TYPE_4__ {size_t a; size_t b; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  CHANGED_GDT ; 
 int /*<<< orphan*/  fixup_gdt_table (struct lg_cpu*,size_t,size_t) ; 
 int /*<<< orphan*/  kill_guest (struct lg_cpu*,char*,size_t) ; 

void load_guest_gdt_entry(struct lg_cpu *cpu, u32 num, u32 lo, u32 hi)
{
	/*
	 * We assume the Guest has the same number of GDT entries as the
	 * Host, otherwise we'd have to dynamically allocate the Guest GDT.
	 */
	if (num >= ARRAY_SIZE(cpu->arch.gdt)) {
		kill_guest(cpu, "too many gdt entries %i", num);
		return;
	}

	/* Set it up, then fix it. */
	cpu->arch.gdt[num].a = lo;
	cpu->arch.gdt[num].b = hi;
	fixup_gdt_table(cpu, num, num+1);
	/*
	 * Mark that the GDT changed so the core knows it has to copy it again,
	 * even if the Guest is run on the same CPU.
	 */
	cpu->changed |= CHANGED_GDT;
}