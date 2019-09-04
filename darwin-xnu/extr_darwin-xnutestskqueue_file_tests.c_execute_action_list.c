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
typedef  int /*<<< orphan*/  action_t ;

/* Variables and functions */
 int /*<<< orphan*/  T_LOG (char*,int,...) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ execute_action (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int
execute_action_list(action_t *actions, int nactions, int failout) 
{
	int i, res;
	for (i = 0, res = 0; (0 == res || (!failout)) && (i < nactions); i++) {
		T_LOG("Starting prep action %d\n", i);
		res = *((int *) execute_action(&(actions[i])));
		if(res != 0) {
			T_LOG("Action list failed on step %d. res = %d errno = %d (%s)\n", i, res,
				errno, strerror(errno));
		} else {
			T_LOG("Action list work succeeded on step %d.\n", i);
		}
	}

	return res;
}