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
typedef  int /*<<< orphan*/  mcpwm_fault_signal_t ;
typedef  int mcpwm_fault_input_level_t ;
typedef  int /*<<< orphan*/  mcpwm_action_on_pwmxb_t ;
typedef  int /*<<< orphan*/  mcpwm_action_on_pwmxa_t ;
struct TYPE_3__ {int pin_bit_mask; int /*<<< orphan*/  mode; int /*<<< orphan*/  intr_type; } ;
typedef  TYPE_1__ gpio_config_t ;

/* Variables and functions */
 int FAULT_SIG_NUM ; 
 int /*<<< orphan*/  GPIO_FAULT_IN ; 
 int /*<<< orphan*/  GPIO_INTR_DISABLE ; 
 int /*<<< orphan*/  GPIO_MODE_OUTPUT ; 
 int /*<<< orphan*/  GPIO_PWMA_PCNT_INPUT ; 
 int /*<<< orphan*/  GPIO_PWMB_PCNT_INPUT ; 
 int /*<<< orphan*/  PCNT_CTRL_FLOATING_IO1 ; 
 int /*<<< orphan*/  PCNT_CTRL_FLOATING_IO2 ; 
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_action_level (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gpio_config (TYPE_1__*) ; 
 int /*<<< orphan*/  gpio_set_level (int,int) ; 
 int /*<<< orphan*/  mcpwm_basic_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_fault_deinit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_fault_init (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_fault_set_cyc_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_gpio_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcnt_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

__attribute__((used)) static void cycle_fault_test(mcpwm_unit_t unit, mcpwm_io_signals_t mcpwm_a, mcpwm_io_signals_t mcpwm_b, mcpwm_timer_t timer,
        mcpwm_fault_signal_t fault_sig, mcpwm_fault_input_level_t input_sig, mcpwm_io_signals_t fault_io,
        mcpwm_action_on_pwmxa_t action_a, mcpwm_action_on_pwmxb_t action_b)
{
    gpio_config_t gp;
    gp.intr_type = GPIO_INTR_DISABLE;
    gp.mode = GPIO_MODE_OUTPUT;
    gp.pin_bit_mask = (1 << FAULT_SIG_NUM);
    gpio_config(&gp); // gpio configure should be more previous than mcpwm configuration
    gpio_set_level(FAULT_SIG_NUM, !input_sig);

    pcnt_init(GPIO_PWMA_PCNT_INPUT, PCNT_CTRL_FLOATING_IO1);
    pcnt_init(GPIO_PWMB_PCNT_INPUT, PCNT_CTRL_FLOATING_IO2);

    mcpwm_basic_config(unit, mcpwm_a, mcpwm_b, timer);
    mcpwm_gpio_init(unit, fault_io, GPIO_FAULT_IN);

    // cycle mode, it can be triggered more than once
    printf("cyc test:\n");
    gpio_set_level(FAULT_SIG_NUM, !input_sig);
    TEST_ESP_OK(mcpwm_fault_init(unit, input_sig, fault_sig));
    TEST_ESP_OK(mcpwm_fault_set_cyc_mode(unit, timer, fault_sig, action_a, action_b));
    vTaskDelay(1000 / portTICK_RATE_MS);
    gpio_set_level(FAULT_SIG_NUM, input_sig); // trigger the fault event
    vTaskDelay(1000 / portTICK_RATE_MS);
    get_action_level(input_sig, action_a, action_b, 1000, 5);
    TEST_ESP_OK(mcpwm_fault_deinit(unit, fault_sig));
}