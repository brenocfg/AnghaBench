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
typedef  int mach_msg_type_number_t ;
typedef  int /*<<< orphan*/  mach_exception_data_type_t ;
typedef  int /*<<< orphan*/  exception_type_t ;
typedef  int /*<<< orphan*/  arm_saved_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXC_ARM_UNDEFINED ; 
 int /*<<< orphan*/  EXC_BAD_INSTRUCTION ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exception_triage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  get_saved_state_sp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
handle_wf_trap(arm_saved_state_t *ss)
{
	exception_type_t exc;
	mach_exception_data_type_t codes[2];
	mach_msg_type_number_t numcodes = 2;

	exc = EXC_BAD_INSTRUCTION;
	codes[0] = EXC_ARM_UNDEFINED;
	codes[1] = get_saved_state_sp(ss);

	exception_triage(exc, codes, numcodes);
	assert(0); /* NOTREACHED */
}