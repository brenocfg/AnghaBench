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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  mcpwm_unit_t ;
typedef  int /*<<< orphan*/  mcpwm_timer_t ;
typedef  int /*<<< orphan*/  mcpwm_io_signals_t ;
typedef  int /*<<< orphan*/  mcpwm_carrier_out_ivt_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  judge_count_value (int,int) ; 
 int /*<<< orphan*/  mcpwm_basic_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_carrier_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_carrier_output_invert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_carrier_set_duty_cycle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_carrier_set_period (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void carrier_with_set_function_test(mcpwm_unit_t unit, mcpwm_io_signals_t mcpwm_a, mcpwm_io_signals_t mcpwm_b, mcpwm_timer_t timer,
        mcpwm_carrier_out_ivt_t invert_or_not, uint8_t period, uint8_t duty, uint8_t os_width)
{
    // no inversion and no one shot
    mcpwm_basic_config(unit, mcpwm_a, mcpwm_b, timer);
    TEST_ESP_OK(mcpwm_carrier_enable(unit, timer));
    TEST_ESP_OK(mcpwm_carrier_set_period(unit, timer, period)); //carrier revolution
    TEST_ESP_OK(mcpwm_carrier_set_duty_cycle(unit, timer, duty)); // carrier duty
    judge_count_value(500, 50000/5.6);

    // with invert
    TEST_ESP_OK(mcpwm_carrier_output_invert(unit, timer, invert_or_not));
    vTaskDelay(2000 / portTICK_RATE_MS);
}