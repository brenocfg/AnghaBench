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
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int /*<<< orphan*/  adc_bits_width_t ;
typedef  scalar_t__ adc2_channel_t ;

/* Variables and functions */
 scalar_t__ ADC2_CHANNEL_MAX ; 
 int /*<<< orphan*/  ADC_CTRL_RTC ; 
 int /*<<< orphan*/  ADC_UNIT_2 ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_TIMEOUT ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  RTC_MODULE_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _lock_release (int /*<<< orphan*/ *) ; 
 int _lock_try_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  adc2_config_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adc2_dac_disable (scalar_t__) ; 
 int /*<<< orphan*/  adc2_spinlock ; 
 int /*<<< orphan*/  adc2_wifi_lock ; 
 scalar_t__ adc_convert (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  adc_power_on () ; 
 int /*<<< orphan*/  adc_set_controller (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 

esp_err_t adc2_get_raw(adc2_channel_t channel, adc_bits_width_t width_bit, int* raw_out)
{
    uint16_t adc_value = 0;
    RTC_MODULE_CHECK(channel < ADC2_CHANNEL_MAX, "ADC Channel Err", ESP_ERR_INVALID_ARG);

    //in critical section with whole rtc module
    adc_power_on();

    //avoid collision with other tasks
    portENTER_CRITICAL(&adc2_spinlock);
    //lazy initialization
    //try the lock, return if failed (wifi using).
    if ( _lock_try_acquire( &adc2_wifi_lock ) == -1 ) {
        portEXIT_CRITICAL( &adc2_spinlock );
        return ESP_ERR_TIMEOUT;
    }

    //disable other peripherals
#ifdef CONFIG_ADC_DISABLE_DAC
    adc2_dac_disable( channel );
#endif
    // set controller
    // in critical section with whole rtc module
    // because the PWDET use the same registers, place it here.
    adc2_config_width( width_bit );
    adc_set_controller( ADC_UNIT_2, ADC_CTRL_RTC );
    //start converting
    adc_value = adc_convert( ADC_UNIT_2, channel );
    _lock_release( &adc2_wifi_lock );
    portEXIT_CRITICAL(&adc2_spinlock);

    *raw_out = (int)adc_value;
    return ESP_OK;
}