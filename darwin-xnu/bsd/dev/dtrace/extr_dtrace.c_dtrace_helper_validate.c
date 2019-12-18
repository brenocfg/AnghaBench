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
struct TYPE_3__ {int dtha_nactions; int /*<<< orphan*/ ** dtha_actions; int /*<<< orphan*/ * dtha_predicate; } ;
typedef  TYPE_1__ dtrace_helper_action_t ;
typedef  int /*<<< orphan*/  dtrace_difo_t ;

/* Variables and functions */
 scalar_t__ dtrace_difo_validate_helper (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dtrace_helper_validate(dtrace_helper_action_t *helper)
{
	int err = 0, i;
	dtrace_difo_t *dp;

	if ((dp = helper->dtha_predicate) != NULL)
		err += dtrace_difo_validate_helper(dp);

	for (i = 0; i < helper->dtha_nactions; i++)
		err += dtrace_difo_validate_helper(helper->dtha_actions[i]);

	return (err == 0);
}