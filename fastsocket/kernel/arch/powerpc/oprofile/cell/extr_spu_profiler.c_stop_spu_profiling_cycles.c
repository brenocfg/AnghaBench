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
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  samples ; 
 scalar_t__ spu_prof_running ; 
 int /*<<< orphan*/  timer ; 

void stop_spu_profiling_cycles(void)
{
	spu_prof_running = 0;
	hrtimer_cancel(&timer);
	kfree(samples);
	pr_debug("SPU_PROF: stop_spu_profiling_cycles issued\n");
}