#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ adc_unit_t ;
typedef  int adc_controller_t ;
struct TYPE_24__ {int xpd_hall_force; int hall_phase_force; } ;
struct TYPE_23__ {int meas1_start_force; int sar1_en_pad_force; } ;
struct TYPE_22__ {int sar1_dig_force; } ;
struct TYPE_21__ {int sar2_mux; } ;
struct TYPE_20__ {int sar2_dig_force; int sar2_pwdet_force; } ;
struct TYPE_19__ {int meas2_start_force; int sar2_en_pad_force; } ;
struct TYPE_18__ {int xpd_hall_force; int hall_phase_force; } ;
struct TYPE_17__ {int meas1_start_force; int sar1_en_pad_force; } ;
struct TYPE_16__ {int sar1_dig_force; } ;
struct TYPE_13__ {int meas2_start_force; int sar2_en_pad_force; } ;
struct TYPE_15__ {TYPE_10__ sar_meas2_ctrl2; TYPE_9__ sar_hall_ctrl; TYPE_8__ sar_meas1_ctrl2; TYPE_7__ sar_meas1_mux; TYPE_5__ sar_read_ctrl2; TYPE_4__ sar_meas_start2; TYPE_3__ sar_touch_ctrl1; TYPE_2__ sar_meas_start1; TYPE_1__ sar_read_ctrl; } ;
struct TYPE_14__ {TYPE_6__ saradc_ctrl; } ;

/* Variables and functions */
#define  ADC2_CTRL_PWDET 131 
#define  ADC_CTRL_DIG 130 
#define  ADC_CTRL_RTC 129 
#define  ADC_CTRL_ULP 128 
 scalar_t__ ADC_UNIT_1 ; 
 scalar_t__ ADC_UNIT_2 ; 
 int /*<<< orphan*/  ESP_LOGE (int /*<<< orphan*/ ,char*) ; 
 TYPE_12__ SENS ; 
 TYPE_11__ SYSCON ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void adc_set_controller(adc_unit_t unit, adc_controller_t ctrl )
{
#if CONFIG_IDF_TARGET_ESP32
    if ( unit == ADC_UNIT_1 ) {
        switch( ctrl ) {
            case ADC_CTRL_RTC:
                SENS.sar_read_ctrl.sar1_dig_force = false;      //RTC controller controls the ADC, not digital controller
                SENS.sar_meas_start1.meas1_start_force = true;  //RTC controller controls the ADC,not ulp coprocessor
                SENS.sar_meas_start1.sar1_en_pad_force = true;  //RTC controller controls the data port, not ulp coprocessor
                SENS.sar_touch_ctrl1.xpd_hall_force = true;     // RTC controller controls the hall sensor power,not ulp coprocessor
                SENS.sar_touch_ctrl1.hall_phase_force = true;   // RTC controller controls the hall sensor phase,not ulp coprocessor
                break;
            case ADC_CTRL_ULP:
                SENS.sar_read_ctrl.sar1_dig_force = false;
                SENS.sar_meas_start1.meas1_start_force = false;
                SENS.sar_meas_start1.sar1_en_pad_force = false;
                SENS.sar_touch_ctrl1.xpd_hall_force = false;
                SENS.sar_touch_ctrl1.hall_phase_force = false;
                break;
            case ADC_CTRL_DIG:
                SENS.sar_read_ctrl.sar1_dig_force = true;
                SENS.sar_meas_start1.meas1_start_force = true;
                SENS.sar_meas_start1.sar1_en_pad_force = true;
                SENS.sar_touch_ctrl1.xpd_hall_force = true;
                SENS.sar_touch_ctrl1.hall_phase_force = true;
                break;
            default:
                ESP_LOGE(TAG, "adc1 selects invalid controller");
                break;
        }
    } else if ( unit == ADC_UNIT_2) {
        switch( ctrl ) {
            case ADC_CTRL_RTC:
                SENS.sar_meas_start2.meas2_start_force = true;  //RTC controller controls the ADC,not ulp coprocessor
                SENS.sar_meas_start2.sar2_en_pad_force = true;  //RTC controller controls the data port, not ulp coprocessor
                SENS.sar_read_ctrl2.sar2_dig_force = false;     //RTC controller controls the ADC, not digital controller
                SENS.sar_read_ctrl2.sar2_pwdet_force = false;   //RTC controller controls the ADC, not PWDET
                SYSCON.saradc_ctrl.sar2_mux = true;             //RTC controller controls the ADC, not PWDET
                break;
            case ADC_CTRL_ULP:
                SENS.sar_meas_start2.meas2_start_force = false;
                SENS.sar_meas_start2.sar2_en_pad_force = false;
                SENS.sar_read_ctrl2.sar2_dig_force = false;
                SENS.sar_read_ctrl2.sar2_pwdet_force = false;
                SYSCON.saradc_ctrl.sar2_mux = true;
                break;
            case ADC_CTRL_DIG:
                SENS.sar_meas_start2.meas2_start_force = true;
                SENS.sar_meas_start2.sar2_en_pad_force = true;
                SENS.sar_read_ctrl2.sar2_dig_force = true;
                SENS.sar_read_ctrl2.sar2_pwdet_force = false;
                SYSCON.saradc_ctrl.sar2_mux = true;
                break;
            case ADC2_CTRL_PWDET:
                //currently only used by Wi-Fi
                SENS.sar_meas_start2.meas2_start_force = true;
                SENS.sar_meas_start2.sar2_en_pad_force = true;
                SENS.sar_read_ctrl2.sar2_dig_force = false;
                SENS.sar_read_ctrl2.sar2_pwdet_force = true;
                SYSCON.saradc_ctrl.sar2_mux = false;
                break;
            default:
                ESP_LOGE(TAG, "adc2 selects invalid controller");
                break;            
        }
    } else {
      ESP_LOGE(TAG, "invalid adc unit");
      assert(0);
    }
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    if ( unit == ADC_UNIT_1 ) {
        switch( ctrl ) {
            case ADC_CTRL_RTC:
                SENS.sar_meas1_mux.sar1_dig_force = false;      //RTC controller controls the ADC, not digital controller
                SENS.sar_meas1_ctrl2.meas1_start_force = true;  //RTC controller controls the ADC,not ulp coprocessor
                SENS.sar_meas1_ctrl2.sar1_en_pad_force = true;  //RTC controller controls the data port, not ulp coprocessor
                SENS.sar_hall_ctrl.xpd_hall_force = true;     // RTC controller controls the hall sensor power,not ulp coprocessor
                SENS.sar_hall_ctrl.hall_phase_force = true;   // RTC controller controls the hall sensor phase,not ulp coprocessor
                break;
            case ADC_CTRL_ULP:
                SENS.sar_meas1_mux.sar1_dig_force = false;
                SENS.sar_meas1_ctrl2.meas1_start_force = false;
                SENS.sar_meas1_ctrl2.sar1_en_pad_force = false;
                SENS.sar_hall_ctrl.xpd_hall_force = false;
                SENS.sar_hall_ctrl.hall_phase_force = false;
                break;
            case ADC_CTRL_DIG:
                SENS.sar_meas1_mux.sar1_dig_force = true;
                SENS.sar_meas1_ctrl2.meas1_start_force = true;
                SENS.sar_meas1_ctrl2.sar1_en_pad_force = true;
                SENS.sar_hall_ctrl.xpd_hall_force = true;
                SENS.sar_hall_ctrl.hall_phase_force = true;
                break;
            default:
                ESP_LOGE(TAG, "adc1 selects invalid controller");
                break;            
        }
    } else if ( unit == ADC_UNIT_2) {
        switch( ctrl ) {
            case ADC_CTRL_RTC:
                SENS.sar_meas2_ctrl2.meas2_start_force = true;  //RTC controller controls the ADC,not ulp coprocessor 
                SENS.sar_meas2_ctrl2.sar2_en_pad_force = true;  //RTC controller controls the data port, not ulp coprocessor
                break;
            case ADC_CTRL_ULP:
                SENS.sar_meas2_ctrl2.meas2_start_force = false;
                SENS.sar_meas2_ctrl2.sar2_en_pad_force = false;
                break;
            case ADC_CTRL_DIG:
                SENS.sar_meas2_ctrl2.meas2_start_force = true;
                SENS.sar_meas2_ctrl2.sar2_en_pad_force = true;
                break;
            case ADC2_CTRL_PWDET:
                //currently only used by Wi-Fi
                SENS.sar_meas2_ctrl2.meas2_start_force = true;
                SENS.sar_meas2_ctrl2.sar2_en_pad_force = true;
                break;
            default:
                ESP_LOGE(TAG, "adc2 selects invalid controller");
                break;            
        }
    } else {
      ESP_LOGE(TAG, "invalid adc unit");
      assert(0);
    }
#endif
}