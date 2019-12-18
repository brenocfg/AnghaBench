#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int sar_amp_wait3; } ;
struct TYPE_14__ {int sar_amp_wait1; int sar_amp_wait2; } ;
struct TYPE_13__ {scalar_t__ amp_short_ref_gnd_fsm; scalar_t__ amp_short_ref_fsm; scalar_t__ amp_rst_fb_fsm; } ;
struct TYPE_12__ {void* force_xpd_amp; } ;
struct TYPE_11__ {int sar_amp_wait3; void* force_xpd_amp; } ;
struct TYPE_10__ {int sar_amp_wait1; int sar_amp_wait2; } ;
struct TYPE_9__ {scalar_t__ amp_short_ref_gnd_fsm; scalar_t__ amp_short_ref_fsm; scalar_t__ amp_rst_fb_fsm; } ;
struct TYPE_16__ {TYPE_7__ sar_amp_ctrl2; TYPE_6__ sar_amp_ctrl1; TYPE_5__ sar_amp_ctrl3; TYPE_4__ sar_meas1_ctrl1; TYPE_3__ sar_meas_wait2; TYPE_2__ sar_meas_wait1; TYPE_1__ sar_meas_ctrl; } ;

/* Variables and functions */
 TYPE_8__ SENS ; 
 void* SENS_FORCE_XPD_AMP_PD ; 

__attribute__((used)) static inline void adc1_fsm_disable(void)
{
#if CONFIG_IDF_TARGET_ESP32
    //channel is set in the  convert function
    SENS.sar_meas_wait2.force_xpd_amp = SENS_FORCE_XPD_AMP_PD;
    //disable FSM, it's only used by the LNA.
    SENS.sar_meas_ctrl.amp_rst_fb_fsm = 0;
    SENS.sar_meas_ctrl.amp_short_ref_fsm = 0;
    SENS.sar_meas_ctrl.amp_short_ref_gnd_fsm = 0;
    SENS.sar_meas_wait1.sar_amp_wait1 = 1;
    SENS.sar_meas_wait1.sar_amp_wait2 = 1;
    SENS.sar_meas_wait2.sar_amp_wait3 = 1;    
#elif CONFIG_IDF_TARGET_ESP32S2BETA
    //channel is set in the  convert function
    SENS.sar_meas1_ctrl1.force_xpd_amp = SENS_FORCE_XPD_AMP_PD;
    //disable FSM, it's only used by the LNA.
    SENS.sar_amp_ctrl3.amp_rst_fb_fsm = 0;
    SENS.sar_amp_ctrl3.amp_short_ref_fsm = 0;
    SENS.sar_amp_ctrl3.amp_short_ref_gnd_fsm = 0;
    SENS.sar_amp_ctrl1.sar_amp_wait1 = 1;
    SENS.sar_amp_ctrl1.sar_amp_wait2 = 1;
    SENS.sar_amp_ctrl2.sar_amp_wait3 = 1;
#endif
}