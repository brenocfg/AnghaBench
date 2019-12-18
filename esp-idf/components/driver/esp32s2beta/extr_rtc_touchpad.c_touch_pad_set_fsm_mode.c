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
typedef  scalar_t__ touch_fsm_mode_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {int touch_slp_timer_en; scalar_t__ touch_start_force; scalar_t__ touch_start_en; } ;
struct TYPE_4__ {TYPE_1__ touch_ctrl2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__ RTCCNTL ; 
 int /*<<< orphan*/  RTC_TOUCH_ENTER_CRITICAL () ; 
 int /*<<< orphan*/  RTC_TOUCH_EXIT_CRITICAL () ; 
 scalar_t__ TOUCH_FSM_MODE_TIMER ; 

esp_err_t touch_pad_set_fsm_mode(touch_fsm_mode_t mode)
{
    RTC_TOUCH_ENTER_CRITICAL();
    RTCCNTL.touch_ctrl2.touch_start_en = 0; //stop touch fsm
    RTCCNTL.touch_ctrl2.touch_start_force = mode;
    RTCCNTL.touch_ctrl2.touch_slp_timer_en = (mode == TOUCH_FSM_MODE_TIMER ? 1 : 0);
    RTC_TOUCH_EXIT_CRITICAL();
    return ESP_OK;
}