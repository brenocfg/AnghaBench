#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  esp_err_t ;
struct TYPE_4__ {int /*<<< orphan*/  event_cb; } ;
typedef  TYPE_1__ esp_blufi_callbacks_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTC_PID_BLUFI ; 
 scalar_t__ ESP_BLUEDROID_STATUS_UNINITIALIZED ; 
 int /*<<< orphan*/  ESP_ERR_INVALID_STATE ; 
 int /*<<< orphan*/  ESP_FAIL ; 
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  btc_blufi_set_callbacks (TYPE_1__*) ; 
 scalar_t__ btc_profile_cb_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ esp_bluedroid_get_status () ; 

esp_err_t esp_blufi_register_callbacks(esp_blufi_callbacks_t *callbacks)
{
    if (esp_bluedroid_get_status() == ESP_BLUEDROID_STATUS_UNINITIALIZED) {
        return ESP_ERR_INVALID_STATE;
    }

    if (callbacks == NULL) {
        return ESP_FAIL;
    }

    btc_blufi_set_callbacks(callbacks);
    return (btc_profile_cb_set(BTC_PID_BLUFI, callbacks->event_cb) == 0 ? ESP_OK : ESP_FAIL);
}