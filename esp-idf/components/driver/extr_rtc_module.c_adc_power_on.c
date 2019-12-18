#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int force_xpd_sar; } ;
struct TYPE_4__ {int force_xpd_sar; } ;
struct TYPE_6__ {TYPE_2__ sar_power_xpd_sar; TYPE_1__ sar_meas_wait2; } ;

/* Variables and functions */
 TYPE_3__ SENS ; 
 void* SENS_FORCE_XPD_SAR_FSM ; 
 void* SENS_FORCE_XPD_SAR_PU ; 
 int SENS_FORCE_XPD_SAR_SW_M ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_spinlock ; 

void adc_power_on(void)
{
    portENTER_CRITICAL(&rtc_spinlock);
#if CONFIG_IDF_TARGET_ESP32
    //The power FSM controlled mode saves more power, while the ADC noise may get increased.
#ifndef CONFIG_ADC_FORCE_XPD_FSM
    //Set the power always on to increase precision.
    SENS.sar_meas_wait2.force_xpd_sar = SENS_FORCE_XPD_SAR_PU;
#else
    //Use the FSM to turn off the power while not used to save power.
    if (SENS.sar_meas_wait2.force_xpd_sar & SENS_FORCE_XPD_SAR_SW_M) {
        SENS.sar_meas_wait2.force_xpd_sar = SENS_FORCE_XPD_SAR_PU;
    } else {
        SENS.sar_meas_wait2.force_xpd_sar = SENS_FORCE_XPD_SAR_FSM;
    }
#endif
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    //The power FSM controlled mode saves more power, while the ADC noise may get increased.
#ifndef CONFIG_ADC_FORCE_XPD_FSM
    //Set the power always on to increase precision.
    SENS.sar_power_xpd_sar.force_xpd_sar = SENS_FORCE_XPD_SAR_PU;
#else    
    //Use the FSM to turn off the power while not used to save power.
    if (SENS.sar_power_xpd_sar.force_xpd_sar & SENS_FORCE_XPD_SAR_SW_M) {
        SENS.sar_power_xpd_sar.force_xpd_sar = SENS_FORCE_XPD_SAR_PU;
    } else {
        SENS.sar_power_xpd_sar.force_xpd_sar = SENS_FORCE_XPD_SAR_FSM;
    }
#endif
#endif
    portEXIT_CRITICAL(&rtc_spinlock);
}