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
 int /*<<< orphan*/  ADC_CTRL_ULP ; 
 int /*<<< orphan*/  ADC_UNIT_1 ; 
 int /*<<< orphan*/  adc1_fsm_disable () ; 
 int /*<<< orphan*/  adc1_hall_enable (int) ; 
 int /*<<< orphan*/  adc_power_on () ; 
 int /*<<< orphan*/  adc_set_controller (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_spinlock ; 

void adc1_ulp_enable(void)
{
    adc_power_on();

    portENTER_CRITICAL(&rtc_spinlock);
    adc_set_controller( ADC_UNIT_1, ADC_CTRL_ULP );
    // since most users do not need LNA and HALL with uLP, we disable them here
    // open them in the uLP if needed.
    adc1_fsm_disable();
    adc1_hall_enable(false);
    portEXIT_CRITICAL(&rtc_spinlock);
}