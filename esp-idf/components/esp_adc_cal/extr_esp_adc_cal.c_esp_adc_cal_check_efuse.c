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
typedef  scalar_t__ esp_adc_cal_value_t ;

/* Variables and functions */
 scalar_t__ ESP_ADC_CAL_VAL_EFUSE_TP ; 
 scalar_t__ ESP_ADC_CAL_VAL_EFUSE_VREF ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_ERR_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ESP_OK ; 
 scalar_t__ check_efuse_tp () ; 
 scalar_t__ check_efuse_vref () ; 

esp_err_t esp_adc_cal_check_efuse(esp_adc_cal_value_t source)
{
    if (source == ESP_ADC_CAL_VAL_EFUSE_TP) {
        return (check_efuse_tp()) ? ESP_OK : ESP_ERR_NOT_SUPPORTED;
    } else if (source == ESP_ADC_CAL_VAL_EFUSE_VREF) {
        return (check_efuse_vref()) ? ESP_OK : ESP_ERR_NOT_SUPPORTED;
    } else {
        return ESP_ERR_INVALID_ARG;
    }
}