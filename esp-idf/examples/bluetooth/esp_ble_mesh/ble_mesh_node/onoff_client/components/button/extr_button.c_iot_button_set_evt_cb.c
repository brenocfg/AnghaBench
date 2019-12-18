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
typedef  scalar_t__ button_handle_t ;
struct TYPE_7__ {int interval; TYPE_4__* pbtn; void* cb; void* arg; } ;
struct TYPE_6__ {int interval; int /*<<< orphan*/  tmr; TYPE_4__* pbtn; void* cb; void* arg; } ;
struct TYPE_5__ {int interval; int /*<<< orphan*/  tmr; TYPE_4__* pbtn; void* cb; void* arg; } ;
struct TYPE_8__ {TYPE_3__ tap_short_cb; TYPE_2__ tap_psh_cb; TYPE_1__ tap_rls_cb; } ;
typedef  TYPE_4__ button_dev_t ;
typedef  scalar_t__ button_cb_type_t ;
typedef  void* button_cb ;

/* Variables and functions */
 scalar_t__ BUTTON_CB_PUSH ; 
 scalar_t__ BUTTON_CB_RELEASE ; 
 scalar_t__ BUTTON_CB_SERIAL ; 
 scalar_t__ BUTTON_CB_TAP ; 
 int BUTTON_GLITCH_FILTER_TIME_MS ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  POINT_ASSERT (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  iot_button_set_serial_cb (scalar_t__,int,int,void*,void*) ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int portTICK_RATE_MS ; 
 int /*<<< orphan*/  xTimerChangePeriod (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

esp_err_t iot_button_set_evt_cb(button_handle_t btn_handle, button_cb_type_t type, button_cb cb, void* arg)
{
    POINT_ASSERT(TAG, btn_handle, ESP_ERR_INVALID_ARG);
    button_dev_t* btn = (button_dev_t*) btn_handle;
    if (type == BUTTON_CB_PUSH) {
        btn->tap_psh_cb.arg = arg;
        btn->tap_psh_cb.cb = cb;
        btn->tap_psh_cb.interval = BUTTON_GLITCH_FILTER_TIME_MS / portTICK_RATE_MS;
        btn->tap_psh_cb.pbtn = btn;
        #if !USE_ESP_TIMER
        xTimerChangePeriod(btn->tap_psh_cb.tmr, btn->tap_psh_cb.interval, portMAX_DELAY);
        #endif
    } else if (type == BUTTON_CB_RELEASE) {
        btn->tap_rls_cb.arg = arg;
        btn->tap_rls_cb.cb = cb;
        btn->tap_rls_cb.interval = BUTTON_GLITCH_FILTER_TIME_MS / portTICK_RATE_MS;
        btn->tap_rls_cb.pbtn = btn;
        #if !USE_ESP_TIMER
        xTimerChangePeriod(btn->tap_rls_cb.tmr, btn->tap_psh_cb.interval, portMAX_DELAY);
        #endif
    } else if (type == BUTTON_CB_TAP) {
        btn->tap_short_cb.arg = arg;
        btn->tap_short_cb.cb = cb;
        btn->tap_short_cb.interval = BUTTON_GLITCH_FILTER_TIME_MS / portTICK_RATE_MS;
        btn->tap_short_cb.pbtn = btn;
    } else if (type == BUTTON_CB_SERIAL) {
        iot_button_set_serial_cb(btn_handle, 1, 1000 / portTICK_RATE_MS, cb, arg);
    }
    return ESP_OK;
}