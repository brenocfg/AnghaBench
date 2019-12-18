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
typedef  int /*<<< orphan*/  mcpwm_deadtime_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  MCPWM_ACTIVE_HIGH_COMPLIMENT_MODE ; 
 int /*<<< orphan*/  MCPWM_ACTIVE_HIGH_MODE ; 
 int /*<<< orphan*/  MCPWM_ACTIVE_LOW_COMPLIMENT_MODE ; 
 int /*<<< orphan*/  MCPWM_ACTIVE_LOW_MODE ; 
 int /*<<< orphan*/  MCPWM_ACTIVE_RED_FED_FROM_PWMXA ; 
 int /*<<< orphan*/  MCPWM_ACTIVE_RED_FED_FROM_PWMXB ; 
 int /*<<< orphan*/  MCPWM_BYPASS_FED ; 
 int /*<<< orphan*/  MCPWM_BYPASS_RED ; 
 int /*<<< orphan*/  mcpwm_basic_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_deadtime_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_deadtime_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void deadtime_test(mcpwm_unit_t unit, mcpwm_io_signals_t mcpwm_a, mcpwm_io_signals_t mcpwm_b, mcpwm_timer_t timer)
{
    mcpwm_basic_config(unit, mcpwm_a, mcpwm_b, timer);
    mcpwm_deadtime_type_t deadtime_type[8] = {MCPWM_BYPASS_RED, MCPWM_BYPASS_FED, MCPWM_ACTIVE_HIGH_MODE,
            MCPWM_ACTIVE_LOW_MODE, MCPWM_ACTIVE_HIGH_COMPLIMENT_MODE, MCPWM_ACTIVE_LOW_COMPLIMENT_MODE,
            MCPWM_ACTIVE_RED_FED_FROM_PWMXA, MCPWM_ACTIVE_RED_FED_FROM_PWMXB};

    for(int i=0; i<8; i++) {
        mcpwm_deadtime_enable(unit, timer, deadtime_type[i], 1000, 1000);
        vTaskDelay(1000 / portTICK_RATE_MS);
        mcpwm_deadtime_disable(unit, timer);
    }
}