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
typedef  scalar_t__ button_handle_t ;
struct TYPE_4__ {int /*<<< orphan*/  tmr; TYPE_1__* pbtn; int /*<<< orphan*/ * arg; int /*<<< orphan*/ * cb; } ;
struct TYPE_3__ {TYPE_2__ press_serial_cb; TYPE_2__ tap_short_cb; TYPE_2__ tap_rls_cb; TYPE_2__ tap_psh_cb; } ;
typedef  TYPE_1__ button_dev_t ;
typedef  scalar_t__ button_cb_type_t ;
typedef  TYPE_2__ button_cb_t ;

/* Variables and functions */
 scalar_t__ BUTTON_CB_PUSH ; 
 scalar_t__ BUTTON_CB_RELEASE ; 
 scalar_t__ BUTTON_CB_SERIAL ; 
 scalar_t__ BUTTON_CB_TAP ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  button_free_tmr (int /*<<< orphan*/ *) ; 

esp_err_t iot_button_rm_cb(button_handle_t btn_handle, button_cb_type_t type)
{
    button_dev_t* btn = (button_dev_t*) btn_handle;
    button_cb_t* btn_cb = NULL;
    if (type == BUTTON_CB_PUSH) {
        btn_cb = &btn->tap_psh_cb;
    } else if (type == BUTTON_CB_RELEASE) {
        btn_cb = &btn->tap_rls_cb;
    } else if (type == BUTTON_CB_TAP) {
        btn_cb = &btn->tap_short_cb;
    } else if (type == BUTTON_CB_SERIAL) {
        btn_cb = &btn->press_serial_cb;
    }
    btn_cb->cb = NULL;
    btn_cb->arg = NULL;
    btn_cb->pbtn = btn;
    button_free_tmr(&btn_cb->tmr);
    return ESP_OK;
}