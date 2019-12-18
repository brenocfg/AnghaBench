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
typedef  int u8 ;
typedef  int u32 ;
struct lg_cpu {int dummy; } ;
struct desc_struct {int a; int b; } ;

/* Variables and functions */
 int GUEST_PL ; 
 int __KERNEL_CS ; 
 int /*<<< orphan*/  idt_present (int,int) ; 
 int idt_type (int,int) ; 
 int /*<<< orphan*/  kill_guest (struct lg_cpu*,char*,int) ; 

__attribute__((used)) static void set_trap(struct lg_cpu *cpu, struct desc_struct *trap,
		     unsigned int num, u32 lo, u32 hi)
{
	u8 type = idt_type(lo, hi);

	/* We zero-out a not-present entry */
	if (!idt_present(lo, hi)) {
		trap->a = trap->b = 0;
		return;
	}

	/* We only support interrupt and trap gates. */
	if (type != 0xE && type != 0xF)
		kill_guest(cpu, "bad IDT type %i", type);

	/*
	 * We only copy the handler address, present bit, privilege level and
	 * type.  The privilege level controls where the trap can be triggered
	 * manually with an "int" instruction.  This is usually GUEST_PL,
	 * except for system calls which userspace can use.
	 */
	trap->a = ((__KERNEL_CS|GUEST_PL)<<16) | (lo&0x0000FFFF);
	trap->b = (hi&0xFFFFEF00);
}