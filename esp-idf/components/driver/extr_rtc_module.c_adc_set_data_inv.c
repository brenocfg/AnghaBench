#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  int adc_unit_t ;
struct TYPE_9__ {int sar2_data_inv; } ;
struct TYPE_8__ {int sar1_data_inv; } ;
struct TYPE_7__ {int sar2_data_inv; } ;
struct TYPE_6__ {int sar1_data_inv; } ;
struct TYPE_10__ {TYPE_4__ sar_reader2_ctrl; TYPE_3__ sar_reader1_ctrl; TYPE_2__ sar_read_ctrl2; TYPE_1__ sar_read_ctrl; } ;

/* Variables and functions */
 int ADC_UNIT_1 ; 
 int ADC_UNIT_2 ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_5__ SENS ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_spinlock ; 

esp_err_t adc_set_data_inv(adc_unit_t adc_unit, bool inv_en)
{
    portENTER_CRITICAL(&rtc_spinlock);
#if CONFIG_IDF_TARGET_ESP32
    if (adc_unit & ADC_UNIT_1) {
        // Enable ADC data invert
        SENS.sar_read_ctrl.sar1_data_inv = inv_en;
    }
    if (adc_unit & ADC_UNIT_2) {
        // Enable ADC data invert
        SENS.sar_read_ctrl2.sar2_data_inv = inv_en;
    }
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    if (adc_unit & ADC_UNIT_1) {
        // Enable ADC data invert
        SENS.sar_reader1_ctrl.sar1_data_inv = inv_en;
    }
    if (adc_unit & ADC_UNIT_2) {
        // Enable ADC data invert
        SENS.sar_reader2_ctrl.sar2_data_inv = inv_en;
    }
#endif
    portEXIT_CRITICAL(&rtc_spinlock);
    return ESP_OK;
}