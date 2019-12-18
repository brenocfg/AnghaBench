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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ ucallstack_depth; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MAX_CALLSTACK_FRAMES ; 
 unsigned int actionc ; 
 TYPE_1__* actionv ; 

int
kperf_action_set_ucallstack_depth(unsigned action_id, uint32_t depth)
{
	if ((action_id > actionc) || (action_id == 0)) {
		return EINVAL;
	}

	if (depth > MAX_CALLSTACK_FRAMES) {
		return EINVAL;
	}

	actionv[action_id - 1].ucallstack_depth = depth;

	return 0;
}