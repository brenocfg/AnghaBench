#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ param; scalar_t__ fn; } ;
typedef  TYPE_1__ wifi_wpa2_param_t ;
typedef  scalar_t__ wifi_wpa2_fn_t ;
typedef  scalar_t__ esp_err_t ;

/* Variables and functions */
 scalar_t__ ESP_OK ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  WPA2_STATE_DISABLED ; 
 scalar_t__ esp_wifi_sta_wpa2_ent_disable_fn ; 
 scalar_t__ esp_wifi_sta_wpa2_ent_disable_internal (TYPE_1__*) ; 
 int /*<<< orphan*/  wpa2_api_lock () ; 
 int /*<<< orphan*/  wpa2_api_unlock () ; 
 scalar_t__ wpa2_is_disabled () ; 
 int /*<<< orphan*/  wpa2_set_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

esp_err_t esp_wifi_sta_wpa2_ent_disable(void)
{
    wifi_wpa2_param_t param;
    esp_err_t ret;

    wpa2_api_lock();

    if (wpa2_is_disabled()) {
        wpa_printf(MSG_INFO, "WPA2: already disabled");
        wpa2_api_unlock();
        return ESP_OK;
    }

    param.fn = (wifi_wpa2_fn_t)esp_wifi_sta_wpa2_ent_disable_fn;
    param.param = 0;
    ret = esp_wifi_sta_wpa2_ent_disable_internal(&param);

    if (ESP_OK == ret) {
        wpa2_set_state(WPA2_STATE_DISABLED);
    } else {
        wpa_printf(MSG_ERROR, "failed to disable wpa2 ret=%d", ret);
    }

    wpa2_api_unlock();

    return ret;
}