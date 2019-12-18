#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int hall_phase; } ;
struct TYPE_4__ {TYPE_1__ hall_sens; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC1_CHANNEL_0 ; 
 int /*<<< orphan*/  ADC1_CHANNEL_3 ; 
 int /*<<< orphan*/  ADC_CTRL_RTC ; 
 int /*<<< orphan*/  ADC_UNIT_1 ; 
 TYPE_2__ RTCIO ; 
 int /*<<< orphan*/  adc1_fsm_disable () ; 
 int /*<<< orphan*/  adc1_hall_enable (int) ; 
 int adc_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adc_power_on () ; 
 int /*<<< orphan*/  adc_set_controller (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_spinlock ; 

__attribute__((used)) static int hall_sensor_get_value(void)    //hall sensor without LNA
{
    int hall_value = 0;

    adc_power_on();

#if CONFIG_IDF_TARGET_ESP32
    int Sens_Vp0;
    int Sens_Vn0;
    int Sens_Vp1;
    int Sens_Vn1;
    portENTER_CRITICAL(&rtc_spinlock);
    //disable other peripherals
    adc1_fsm_disable();//currently the LNA is not open, close it by default
    adc1_hall_enable(true);
    // set controller
    adc_set_controller( ADC_UNIT_1, ADC_CTRL_RTC );
    // convert for 4 times with different phase and outputs
    RTCIO.hall_sens.hall_phase = 0;      // hall phase
    Sens_Vp0 = adc_convert( ADC_UNIT_1, ADC1_CHANNEL_0 );
    Sens_Vn0 = adc_convert( ADC_UNIT_1, ADC1_CHANNEL_3 );
    RTCIO.hall_sens.hall_phase = 1;
    Sens_Vp1 = adc_convert( ADC_UNIT_1, ADC1_CHANNEL_0 );
    Sens_Vn1 = adc_convert( ADC_UNIT_1, ADC1_CHANNEL_3 );
    portEXIT_CRITICAL(&rtc_spinlock);
    hall_value = (Sens_Vp1 - Sens_Vp0) - (Sens_Vn1 - Sens_Vn0);
#endif
    return hall_value;
}