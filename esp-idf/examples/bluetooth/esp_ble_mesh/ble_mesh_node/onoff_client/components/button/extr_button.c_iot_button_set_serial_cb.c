#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {char* name; int /*<<< orphan*/  dispatch_method; int /*<<< orphan*/  callback; TYPE_3__* arg; } ;
typedef  TYPE_2__ esp_timer_create_args_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  scalar_t__ button_handle_t ;
struct TYPE_6__ {int /*<<< orphan*/ * tmr; TYPE_3__* pbtn; int /*<<< orphan*/  interval; int /*<<< orphan*/  cb; void* arg; } ;
struct TYPE_8__ {int serial_thres_sec; TYPE_1__ press_serial_cb; } ;
typedef  TYPE_3__ button_dev_t ;
typedef  int /*<<< orphan*/  button_cb ;
typedef  int /*<<< orphan*/  TickType_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  ESP_TIMER_TASK ; 
 int /*<<< orphan*/  button_press_serial_cb ; 
 int /*<<< orphan*/  esp_timer_create (TYPE_2__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pdFALSE ; 
 int /*<<< orphan*/  portMAX_DELAY ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  xTimerChangePeriod (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xTimerCreate (char*,int,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 

esp_err_t iot_button_set_serial_cb(button_handle_t btn_handle, uint32_t start_after_sec, TickType_t interval_tick, button_cb cb, void* arg)
{
    button_dev_t* btn = (button_dev_t*) btn_handle;
    btn->serial_thres_sec = start_after_sec;

    if (btn->press_serial_cb.tmr == NULL) {
        #if !USE_ESP_TIMER
        btn->press_serial_cb.tmr = xTimerCreate("btn_serial_tmr", btn->serial_thres_sec*1000 / portTICK_PERIOD_MS,
                            pdFALSE, btn, button_press_serial_cb);
        #else
        esp_timer_create_args_t tmr_param_ser;
        tmr_param_ser.arg = btn;
        tmr_param_ser.callback = button_press_serial_cb;
        tmr_param_ser.dispatch_method = ESP_TIMER_TASK;
        tmr_param_ser.name = "btn_serial_tmr";
        esp_timer_create(&tmr_param_ser, &btn->press_serial_cb.tmr);
        #endif
    }
    btn->press_serial_cb.arg = arg;
    btn->press_serial_cb.cb = cb;
    btn->press_serial_cb.interval = interval_tick;
    btn->press_serial_cb.pbtn = btn;
    #if !USE_ESP_TIMER
    xTimerChangePeriod(btn->press_serial_cb.tmr, btn->serial_thres_sec*1000 / portTICK_PERIOD_MS, portMAX_DELAY);
    #endif
    return ESP_OK;
}