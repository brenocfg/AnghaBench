#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ wifi_mode_t ;
struct TYPE_2__ {int bssid_set; int /*<<< orphan*/  ssid; int /*<<< orphan*/  bssid; } ;
struct wps_sm {int is_wps_scan; char* ssid; int /*<<< orphan*/  channel; scalar_t__ ssid_len; TYPE_1__ config; scalar_t__ scan_cnt; int /*<<< orphan*/  bssid; int /*<<< orphan*/  discover_ssid_cnt; } ;
struct wps_scan_ie {char* bssid; int capinfo; int /*<<< orphan*/  chan; scalar_t__* ssid; int /*<<< orphan*/  wpa; int /*<<< orphan*/  rsn; scalar_t__* wps; } ;
struct wpabuf {int dummy; } ;

/* Variables and functions */
 scalar_t__ ETH_ALEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int WIFI_CAPINFO_PRIVACY ; 
 scalar_t__ WIFI_MODE_APSTA ; 
 scalar_t__ WIFI_MODE_STA ; 
 scalar_t__ WPS_STATUS_DISABLE ; 
 scalar_t__ WPS_STATUS_SCANNING ; 
 scalar_t__ WPS_TYPE_DISABLE ; 
 int /*<<< orphan*/  esp_wifi_enable_sta_privacy_internal () ; 
 int /*<<< orphan*/  esp_wifi_get_mode (scalar_t__*) ; 
 struct wps_sm* gWpsSm ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  os_bzero (char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 struct wpabuf* wpabuf_alloc_copy (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__ wps_get_status () ; 
 scalar_t__ wps_get_type () ; 
 scalar_t__ wps_is_selected_pbc_registrar (struct wpabuf*,char*) ; 
 scalar_t__ wps_is_selected_pin_registrar (struct wpabuf*,char*) ; 

__attribute__((used)) static bool
wps_parse_scan_result(struct wps_scan_ie *scan)
{
    struct wps_sm *sm = gWpsSm;
    wifi_mode_t op_mode = 0;
#ifdef WPS_DEBUG
    char tmp[32];

    os_bzero(tmp, 32);
    strncpy(tmp, (char *)&scan->ssid[2], (int)scan->ssid[1]);
    wpa_printf(MSG_DEBUG, "wps parse scan: %s", tmp);
#endif

    if (wps_get_type() == WPS_TYPE_DISABLE
            || (wps_get_status() != WPS_STATUS_DISABLE
                && wps_get_status() != WPS_STATUS_SCANNING)
       ) {
        return false;
    }

    esp_wifi_get_mode(&op_mode);
    if ((op_mode == WIFI_MODE_STA || op_mode == WIFI_MODE_APSTA) && scan->wps) {
        struct wpabuf *buf = wpabuf_alloc_copy(scan->wps + 6, scan->wps[1] - 4);

        if (wps_is_selected_pbc_registrar(buf, scan->bssid)
                || wps_is_selected_pin_registrar(buf, scan->bssid)) {
            wpabuf_free(buf);

            if (sm->is_wps_scan == false) {
                return false;
            }
            if (memcmp(sm->config.bssid, scan->bssid, ETH_ALEN) != 0 ) {
                sm->discover_ssid_cnt++;
            }

            if (!scan->rsn && !scan->wpa && (scan->capinfo & WIFI_CAPINFO_PRIVACY)) {
                wpa_printf(MSG_ERROR, "WEP not suppported in WPS");

                return false;
            }

            esp_wifi_enable_sta_privacy_internal();
            os_bzero(sm->ssid, sizeof(sm->ssid));
            strncpy((char *)sm->ssid, (char *)&scan->ssid[2], (int)scan->ssid[1]);
            sm->ssid_len = scan->ssid[1];
            if (scan->bssid) {
                memcpy(gWpsSm->bssid, scan->bssid, ETH_ALEN);
                memcpy(sm->config.bssid, scan->bssid, ETH_ALEN);
                sm->config.bssid_set = 1;
            } else {
            }
            wpa_printf(MSG_DEBUG, "wps discover [%s]", sm->ssid);
            sm->scan_cnt = 0;

            memcpy(sm->config.ssid, sm->ssid, sm->ssid_len);
            sm->channel = scan->chan;

            return true;
        }
        wpabuf_free(buf);
    }

    return false;
}