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
typedef  int /*<<< orphan*/  u8 ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
 int ESP_FAIL ; 
 int ESP_OK ; 
 int /*<<< orphan*/  ETH_P_EAPOL ; 
 int /*<<< orphan*/  IEEE802_1X_TYPE_EAPOL_START ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  WPA2_ENT_EAP_STATE_IN_PROGRESS ; 
 int WPA_ERR_INVALID_BSSID ; 
 int esp_wifi_get_assoc_bssid_internal (int /*<<< orphan*/ *) ; 
 struct eap_sm* gEapSm ; 
 int /*<<< orphan*/  wpa2_set_eap_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wpa2_sm_alloc_eapol (struct eap_sm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa2_sm_ether_send (struct eap_sm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa2_sm_free_eapol (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wpa_sta_is_cur_pmksa_set () ; 

__attribute__((used)) static int wpa2_start_eapol_internal(void)
{
    struct eap_sm *sm = gEapSm;
    int ret = 0;
    u8 bssid[6];
    u8 *buf;
    size_t len;

    if (!sm) {
        return ESP_FAIL;
    }
    if (wpa_sta_is_cur_pmksa_set()) {
        wpa_printf(MSG_DEBUG,
                "RSN: PMKSA caching - do not send EAPOL-Start");
        return ESP_FAIL;
    }

    ret = esp_wifi_get_assoc_bssid_internal(bssid);
    if (ret != 0) {
        wpa_printf(MSG_ERROR, "bssid is empty!");
        return WPA_ERR_INVALID_BSSID;
    }

    buf = wpa2_sm_alloc_eapol(sm, IEEE802_1X_TYPE_EAPOL_START, (u8 *)"", 0, &len, NULL);
    if (!buf) {
        return ESP_FAIL;
    }

    wpa2_set_eap_state(WPA2_ENT_EAP_STATE_IN_PROGRESS);
    wpa2_sm_ether_send(sm, bssid, ETH_P_EAPOL, buf, len);
    wpa2_sm_free_eapol(buf);
    return ESP_OK;
}