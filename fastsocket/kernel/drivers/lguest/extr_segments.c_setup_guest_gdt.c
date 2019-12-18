#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* gdt; } ;
struct lg_cpu {TYPE_1__ arch; } ;
struct TYPE_5__ {int b; } ;

/* Variables and functions */
 TYPE_2__ FULL_EXEC_SEGMENT ; 
 TYPE_2__ FULL_SEGMENT ; 
 size_t GDT_ENTRY_KERNEL_CS ; 
 size_t GDT_ENTRY_KERNEL_DS ; 
 int GUEST_PL ; 

void setup_guest_gdt(struct lg_cpu *cpu)
{
	/*
	 * Start with full 0-4G segments...except the Guest is allowed to use
	 * them, so set the privilege level appropriately in the flags.
	 */
	cpu->arch.gdt[GDT_ENTRY_KERNEL_CS] = FULL_EXEC_SEGMENT;
	cpu->arch.gdt[GDT_ENTRY_KERNEL_DS] = FULL_SEGMENT;
	cpu->arch.gdt[GDT_ENTRY_KERNEL_CS].b |= (GUEST_PL << 13);
	cpu->arch.gdt[GDT_ENTRY_KERNEL_DS].b |= (GUEST_PL << 13);
}