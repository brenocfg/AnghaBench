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
typedef  int /*<<< orphan*/  gpio_num_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int adc_unit_t ;
typedef  scalar_t__ adc_channel_t ;
typedef  scalar_t__ adc1_channel_t ;

/* Variables and functions */
 scalar_t__ ADC1_CHANNEL_MAX ; 
 int /*<<< orphan*/  ADC1_CHECK_FUNCTION_RET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADC_CHECK_UNIT (int) ; 
 int ADC_UNIT_1 ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  GPIO_FLOATING ; 
 int /*<<< orphan*/  RTC_MODULE_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adc1_pad_get_io_num (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_set_pull_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_gpio_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_gpio_input_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_gpio_output_disable (int /*<<< orphan*/ ) ; 

esp_err_t adc_gpio_init(adc_unit_t adc_unit, adc_channel_t channel)
{
    ADC_CHECK_UNIT(adc_unit);
    gpio_num_t gpio_num = 0;
    if (adc_unit & ADC_UNIT_1) {
        RTC_MODULE_CHECK((adc1_channel_t) channel < ADC1_CHANNEL_MAX, "ADC1 channel error", ESP_ERR_INVALID_ARG);
        ADC1_CHECK_FUNCTION_RET(adc1_pad_get_io_num((adc1_channel_t) channel, &gpio_num));
        ADC1_CHECK_FUNCTION_RET(rtc_gpio_init(gpio_num));
        ADC1_CHECK_FUNCTION_RET(rtc_gpio_output_disable(gpio_num));
        ADC1_CHECK_FUNCTION_RET(rtc_gpio_input_disable(gpio_num));
        ADC1_CHECK_FUNCTION_RET(gpio_set_pull_mode(gpio_num, GPIO_FLOATING));
    }
    return ESP_OK;
}