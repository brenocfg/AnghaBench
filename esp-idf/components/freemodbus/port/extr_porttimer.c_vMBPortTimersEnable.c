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
 int /*<<< orphan*/  ESP_ERROR_CHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_enable_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_pause (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_set_counter_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 
 int /*<<< orphan*/  timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usTimerGroupIndex ; 
 int /*<<< orphan*/  usTimerIndex ; 

void vMBPortTimersEnable(void)
{
#ifdef CONFIG_FMB_TIMER_PORT_ENABLED
    ESP_ERROR_CHECK(timer_pause(usTimerGroupIndex, usTimerIndex));
    ESP_ERROR_CHECK(timer_set_counter_value(usTimerGroupIndex, usTimerIndex, 0ULL));
    ESP_ERROR_CHECK(timer_enable_intr(usTimerGroupIndex, usTimerIndex));
    ESP_ERROR_CHECK(timer_start(usTimerGroupIndex, usTimerIndex));
#endif
}