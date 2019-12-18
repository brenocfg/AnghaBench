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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int TRAP (struct pt_regs*) ; 
 int /*<<< orphan*/  bus_error_jmp ; 
 int fault_except ; 
 int fault_type ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int handle_fault(struct pt_regs *regs)
{
	fault_except = TRAP(regs);
	switch (TRAP(regs)) {
	case 0x200:
		fault_type = 0;
		break;
	case 0x300:
	case 0x380:
		fault_type = 1;
		break;
	default:
		fault_type = 2;
	}

	longjmp(bus_error_jmp, 1);

	return 0;
}