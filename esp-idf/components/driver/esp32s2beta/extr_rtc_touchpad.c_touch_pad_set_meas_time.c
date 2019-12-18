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
typedef  void* uint16_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_5__ {int /*<<< orphan*/  touch_xpd_wait; } ;
struct TYPE_4__ {void* touch_meas_num; void* touch_sleep_cycles; } ;
struct TYPE_6__ {TYPE_2__ touch_ctrl2; TYPE_1__ touch_ctrl1; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_3__ RTCCNTL ; 
 int /*<<< orphan*/  RTC_TOUCH_ENTER_CRITICAL () ; 
 int /*<<< orphan*/  RTC_TOUCH_EXIT_CRITICAL () ; 
 int /*<<< orphan*/  TOUCH_PAD_MEASURE_WAIT_DEFAULT ; 

esp_err_t touch_pad_set_meas_time(uint16_t sleep_cycle, uint16_t meas_times)
{
    RTC_TOUCH_ENTER_CRITICAL();
    // touch sensor sleep cycle Time = sleep_cycle / RTC_SLOW_CLK( can be 150k or 32k depending on the options)
    RTCCNTL.touch_ctrl1.touch_sleep_cycles = sleep_cycle;
    //The times of charge and discharge in each measure process of touch channels.
    RTCCNTL.touch_ctrl1.touch_meas_num = meas_times;
    //the waiting cycles (in 8MHz) between TOUCH_START and TOUCH_XPD
    RTCCNTL.touch_ctrl2.touch_xpd_wait = TOUCH_PAD_MEASURE_WAIT_DEFAULT; //wait volt stable
    RTC_TOUCH_EXIT_CRITICAL();
    return ESP_OK;
}