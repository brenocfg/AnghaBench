#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
typedef  scalar_t__ adc_unit_t ;
struct TYPE_11__ {int sar2_en_pad; int meas2_start_sar; scalar_t__ meas2_done_sar; int meas2_data_sar; } ;
struct TYPE_10__ {int sar1_en_pad; int meas1_start_sar; scalar_t__ meas1_done_sar; int meas1_data_sar; } ;
struct TYPE_9__ {scalar_t__ meas_status; } ;
struct TYPE_8__ {int sar2_en_pad; int meas2_start_sar; scalar_t__ meas2_done_sar; int meas2_data_sar; } ;
struct TYPE_7__ {int sar1_en_pad; int meas1_start_sar; scalar_t__ meas1_done_sar; int meas1_data_sar; } ;
struct TYPE_12__ {TYPE_5__ sar_meas2_ctrl2; TYPE_4__ sar_meas1_ctrl2; TYPE_3__ sar_slave_addr1; TYPE_2__ sar_meas_start2; TYPE_1__ sar_meas_start1; } ;

/* Variables and functions */
 scalar_t__ ADC_UNIT_1 ; 
 scalar_t__ ADC_UNIT_2 ; 
 int ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 TYPE_6__ SENS ; 
 int /*<<< orphan*/  TAG ; 

__attribute__((used)) static int adc_convert( adc_unit_t unit, int channel)
{
    uint16_t adc_value = 0;
#if CONFIG_IDF_TARGET_ESP32
    if ( unit == ADC_UNIT_1 ) {
        SENS.sar_meas_start1.sar1_en_pad = (1 << channel); //only one channel is selected.
        while (SENS.sar_slave_addr1.meas_status != 0);
        SENS.sar_meas_start1.meas1_start_sar = 0;
        SENS.sar_meas_start1.meas1_start_sar = 1;
        while (SENS.sar_meas_start1.meas1_done_sar == 0);
        adc_value = SENS.sar_meas_start1.meas1_data_sar;
    } else if ( unit == ADC_UNIT_2 ) {
        SENS.sar_meas_start2.sar2_en_pad = (1 << channel); //only one channel is selected.

        SENS.sar_meas_start2.meas2_start_sar = 0; //start force 0
        SENS.sar_meas_start2.meas2_start_sar = 1; //start force 1
        while (SENS.sar_meas_start2.meas2_done_sar == 0) {}; //read done
        adc_value = SENS.sar_meas_start2.meas2_data_sar;
    } else {
        ESP_LOGE(TAG, "invalid adc unit");
        return ESP_ERR_INVALID_ARG;
    }
#elif CONFIG_IDF_TARGET_ESP32S2BETA
     if ( unit == ADC_UNIT_1 ) {
        SENS.sar_meas1_ctrl2.sar1_en_pad = (1 << channel); //only one channel is selected.
        while (SENS.sar_slave_addr1.meas_status != 0);
        SENS.sar_meas1_ctrl2.meas1_start_sar = 0;
        SENS.sar_meas1_ctrl2.meas1_start_sar = 1;
        while (SENS.sar_meas1_ctrl2.meas1_done_sar == 0);
        adc_value = SENS.sar_meas1_ctrl2.meas1_data_sar;
    } else if ( unit == ADC_UNIT_2 ) {
        SENS.sar_meas2_ctrl2.sar2_en_pad = (1 << channel); //only one channel is selected.    
        
        SENS.sar_meas2_ctrl2.meas2_start_sar = 0; //start force 0
        SENS.sar_meas2_ctrl2.meas2_start_sar = 1; //start force 1
        while (SENS.sar_meas2_ctrl2.meas2_done_sar == 0) {}; //read done
        adc_value = SENS.sar_meas2_ctrl2.meas2_data_sar;    
    } else {
        ESP_LOGE(TAG, "invalid adc unit");
        return ESP_ERR_INVALID_ARG;
    }
#endif
    return adc_value;
}