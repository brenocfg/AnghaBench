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
 int /*<<< orphan*/  bdi_arm_supers_timer () ; 
 int /*<<< orphan*/  sync_supers_tsk ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sync_supers_timer_fn(unsigned long unused)
{
	wake_up_process(sync_supers_tsk);
	bdi_arm_supers_timer();
}