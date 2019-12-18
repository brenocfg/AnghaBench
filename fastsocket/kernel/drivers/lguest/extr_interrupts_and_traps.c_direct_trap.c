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

/* Variables and functions */
 unsigned int FIRST_EXTERNAL_VECTOR ; 
 unsigned int LGUEST_TRAP_ENTRY ; 
 int /*<<< orphan*/  could_be_syscall (unsigned int) ; 

__attribute__((used)) static bool direct_trap(unsigned int num)
{
	/*
	 * Hardware interrupts don't go to the Guest at all (except system
	 * call).
	 */
	if (num >= FIRST_EXTERNAL_VECTOR && !could_be_syscall(num))
		return false;

	/*
	 * The Host needs to see page faults (for shadow paging and to save the
	 * fault address), general protection faults (in/out emulation) and
	 * device not available (TS handling), invalid opcode fault (kvm hcall),
	 * and of course, the hypercall trap.
	 */
	return num != 14 && num != 13 && num != 7 &&
			num != 6 && num != LGUEST_TRAP_ENTRY;
}