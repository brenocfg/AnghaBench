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
typedef  void* adc_bits_width_t ;
struct TYPE_9__ {int sar2_data_inv; void* sar2_sample_bit; } ;
struct TYPE_8__ {int sar2_pwdet_cct; } ;
struct TYPE_7__ {void* sar2_bit_width; } ;
struct TYPE_11__ {int sar2_data_inv; void* sar2_sample_bit; } ;
struct TYPE_10__ {int sar2_pwdet_cct; void* sar2_bit_width; } ;
struct TYPE_12__ {TYPE_3__ sar_reader2_ctrl; TYPE_2__ sar_meas2_mux; TYPE_1__ sar_meas2_ctrl1; TYPE_5__ sar_read_ctrl2; TYPE_4__ sar_start_force; } ;

/* Variables and functions */
 TYPE_6__ SENS ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_spinlock ; 

__attribute__((used)) static inline void adc2_config_width(adc_bits_width_t width_bit)
{
    portENTER_CRITICAL(&rtc_spinlock);
#if CONFIG_IDF_TARGET_ESP32
    //sar_start_force shared with ADC1
    SENS.sar_start_force.sar2_bit_width = width_bit;
    //cct set to the same value with PHY
    SENS.sar_start_force.sar2_pwdet_cct = 4;
    portEXIT_CRITICAL(&rtc_spinlock);

    //Invert the adc value,the Output value is invert
    SENS.sar_read_ctrl2.sar2_data_inv = 1;
    //Set The adc sample width,invert adc value,must digital sar2_bit_width[1:0]=3
    SENS.sar_read_ctrl2.sar2_sample_bit = width_bit;
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    //sar_start_force shared with ADC1
    SENS.sar_meas2_ctrl1.sar2_bit_width = width_bit;
    //cct set to the same value with PHY
    SENS.sar_meas2_mux.sar2_pwdet_cct = 4;
    portEXIT_CRITICAL(&rtc_spinlock);
    //Invert the adc value,the Output value is invert
    SENS.sar_reader2_ctrl.sar2_data_inv = 1;
    //Set The adc sample width,invert adc value,must digital sar2_bit_width[1:0]=3
    SENS.sar_reader2_ctrl.sar2_sample_bit = width_bit;
#endif
}