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
typedef  int adc_unit_t ;
typedef  int adc_channel_t ;
typedef  scalar_t__ adc_atten_t ;
typedef  scalar_t__ adc1_channel_t ;

/* Variables and functions */
 scalar_t__ ADC1_CHANNEL_MAX ; 
 scalar_t__ ADC_ATTEN_MAX ; 
 int /*<<< orphan*/  ADC_CHECK_UNIT (int) ; 
 int ADC_UNIT_1 ; 
 int ADC_UNIT_2 ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  RTC_MODULE_CHECK (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SENS_SAR1_ATTEN_VAL_MASK ; 
 int /*<<< orphan*/  SENS_SAR2_ATTEN_VAL_MASK ; 
 int /*<<< orphan*/  SENS_SAR_ATTEN1_REG ; 
 int /*<<< orphan*/  SENS_SAR_ATTEN2_REG ; 
 int /*<<< orphan*/  SET_PERI_REG_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_spinlock ; 

__attribute__((used)) static esp_err_t adc_set_atten(adc_unit_t adc_unit, adc_channel_t channel, adc_atten_t atten)
{
    ADC_CHECK_UNIT(adc_unit);
    if (adc_unit & ADC_UNIT_1) {
        RTC_MODULE_CHECK((adc1_channel_t)channel < ADC1_CHANNEL_MAX, "ADC Channel Err", ESP_ERR_INVALID_ARG);
    }
    RTC_MODULE_CHECK(atten < ADC_ATTEN_MAX, "ADC Atten Err", ESP_ERR_INVALID_ARG);

    portENTER_CRITICAL(&rtc_spinlock);
    if (adc_unit & ADC_UNIT_1) {
        //SAR1_atten
        SET_PERI_REG_BITS(SENS_SAR_ATTEN1_REG, SENS_SAR1_ATTEN_VAL_MASK, atten, (channel * 2));
    }
    if (adc_unit & ADC_UNIT_2) {
        //SAR2_atten
        SET_PERI_REG_BITS(SENS_SAR_ATTEN2_REG, SENS_SAR2_ATTEN_VAL_MASK, atten, (channel * 2));
    }
    portEXIT_CRITICAL(&rtc_spinlock);
    return ESP_OK;
}