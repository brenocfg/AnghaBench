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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  ucallstack_depth; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAX_CALLSTACK_FRAMES ; 
 unsigned int actionc ; 
 TYPE_1__* actionv ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 

int
kperf_action_get_ucallstack_depth(unsigned action_id, uint32_t * depth_out)
{
	if ((action_id > actionc)) {
		return EINVAL;
	}

	assert(depth_out);

	if (action_id == 0) {
		*depth_out = MAX_CALLSTACK_FRAMES;
	} else {
		*depth_out = actionv[action_id - 1].ucallstack_depth;
	}

	return 0;
}