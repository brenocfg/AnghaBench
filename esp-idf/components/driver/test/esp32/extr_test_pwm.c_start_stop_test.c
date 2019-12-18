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
typedef  int /*<<< orphan*/  mcpwm_unit_t ;
typedef  int /*<<< orphan*/  mcpwm_timer_t ;
typedef  int /*<<< orphan*/  mcpwm_io_signals_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  judge_count_value (int,int) ; 
 int /*<<< orphan*/  mcpwm_basic_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_stop (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void start_stop_test(mcpwm_unit_t unit, mcpwm_io_signals_t mcpwm_a, mcpwm_io_signals_t mcpwm_b, mcpwm_timer_t timer)
{
    mcpwm_basic_config(unit, mcpwm_a, mcpwm_b, timer);
    judge_count_value(2, 1000);
    TEST_ESP_OK(mcpwm_stop(unit, timer));
    vTaskDelay(10 / portTICK_RATE_MS); // wait for a while, stop totally
    judge_count_value(0, 0);
    TEST_ESP_OK(mcpwm_start(unit, timer));
    vTaskDelay(10 / portTICK_RATE_MS); // wait for a while, start totally
    judge_count_value(2, 1000);
}