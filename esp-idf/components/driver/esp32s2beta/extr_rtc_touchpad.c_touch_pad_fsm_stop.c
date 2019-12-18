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
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {scalar_t__ touch_clkgate_en; scalar_t__ touch_slp_timer_en; scalar_t__ touch_start_en; } ;
struct TYPE_4__ {TYPE_1__ touch_ctrl2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__ RTCCNTL ; 
 int /*<<< orphan*/  RTC_TOUCH_ENTER_CRITICAL () ; 
 int /*<<< orphan*/  RTC_TOUCH_EXIT_CRITICAL () ; 

esp_err_t touch_pad_fsm_stop(void)
{
    RTC_TOUCH_ENTER_CRITICAL();
    RTCCNTL.touch_ctrl2.touch_start_en = 0; //stop touch fsm
    RTCCNTL.touch_ctrl2.touch_slp_timer_en = 0;
    RTCCNTL.touch_ctrl2.touch_clkgate_en = 0; //enable touch clock for FSM. or force enable.
    RTC_TOUCH_EXIT_CRITICAL();
    return ESP_OK;
}