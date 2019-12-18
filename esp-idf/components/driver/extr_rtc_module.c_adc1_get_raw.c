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
typedef  int uint16_t ;
typedef  scalar_t__ adc1_channel_t ;

/* Variables and functions */
 scalar_t__ ADC1_CHANNEL_MAX ; 
 int /*<<< orphan*/  ADC_CTRL_RTC ; 
 int /*<<< orphan*/  ADC_UNIT_1 ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  RTC_MODULE_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adc1_adc_mode_acquire () ; 
 int /*<<< orphan*/  adc1_fsm_disable () ; 
 int /*<<< orphan*/  adc1_hall_enable (int) ; 
 int /*<<< orphan*/  adc1_lock_release () ; 
 int adc_convert (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  adc_power_on () ; 
 int /*<<< orphan*/  adc_set_controller (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_spinlock ; 

int adc1_get_raw(adc1_channel_t channel)
{
    uint16_t adc_value;
    RTC_MODULE_CHECK(channel < ADC1_CHANNEL_MAX, "ADC Channel Err", ESP_ERR_INVALID_ARG);
    adc1_adc_mode_acquire();
    adc_power_on();

    portENTER_CRITICAL(&rtc_spinlock);
    //disable other peripherals
    adc1_hall_enable(false);
    adc1_fsm_disable(); //currently the LNA is not open, close it by default
    //set controller
    adc_set_controller( ADC_UNIT_1, ADC_CTRL_RTC );
    //start conversion
    adc_value = adc_convert( ADC_UNIT_1, channel );
    portEXIT_CRITICAL(&rtc_spinlock);
    adc1_lock_release();
    return adc_value;
}