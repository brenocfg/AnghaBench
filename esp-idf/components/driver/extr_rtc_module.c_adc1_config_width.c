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
typedef  scalar_t__ adc_bits_width_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_UNIT_1 ; 
 scalar_t__ ADC_WIDTH_MAX ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  RTC_MODULE_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adc_set_data_inv (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  adc_set_data_width (int /*<<< orphan*/ ,scalar_t__) ; 

esp_err_t adc1_config_width(adc_bits_width_t width_bit)
{
    RTC_MODULE_CHECK(width_bit < ADC_WIDTH_MAX, "ADC bit width error", ESP_ERR_INVALID_ARG);
    adc_set_data_width(ADC_UNIT_1, width_bit);
    adc_set_data_inv(ADC_UNIT_1, true);
    return ESP_OK;
}