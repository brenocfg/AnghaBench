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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  mcpwm_unit_t ;
typedef  int /*<<< orphan*/  mcpwm_timer_t ;
typedef  int /*<<< orphan*/  mcpwm_io_signals_t ;
typedef  int /*<<< orphan*/  mcpwm_carrier_out_ivt_t ;
typedef  int /*<<< orphan*/  mcpwm_carrier_os_t ;
struct TYPE_3__ {int carrier_period; int carrier_duty; int pulse_width_in_os; int /*<<< orphan*/  carrier_ivt_mode; int /*<<< orphan*/  carrier_os_mode; } ;
typedef  TYPE_1__ mcpwm_carrier_config_t ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ESP_OK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  judge_count_value (int,int) ; 
 int /*<<< orphan*/  mcpwm_basic_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_carrier_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcpwm_carrier_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void carrier_with_configuration_test(mcpwm_unit_t unit, mcpwm_io_signals_t mcpwm_a, mcpwm_io_signals_t mcpwm_b, mcpwm_timer_t timer,
        mcpwm_carrier_os_t oneshot_or_not, mcpwm_carrier_out_ivt_t invert_or_not, uint8_t period, uint8_t duty, uint8_t os_width)
{
    mcpwm_basic_config(unit, mcpwm_a, mcpwm_b, timer);

    mcpwm_carrier_config_t chop_config;
    chop_config.carrier_period = period;         //carrier period = (period + 1)*800ns
    chop_config.carrier_duty = duty;           // carrier duty cycle, carrier_duty should be less then 8(increment every 12.5%).  carrier duty = (3)*12.5%
    chop_config.carrier_os_mode = oneshot_or_not; //If one shot mode is enabled then set pulse width, if disabled no need to set pulse width
    chop_config.pulse_width_in_os = os_width;      //pulse width of first pulse in one shot mode = (carrier period)*(pulse_width_in_os + 1), should be less then 16.first pulse width = (3 + 1)*carrier_period
    chop_config.carrier_ivt_mode = invert_or_not; //output signal inversion enable
    mcpwm_carrier_init(unit, timer, &chop_config);

    if(!oneshot_or_not) {
        // the pwm frequency is 1000
        // the carrrier duration in one second is 500ms
        // the carrier wave count is: 500ms/carrier_period = 500ms/(period + 1)*800ns
        //                                                 = 62500/(period + 1)
        judge_count_value(500, 62500/(period + 1));
    } else {
        judge_count_value(500, 40000/((period + 1)));  // (500-500*0.125*3)/((period + 1)*800)
    }

    TEST_ESP_OK(mcpwm_carrier_disable(unit, timer));
    judge_count_value(2, 1000);
}