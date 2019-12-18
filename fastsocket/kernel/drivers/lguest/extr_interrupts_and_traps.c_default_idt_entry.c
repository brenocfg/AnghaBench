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
typedef  int u32 ;
struct desc_struct {int b; int a; } ;

/* Variables and functions */
 int GUEST_PL ; 
 int LGUEST_CS ; 
 int LGUEST_TRAP_ENTRY ; 

__attribute__((used)) static void default_idt_entry(struct desc_struct *idt,
			      int trap,
			      const unsigned long handler,
			      const struct desc_struct *base)
{
	/* A present interrupt gate. */
	u32 flags = 0x8e00;

	/*
	 * Set the privilege level on the entry for the hypercall: this allows
	 * the Guest to use the "int" instruction to trigger it.
	 */
	if (trap == LGUEST_TRAP_ENTRY)
		flags |= (GUEST_PL << 13);
	else if (base)
		/*
		 * Copy privilege level from what Guest asked for.  This allows
		 * debug (int 3) traps from Guest userspace, for example.
		 */
		flags |= (base->b & 0x6000);

	/* Now pack it into the IDT entry in its weird format. */
	idt->a = (LGUEST_CS<<16) | (handler&0x0000FFFF);
	idt->b = (handler&0xFFFF0000) | flags;
}