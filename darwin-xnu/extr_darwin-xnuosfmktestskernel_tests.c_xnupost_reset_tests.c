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
typedef  TYPE_1__* xnupost_test_t ;
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_3__ {int xt_retval; int /*<<< orphan*/  xt_test_actions; scalar_t__ xt_end_time; scalar_t__ xt_begin_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  XT_ACTION_NONE ; 

kern_return_t
xnupost_reset_tests(xnupost_test_t test_list, uint32_t test_count)
{
	uint32_t i = 0;
	xnupost_test_t testp;
	for (; i < test_count; i++) {
		testp                  = &test_list[i];
		testp->xt_begin_time   = 0;
		testp->xt_end_time     = 0;
		testp->xt_test_actions = XT_ACTION_NONE;
		testp->xt_retval       = -1;
	}
	return KERN_SUCCESS;
}