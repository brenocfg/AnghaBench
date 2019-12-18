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
struct wpa_funcs {int /*<<< orphan*/  wpa_michael_mic_failure; int /*<<< orphan*/ * wpa_config_bss; int /*<<< orphan*/  wpa_parse_wpa_ie; int /*<<< orphan*/  wpa_config_parse_string; int /*<<< orphan*/  wpa_ap_deinit; int /*<<< orphan*/  wpa_ap_init; int /*<<< orphan*/  wpa_ap_rx_eapol; int /*<<< orphan*/  wpa_ap_get_wpa_ie; int /*<<< orphan*/  wpa_ap_remove; int /*<<< orphan*/  wpa_ap_join; int /*<<< orphan*/  wpa_sta_in_4way_handshake; int /*<<< orphan*/  wpa_sta_connect; int /*<<< orphan*/  wpa_sta_rx_eapol; int /*<<< orphan*/  wpa_sta_deinit; int /*<<< orphan*/  wpa_sta_init; } ;

/* Variables and functions */
 int ESP_ERR_NO_MEM ; 
 int ESP_OK ; 
 int /*<<< orphan*/  esp_wifi_register_wpa_cb_internal (struct wpa_funcs*) ; 
 int /*<<< orphan*/  hostap_deinit ; 
 int /*<<< orphan*/  hostap_init ; 
 scalar_t__ os_malloc (int) ; 
 int /*<<< orphan*/  wpa_ap_get_wpa_ie ; 
 int /*<<< orphan*/  wpa_ap_join ; 
 int /*<<< orphan*/  wpa_ap_remove ; 
 int /*<<< orphan*/  wpa_ap_rx_eapol ; 
 int /*<<< orphan*/  wpa_attach ; 
 int /*<<< orphan*/  wpa_config_parse_string ; 
 int /*<<< orphan*/  wpa_deattach ; 
 int /*<<< orphan*/  wpa_michael_mic_failure ; 
 int /*<<< orphan*/  wpa_parse_wpa_ie_wrapper ; 
 int /*<<< orphan*/  wpa_sm_rx_eapol ; 
 int /*<<< orphan*/  wpa_sta_connect ; 
 int /*<<< orphan*/  wpa_sta_in_4way_handshake ; 

int esp_supplicant_init(void)
{
    struct wpa_funcs *wpa_cb;

    wpa_cb = (struct wpa_funcs *)os_malloc(sizeof(struct wpa_funcs));
    if (!wpa_cb) {
        return ESP_ERR_NO_MEM;
    }

    wpa_cb->wpa_sta_init       = wpa_attach;
    wpa_cb->wpa_sta_deinit     = wpa_deattach;
    wpa_cb->wpa_sta_rx_eapol   = wpa_sm_rx_eapol;
    wpa_cb->wpa_sta_connect    = wpa_sta_connect;
    wpa_cb->wpa_sta_in_4way_handshake = wpa_sta_in_4way_handshake;

    wpa_cb->wpa_ap_join       = wpa_ap_join;
    wpa_cb->wpa_ap_remove     = wpa_ap_remove;
    wpa_cb->wpa_ap_get_wpa_ie = wpa_ap_get_wpa_ie;
    wpa_cb->wpa_ap_rx_eapol   = wpa_ap_rx_eapol;
    wpa_cb->wpa_ap_init       = hostap_init;
    wpa_cb->wpa_ap_deinit     = hostap_deinit;

    wpa_cb->wpa_config_parse_string  = wpa_config_parse_string;
    wpa_cb->wpa_parse_wpa_ie  = wpa_parse_wpa_ie_wrapper;
    wpa_cb->wpa_config_bss = NULL;//wpa_config_bss;
    wpa_cb->wpa_michael_mic_failure = wpa_michael_mic_failure;

    esp_wifi_register_wpa_cb_internal(wpa_cb);

    return ESP_OK;
}