#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {int touch_clkgate_en; } ;
struct TYPE_8__ {TYPE_1__ touch_ctrl2; } ;
struct TYPE_6__ {int /*<<< orphan*/  touch_channel_clr; } ;
struct TYPE_7__ {TYPE_2__ sar_touch_chn_st; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_4__ RTCCNTL ; 
 int /*<<< orphan*/  RTC_TOUCH_ENTER_CRITICAL () ; 
 int /*<<< orphan*/  RTC_TOUCH_EXIT_CRITICAL () ; 
 TYPE_3__ SENS ; 
 int /*<<< orphan*/  TOUCH_PAD_BIT_MASK_MAX ; 

esp_err_t touch_pad_fsm_start(void)
{
    RTC_TOUCH_ENTER_CRITICAL();
    RTCCNTL.touch_ctrl2.touch_clkgate_en = 1; //enable touch clock for FSM. or force enable.
    SENS.sar_touch_chn_st.touch_channel_clr = TOUCH_PAD_BIT_MASK_MAX;   // clear SENS_TOUCH_SLP_BASELINE
    RTC_TOUCH_EXIT_CRITICAL();
    return ESP_OK;
}