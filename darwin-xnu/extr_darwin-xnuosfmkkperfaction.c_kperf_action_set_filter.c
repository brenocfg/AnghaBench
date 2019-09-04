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
kperf_action_set_filter(unsigned actionid, int pid)
{
	if ((actionid > actionc) || (actionid == 0)) {
		return EINVAL;
	}

	actionv[actionid - 1].pid_filter = pid;

	return 0;
}