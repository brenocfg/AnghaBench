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
struct lguest_ro_state {int /*<<< orphan*/  guest_tss; struct desc_struct* guest_gdt; } ;
struct desc_struct {int a; int b; } ;

/* Variables and functions */
 struct desc_struct FULL_EXEC_SEGMENT ; 
 struct desc_struct FULL_SEGMENT ; 
 size_t GDT_ENTRY_LGUEST_CS ; 
 size_t GDT_ENTRY_LGUEST_DS ; 
 size_t GDT_ENTRY_TSS ; 

void setup_default_gdt_entries(struct lguest_ro_state *state)
{
	struct desc_struct *gdt = state->guest_gdt;
	unsigned long tss = (unsigned long)&state->guest_tss;

	/* The Switcher segments are full 0-4G segments, privilege level 0 */
	gdt[GDT_ENTRY_LGUEST_CS] = FULL_EXEC_SEGMENT;
	gdt[GDT_ENTRY_LGUEST_DS] = FULL_SEGMENT;

	/*
	 * The TSS segment refers to the TSS entry for this particular CPU.
	 * Forgive the magic flags: the 0x8900 means the entry is Present, it's
	 * privilege level 0 Available 386 TSS system segment, and the 0x67
	 * means Saturn is eclipsed by Mercury in the twelfth house.
	 */
	gdt[GDT_ENTRY_TSS].a = 0x00000067 | (tss << 16);
	gdt[GDT_ENTRY_TSS].b = 0x00008900 | (tss & 0xFF000000)
		| ((tss >> 16) & 0x000000FF);
}