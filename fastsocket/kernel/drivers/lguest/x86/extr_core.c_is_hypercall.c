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
struct TYPE_2__ {int cs; int /*<<< orphan*/  eip; } ;

/* Variables and functions */
 int GUEST_PL ; 
 int /*<<< orphan*/  __lgread (struct lg_cpu*,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  guest_pa (struct lg_cpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool is_hypercall(struct lg_cpu *cpu)
{
	u8 insn[3];

	/*
	 * This must be the Guest kernel trying to do something.
	 * The bottom two bits of the CS segment register are the privilege
	 * level.
	 */
	if ((cpu->regs->cs & 3) != GUEST_PL)
		return false;

	/* Is it a vmcall? */
	__lgread(cpu, insn, guest_pa(cpu, cpu->regs->eip), sizeof(insn));
	return insn[0] == 0x0f && insn[1] == 0x01 && insn[2] == 0xc1;
}