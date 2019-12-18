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
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 TYPE_2__ RTCCNTL ; 
 int /*<<< orphan*/  RTC_MODULE_CHECK (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

esp_err_t touch_pad_get_inactive_connect(touch_pad_conn_type_t *type)
{
    RTC_MODULE_CHECK(type != NULL, "parameter is NULL", ESP_ERR_INVALID_ARG);
    *type = RTCCNTL.touch_scan_ctrl.touch_inactive_connection;
    return ESP_OK;
}