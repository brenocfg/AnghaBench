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

/* Variables and functions */
 int /*<<< orphan*/  MAX_CALLSTACK_FRAMES ; 
 unsigned int actionc ; 
 int /*<<< orphan*/  kperf_action_set_filter (unsigned int,int) ; 
 int /*<<< orphan*/  kperf_action_set_kcallstack_depth (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kperf_action_set_samplers (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kperf_action_set_ucallstack_depth (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kperf_action_set_userdata (unsigned int,int /*<<< orphan*/ ) ; 

void
kperf_action_reset(void)
{
	for (unsigned int i = 0; i < actionc; i++) {
		kperf_action_set_samplers(i + 1, 0);
		kperf_action_set_userdata(i + 1, 0);
		kperf_action_set_filter(i + 1, -1);
		kperf_action_set_ucallstack_depth(i + 1, MAX_CALLSTACK_FRAMES);
		kperf_action_set_kcallstack_depth(i + 1, MAX_CALLSTACK_FRAMES);
	}
}