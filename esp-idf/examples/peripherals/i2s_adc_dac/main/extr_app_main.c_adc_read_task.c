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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  esp_adc_cal_characteristics_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADC1_TEST_CHANNEL ; 
 int /*<<< orphan*/  ADC_ATTEN_11db ; 
 int /*<<< orphan*/  ADC_ATTEN_DB_11 ; 
 int /*<<< orphan*/  ADC_UNIT_1 ; 
 int /*<<< orphan*/  ADC_WIDTH_12Bit ; 
 int /*<<< orphan*/  ADC_WIDTH_BIT_12 ; 
 int /*<<< orphan*/  ESP_LOGI (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  V_REF ; 
 int /*<<< orphan*/  adc1_config_channel_atten (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adc1_config_width (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esp_adc_cal_characterize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esp_adc_cal_get_voltage (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  vTaskDelay (int) ; 

void adc_read_task(void* arg)
{
    adc1_config_width(ADC_WIDTH_12Bit);
    adc1_config_channel_atten(ADC1_TEST_CHANNEL, ADC_ATTEN_11db);
    esp_adc_cal_characteristics_t characteristics;
    esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, V_REF, &characteristics);
    while(1) {
        uint32_t voltage;
        esp_adc_cal_get_voltage(ADC1_TEST_CHANNEL, &characteristics, &voltage);
        ESP_LOGI(TAG, "%d mV", voltage);
        vTaskDelay(200 / portTICK_RATE_MS);
    }
}