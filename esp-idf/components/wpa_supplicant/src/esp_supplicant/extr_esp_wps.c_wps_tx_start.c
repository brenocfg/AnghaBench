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
struct wps_sm {int /*<<< orphan*/  wps_eapol_start_timer; } ;

/* Variables and functions */
 int ESP_ERR_NO_MEM ; 
 int ESP_FAIL ; 
 int ESP_OK ; 
 int /*<<< orphan*/  ETH_P_EAPOL ; 
 int /*<<< orphan*/  IEEE802_1X_TYPE_EAPOL_START ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int esp_wifi_get_assoc_bssid_internal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ets_timer_arm (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct wps_sm* gWpsSm ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * wps_sm_alloc_eapol (struct wps_sm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wps_sm_ether_send (struct wps_sm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wps_sm_free_eapol (int /*<<< orphan*/ *) ; 

int wps_tx_start(void)
{
    struct wps_sm *sm = gWpsSm;
    u8 bssid[6];
    u8 *buf;
    int len;
    int ret = 0;

    ret = esp_wifi_get_assoc_bssid_internal(bssid);
    if (ret != 0) {
        wpa_printf(MSG_ERROR, "bssid is empty!");
        return ret;
    }

    if (!sm) {
        return ESP_FAIL;
    }

    wpa_printf(MSG_DEBUG,  "WPS: Send EAPOL START.");
    buf = wps_sm_alloc_eapol(sm, IEEE802_1X_TYPE_EAPOL_START, (u8 *)"", 0, (size_t *)&len, NULL);
    if (!buf) {
        return ESP_ERR_NO_MEM;
    }

    wps_sm_ether_send(sm, bssid, ETH_P_EAPOL, buf, len);
    wps_sm_free_eapol(buf);

    ets_timer_arm(&sm->wps_eapol_start_timer, 3000, 0);

    return ESP_OK;
}