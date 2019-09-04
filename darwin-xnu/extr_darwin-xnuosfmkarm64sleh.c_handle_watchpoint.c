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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  mach_exception_data_type_t ;
typedef  int /*<<< orphan*/  exception_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXC_ARM_DA_DEBUG ; 
 int /*<<< orphan*/  EXC_BREAKPOINT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exception_triage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
handle_watchpoint(vm_offset_t fault_addr)
{
	exception_type_t 			exception = EXC_BREAKPOINT;
	mach_exception_data_type_t 	codes[2] = {EXC_ARM_DA_DEBUG};
	mach_msg_type_number_t 		numcodes = 2;

	codes[1] = fault_addr;
	exception_triage(exception, codes, numcodes);
	assert(0); /* NOTREACHED */
}