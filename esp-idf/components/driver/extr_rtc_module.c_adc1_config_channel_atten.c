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
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  scalar_t__ adc_atten_t ;
typedef  scalar_t__ adc1_channel_t ;

/* Variables and functions */
 scalar_t__ ADC1_CHANNEL_MAX ; 
 scalar_t__ ADC_ATTEN_MAX ; 
 int /*<<< orphan*/  ADC_UNIT_1 ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  RTC_MODULE_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adc_gpio_init (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  adc_set_atten (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

esp_err_t adc1_config_channel_atten(adc1_channel_t channel, adc_atten_t atten)
{
    RTC_MODULE_CHECK(channel < ADC1_CHANNEL_MAX, "ADC Channel Err", ESP_ERR_INVALID_ARG);
    RTC_MODULE_CHECK(atten < ADC_ATTEN_MAX, "ADC Atten Err", ESP_ERR_INVALID_ARG);
    adc_gpio_init(ADC_UNIT_1, channel);
    adc_set_atten(ADC_UNIT_1, channel, atten);
    return ESP_OK;
}