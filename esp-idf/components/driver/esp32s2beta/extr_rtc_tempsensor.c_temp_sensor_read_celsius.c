#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_5__ {float offset; float range_min; float range_max; } ;
typedef  TYPE_1__ tsens_dac_offset_t ;
struct TYPE_6__ {size_t dac_offset; } ;
typedef  TYPE_2__ temp_sensor_config_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_ERR_INVALID_ARG ; 
 scalar_t__ ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_LOGW (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  TAG ; 
 float TSENS_ADC_FACTOR ; 
 int /*<<< orphan*/  TSENS_CHECK (int,scalar_t__) ; 
 float TSENS_DAC_FACTOR ; 
 float TSENS_SYS_OFFSET ; 
 TYPE_1__* dac_offset ; 
 scalar_t__ temp_sensor_get_config (TYPE_2__*) ; 
 scalar_t__ temp_sensor_read_raw (scalar_t__*) ; 

esp_err_t temp_sensor_read_celsius(float *celsius)
{
    TSENS_CHECK(celsius != NULL, ESP_ERR_INVALID_ARG);
    temp_sensor_config_t tsens;
    uint32_t tsens_out = 0;
    esp_err_t ret = temp_sensor_get_config(&tsens);
    if (ret == ESP_OK) {
        ret = temp_sensor_read_raw(&tsens_out);
        TSENS_CHECK(ret == ESP_OK, ret);
        const tsens_dac_offset_t *dac = &dac_offset[tsens.dac_offset];
        *celsius = (TSENS_ADC_FACTOR * (float)tsens_out - TSENS_DAC_FACTOR * dac->offset - TSENS_SYS_OFFSET);
        if (*celsius < dac->range_min || *celsius > dac->range_max) {
            ESP_LOGW(TAG, "Exceeding the temperature range!");
            ret = ESP_ERR_INVALID_STATE;
        }
    }
    return ret;
}