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
typedef  int /*<<< orphan*/  touch_pad_conn_type_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_3__ {int /*<<< orphan*/  touch_inactive_connection; } ;
struct TYPE_4__ {TYPE_1__ touch_scan_ctrl; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__ RTCCNTL ; 
 int /*<<< orphan*/  RTC_TOUCH_ENTER_CRITICAL () ; 
 int /*<<< orphan*/  RTC_TOUCH_EXIT_CRITICAL () ; 

esp_err_t touch_pad_set_inactive_connect(touch_pad_conn_type_t type)
{
    RTC_TOUCH_ENTER_CRITICAL();
    RTCCNTL.touch_scan_ctrl.touch_inactive_connection = type;
    RTC_TOUCH_EXIT_CRITICAL();
    return ESP_OK;
}