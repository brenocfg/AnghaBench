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
 int /*<<< orphan*/  register_deep_sleep () ; 
 int /*<<< orphan*/  register_free () ; 
 int /*<<< orphan*/  register_heap () ; 
 int /*<<< orphan*/  register_light_sleep () ; 
 int /*<<< orphan*/  register_restart () ; 
 int /*<<< orphan*/  register_tasks () ; 
 int /*<<< orphan*/  register_version () ; 

void register_system(void)
{
    register_free();
    register_heap();
    register_version();
    register_restart();
    register_deep_sleep();
    register_light_sleep();
#if WITH_TASKS_INFO
    register_tasks();
#endif
}