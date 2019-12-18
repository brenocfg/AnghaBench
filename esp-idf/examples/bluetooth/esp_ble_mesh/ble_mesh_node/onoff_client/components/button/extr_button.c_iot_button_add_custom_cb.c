#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_9__ {char* name; int /*<<< orphan*/  dispatch_method; int /*<<< orphan*/  callback; TYPE_2__* arg; } ;
typedef  TYPE_1__ esp_timer_create_args_t ;
typedef  int /*<<< orphan*/  esp_err_t ;
typedef  TYPE_2__* button_handle_t ;
struct TYPE_11__ {TYPE_2__* cb_head; } ;
typedef  TYPE_3__ button_dev_t ;
struct TYPE_10__ {int interval; struct TYPE_10__* next_cb; int /*<<< orphan*/  tmr; TYPE_3__* pbtn; int /*<<< orphan*/  cb; void* arg; } ;
typedef  TYPE_2__ button_cb_t ;
typedef  int /*<<< orphan*/  button_cb ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_ERR_INVALID_ARG ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  ESP_TIMER_TASK ; 
 int /*<<< orphan*/  IOT_CHECK (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POINT_ASSERT (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAG ; 
 int /*<<< orphan*/  button_press_cb ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  esp_timer_create (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdFALSE ; 
 int portTICK_PERIOD_MS ; 
 int /*<<< orphan*/  xTimerCreate (char*,int,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 

esp_err_t iot_button_add_custom_cb(button_handle_t btn_handle, uint32_t press_sec, button_cb cb, void* arg)
{
    POINT_ASSERT(TAG, btn_handle, ESP_ERR_INVALID_ARG);
    IOT_CHECK(TAG, press_sec != 0, ESP_ERR_INVALID_ARG);
    button_dev_t* btn = (button_dev_t*) btn_handle;
    button_cb_t* cb_new = (button_cb_t*) calloc(1, sizeof(button_cb_t));
    POINT_ASSERT(TAG, cb_new, ESP_FAIL);
    cb_new->arg = arg;
    cb_new->cb = cb;
    cb_new->interval = press_sec * 1000 / portTICK_PERIOD_MS;
    cb_new->pbtn = btn;
    #if !USE_ESP_TIMER
    cb_new->tmr = xTimerCreate("btn_press_tmr", cb_new->interval, pdFALSE, cb_new, button_press_cb);
    #else
    esp_timer_create_args_t tmr_param_cus;
    tmr_param_cus.arg = cb_new;
    tmr_param_cus.callback = button_press_cb;
    tmr_param_cus.dispatch_method = ESP_TIMER_TASK;
    tmr_param_cus.name = "btn_press_custom_tmr";
    esp_timer_create(&tmr_param_cus, &cb_new->tmr);
    #endif
    cb_new->next_cb = btn->cb_head;
    btn->cb_head = cb_new;
    return ESP_OK;
}