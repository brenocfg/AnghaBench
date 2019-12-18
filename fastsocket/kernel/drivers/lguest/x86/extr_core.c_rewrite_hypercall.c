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
typedef  int u8 ;
struct lg_cpu {TYPE_1__* regs; } ;
typedef  int /*<<< orphan*/  insn ;
struct TYPE_2__ {int /*<<< orphan*/  eip; } ;

/* Variables and functions */
 int /*<<< orphan*/  __lgwrite (struct lg_cpu*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  guest_pa (struct lg_cpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  guest_pagetable_clear_all (struct lg_cpu*) ; 

__attribute__((used)) static void rewrite_hypercall(struct lg_cpu *cpu)
{
	/*
	 * This are the opcodes we use to patch the Guest.  The opcode for "int
	 * $0x1f" is "0xcd 0x1f" but vmcall instruction is 3 bytes long, so we
	 * complete the sequence with a NOP (0x90).
	 */
	u8 insn[3] = {0xcd, 0x1f, 0x90};

	__lgwrite(cpu, guest_pa(cpu, cpu->regs->eip), insn, sizeof(insn));
	/*
	 * The above write might have caused a copy of that page to be made
	 * (if it was read-only).  We need to make sure the Guest has
	 * up-to-date pagetables.  As this doesn't happen often, we can just
	 * drop them all.
	 */
	guest_pagetable_clear_all(cpu);
}