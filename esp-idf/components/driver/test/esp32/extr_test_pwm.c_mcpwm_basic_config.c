#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mcpwm_unit_t ;
typedef  int /*<<< orphan*/  mcpwm_timer_t ;
typedef  int /*<<< orphan*/  mcpwm_io_signals_t ;
struct TYPE_3__ {int frequency; double cmpr_a; double cmpr_b; int /*<<< orphan*/  duty_mode; int /*<<< orphan*/  counter_mode; } ;
typedef  TYPE_1__ mcpwm_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_PWMA_OUT ; 
 int /*<<< orphan*/  GPIO_PWMB_OUT ; 
 int /*<<< orphan*/  MCPWM_DUTY_MODE_0 ; 
 int /*<<< orphan*/  MCPWM_UP_COUNTER ; 
 int /*<<< orphan*/  mcpwm_gpio_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void mcpwm_basic_config(mcpwm_unit_t unit, mcpwm_io_signals_t mcpwm_a, mcpwm_io_signals_t mcpwm_b, mcpwm_timer_t timer)
{
    mcpwm_gpio_init(unit, mcpwm_a, GPIO_PWMA_OUT);
    mcpwm_gpio_init(unit, mcpwm_b, GPIO_PWMB_OUT);
    mcpwm_config_t pwm_config = {
        .frequency = 1000,
        .cmpr_a = 50.0,  //duty cycle of PWMxA = 50.0%
        .cmpr_b = 50.0,  //duty cycle of PWMxb = 50.0%
        .counter_mode = MCPWM_UP_COUNTER,
        .duty_mode = MCPWM_DUTY_MODE_0,
    };
    mcpwm_init(unit, timer, &pwm_config);
}