#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_3__ {int member_0; scalar_t__ const far; } ;
typedef  TYPE_1__ ex_cb_state_t ;
typedef  scalar_t__ ex_cb_action_t ;

/* Variables and functions */
 scalar_t__ EXCB_ACTION_NONE ; 
 scalar_t__ EXCB_ACTION_RERUN ; 
 int /*<<< orphan*/  EXCB_CLASS_TEST1 ; 
 int /*<<< orphan*/  EXCB_CLASS_TEST2 ; 
 int /*<<< orphan*/  EXCB_CLASS_TEST3 ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  T_ASSERT (int,char*) ; 
 int /*<<< orphan*/  T_LOG (char*) ; 
 scalar_t__ ex_cb_invoke (int /*<<< orphan*/ ,scalar_t__ const) ; 
 scalar_t__ ex_cb_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  excb_test_action ; 

kern_return_t
ex_cb_test()
{
	const vm_offset_t far1 = 0xdead0001;
	const vm_offset_t far2 = 0xdead0002;
	kern_return_t kr;
	ex_cb_state_t test_context_1 = {0xdeadbeef};
	ex_cb_state_t test_context_2 = {0xdeadbeef};
	ex_cb_action_t action;

	T_LOG("Testing Exception Callback.");
	
	T_LOG("Running registration test.");

	kr = ex_cb_register(EXCB_CLASS_TEST1, &excb_test_action, &test_context_1);
	T_ASSERT(KERN_SUCCESS == kr, "First registration of TEST1 exception callback");
	kr = ex_cb_register(EXCB_CLASS_TEST2, &excb_test_action, &test_context_2);
	T_ASSERT(KERN_SUCCESS == kr, "First registration of TEST2 exception callback");

	kr = ex_cb_register(EXCB_CLASS_TEST2, &excb_test_action, &test_context_2);
	T_ASSERT(KERN_SUCCESS != kr, "Second registration of TEST2 exception callback");
	kr = ex_cb_register(EXCB_CLASS_TEST1, &excb_test_action, &test_context_1);
	T_ASSERT(KERN_SUCCESS != kr, "Second registration of TEST1 exception callback");

	T_LOG("Running invocation test.");

	action = ex_cb_invoke(EXCB_CLASS_TEST1, far1);
	T_ASSERT(EXCB_ACTION_RERUN == action, NULL);
	T_ASSERT(far1 == test_context_1.far, NULL);

	action = ex_cb_invoke(EXCB_CLASS_TEST2, far2);
	T_ASSERT(EXCB_ACTION_NONE == action, NULL);
	T_ASSERT(far2 == test_context_2.far, NULL);

	action = ex_cb_invoke(EXCB_CLASS_TEST3, 0);
	T_ASSERT(EXCB_ACTION_NONE == action, NULL);

	return KERN_SUCCESS;
}