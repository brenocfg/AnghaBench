#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int pid_filter; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int actionc ; 
 TYPE_1__* actionv ; 

int
kperf_action_get_filter(unsigned actionid, int *pid_out)
{
	if ((actionid > actionc)) {
		return EINVAL;
	}

	if (actionid == 0) {
		*pid_out = -1; /* "NULL" action */
	} else {
		*pid_out = actionv[actionid - 1].pid_filter;
	}

	return 0;
}