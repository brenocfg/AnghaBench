#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mcpwm_unit_t ;
typedef  int /*<<< orphan*/  mcpwm_timer_t ;
typedef  int /*<<< orphan*/  mcpwm_sync_signal_t ;
typedef  int /*<<< orphan*/  mcpwm_io_signals_t ;
struct TYPE_5__ {int frequency; double cmpr_a; double cmpr_b; int /*<<< orphan*/  duty_mode; int /*<<< orphan*/  counter_mode; } ;
typedef  TYPE_1__ mcpwm_config_t ;
struct TYPE_6__ {int pin_bit_mask; int /*<<< orphan*/  mode; int /*<<< orphan*/  intr_type; } ;
typedef  TYPE_2__ gpio_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_INTR_DISABLE ; 
 int /*<<< orphan*/  GPIO_MODE_OUTPUT ; 
 int /*<<< orphan*/  GPIO_PWMA_OUT ; 
 int /*<<< orphan*/  GPIO_PWMB_OUT ; 
 int /*<<< orphan*/  GPIO_SYNC_IN ; 
 int /*<<< orphan*/  MCPWM_DUTY_MODE_0 ; 
 int /*<<< orphan*/  MCPWM_UP_COUNTER ; 
 int SYN_SIG_NUM ; 
 int /*<<< orphan*/  gpio_config (TYPE_2__*) ; 
 int /*<<< orphan*/  gpio_pulldown_en (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_set_level (int,int) ; 
 int /*<<< orphan*/  mcpwm_gpio_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  mcpwm_sync_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_sync_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void sync_test(mcpwm_unit_t unit, mcpwm_io_signals_t mcpwm_a, mcpwm_io_signals_t mcpwm_b, mcpwm_timer_t timer,
        mcpwm_sync_signal_t sync_sig, mcpwm_io_signals_t sync_io)
{
    gpio_config_t gp;
    gp.intr_type = GPIO_INTR_DISABLE;
    gp.mode = GPIO_MODE_OUTPUT;
    gp.pin_bit_mask = (1 << SYN_SIG_NUM);
    gpio_config(&gp);
    gpio_set_level(SYN_SIG_NUM, 0);

    mcpwm_gpio_init(unit, mcpwm_a, GPIO_PWMA_OUT);
    mcpwm_gpio_init(unit, mcpwm_b, GPIO_PWMB_OUT);
    mcpwm_gpio_init(unit, sync_io, GPIO_SYNC_IN);
    mcpwm_config_t pwm_config = {
        .frequency = 1000,
        .cmpr_a = 50.0,  //duty cycle of PWMxA = 50.0%
        .cmpr_b = 50.0,  //duty cycle of PWMxb = 50.0%
        .counter_mode = MCPWM_UP_COUNTER,
        .duty_mode = MCPWM_DUTY_MODE_0,
    };
    mcpwm_init(unit, timer, &pwm_config);
    gpio_pulldown_en(GPIO_SYNC_IN);

    mcpwm_sync_enable(unit, timer, sync_sig, 200);
    gpio_set_level(SYN_SIG_NUM, 1);
    vTaskDelay(2000 / portTICK_RATE_MS);
    mcpwm_sync_disable(unit, timer);
    vTaskDelay(2000 / portTICK_RATE_MS);
}