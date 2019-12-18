#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  esp_err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ESP_OK ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  WPA2_VERSION ; 
 int /*<<< orphan*/  eap_peer_sm_deinit () ; 
 int /*<<< orphan*/  eap_peer_unregister_methods () ; 
 int /*<<< orphan*/  esp_wifi_unregister_wpa2_cb_internal () ; 
 scalar_t__ gEapSm ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

esp_err_t esp_wifi_sta_wpa2_ent_disable_fn(void *param)
{
    wpa_printf(MSG_INFO, "WPA2 ENTERPRISE VERSION: [%s] disable\n", WPA2_VERSION);
    esp_wifi_unregister_wpa2_cb_internal();

    if (gEapSm) {
        eap_peer_sm_deinit();
    }

#ifdef USE_WPA2_TASK
#endif

#ifdef EAP_PEER_METHOD
    eap_peer_unregister_methods();
#endif

    return ESP_OK;
}