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
struct TYPE_3__ {int /*<<< orphan*/  far; } ;
typedef  TYPE_1__ ex_cb_state_t ;
typedef  int ex_cb_class_t ;
typedef  int /*<<< orphan*/  ex_cb_action_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXCB_ACTION_NONE ; 
 int /*<<< orphan*/  EXCB_ACTION_RERUN ; 
 int /*<<< orphan*/  EXCB_ACTION_TEST_FAIL ; 
#define  EXCB_CLASS_TEST1 129 
#define  EXCB_CLASS_TEST2 128 

__attribute__((used)) static ex_cb_action_t excb_test_action(
	ex_cb_class_t		cb_class,
	void				*refcon,
	const ex_cb_state_t	*state
	)
{
	ex_cb_state_t *context = (ex_cb_state_t *)refcon;

	if ((NULL == refcon) || (NULL == state))
	{
		return EXCB_ACTION_TEST_FAIL;
	}

	context->far = state->far;

	switch (cb_class)
	{
		case EXCB_CLASS_TEST1:
			return EXCB_ACTION_RERUN;
		case EXCB_CLASS_TEST2:
			return EXCB_ACTION_NONE;
		default:
			return EXCB_ACTION_TEST_FAIL;
	}
}