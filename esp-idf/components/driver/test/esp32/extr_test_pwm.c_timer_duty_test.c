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
 int INITIAL_DUTY ; 
 int /*<<< orphan*/  MCPWM_DUTY_MODE_0 ; 
 int /*<<< orphan*/  MCPWM_OPR_A ; 
 int /*<<< orphan*/  MCPWM_OPR_B ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_INT (double,int) ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_basic_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 double mcpwm_get_duty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_set_duty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  mcpwm_set_duty_in_us (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mcpwm_set_duty_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  printf (char*,double) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void timer_duty_test(mcpwm_unit_t unit, mcpwm_io_signals_t mcpwm_a, mcpwm_io_signals_t mcpwm_b, mcpwm_timer_t timer)
{
    mcpwm_basic_config(unit, mcpwm_a, mcpwm_b, timer);
    vTaskDelay(1000 / portTICK_RATE_MS); // stay this status for a while so that can view its waveform by logic anylyzer

    TEST_ESP_OK(mcpwm_set_duty(unit, timer, MCPWM_OPR_A, (INITIAL_DUTY * 1)));
    TEST_ESP_OK(mcpwm_set_duty(unit, timer, MCPWM_OPR_B, (INITIAL_DUTY * 2)));

    TEST_ASSERT_EQUAL_INT(mcpwm_get_duty(unit, timer, MCPWM_OPR_A), INITIAL_DUTY * 1);
    TEST_ASSERT_EQUAL_INT(mcpwm_get_duty(unit, timer, MCPWM_OPR_B), INITIAL_DUTY * 2);
    vTaskDelay(1000 / portTICK_RATE_MS);  // stay this status for a while so that can view its waveform by logic anylyzer

    mcpwm_set_duty(unit, timer, MCPWM_OPR_A, 55.5f);
    mcpwm_set_duty_type(unit, timer, MCPWM_OPR_A, MCPWM_DUTY_MODE_0);
    printf("mcpwm check = %f\n", mcpwm_get_duty(unit, timer, MCPWM_OPR_A));

    mcpwm_set_duty_in_us(unit, timer, MCPWM_OPR_B, 500);
    printf("mcpwm check = %f\n", mcpwm_get_duty(unit, timer, MCPWM_OPR_B));
    vTaskDelay(1000 / portTICK_RATE_MS);  // stay this status for a while so that can view its waveform by logic anylyzer
}