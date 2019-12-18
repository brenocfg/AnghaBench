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
typedef  int /*<<< orphan*/  instr ;

/* Variables and functions */
 scalar_t__ IS_MTMSRD (unsigned int) ; 
 scalar_t__ IS_RFID (unsigned int) ; 
 int /*<<< orphan*/  is_kernel_addr (unsigned long) ; 
 int /*<<< orphan*/  mread (unsigned long,unsigned int*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static long check_bp_loc(unsigned long addr)
{
	unsigned int instr;

	addr &= ~3;
	if (!is_kernel_addr(addr)) {
		printf("Breakpoints may only be placed at kernel addresses\n");
		return 0;
	}
	if (!mread(addr, &instr, sizeof(instr))) {
		printf("Can't read instruction at address %lx\n", addr);
		return 0;
	}
	if (IS_MTMSRD(instr) || IS_RFID(instr)) {
		printf("Breakpoints may not be placed on mtmsrd or rfid "
		       "instructions\n");
		return 0;
	}
	return 1;
}