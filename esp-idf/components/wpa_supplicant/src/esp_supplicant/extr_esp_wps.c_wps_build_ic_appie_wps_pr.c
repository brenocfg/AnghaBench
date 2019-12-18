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
typedef  int /*<<< orphan*/  uint8_t ;
struct wps_sm {int /*<<< orphan*/  uuid; int /*<<< orphan*/  dev; } ;
struct wpabuf {int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_PW_DEFAULT ; 
 int /*<<< orphan*/  DEV_PW_PUSHBUTTON ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WIFI_APPIE_WPS_PR ; 
 int /*<<< orphan*/  WPS_REQ_ENROLLEE ; 
 scalar_t__ WPS_TYPE_PBC ; 
 int /*<<< orphan*/  esp_wifi_set_appie_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wps_sm* gWpsSm ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__ wpabuf_head (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_len (struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_put_buf (struct wpabuf*,struct wpabuf*) ; 
 scalar_t__ wpabuf_resize (struct wpabuf**,int /*<<< orphan*/ ) ; 
 scalar_t__ wps_build_probe_req_ie (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ wps_get_type () ; 

__attribute__((used)) static void
wps_build_ic_appie_wps_pr(void)
{
    struct wpabuf *extra_ie = NULL;
    struct wpabuf *wps_ie;
    struct wps_sm *sm = gWpsSm;

    wpa_printf(MSG_DEBUG, "wps build: wps pr");

    if (wps_get_type() == WPS_TYPE_PBC) {
        wps_ie = (struct wpabuf *)wps_build_probe_req_ie(DEV_PW_PUSHBUTTON,
                 sm->dev,
                 sm->uuid, WPS_REQ_ENROLLEE,
                 0, NULL);
    } else {
        wps_ie = (struct wpabuf *)wps_build_probe_req_ie(DEV_PW_DEFAULT,
                 sm->dev,
                 sm->uuid, WPS_REQ_ENROLLEE,
                 0, NULL);
    }

    if (wps_ie) {
        if (wpabuf_resize(&extra_ie, wpabuf_len(wps_ie)) == 0) {
            wpabuf_put_buf(extra_ie, wps_ie);
        } else {
            wpabuf_free(wps_ie);
            return;
        }
        wpabuf_free(wps_ie);
    }

    esp_wifi_set_appie_internal(WIFI_APPIE_WPS_PR, (uint8_t *)wpabuf_head(extra_ie), extra_ie->used, 0);
    wpabuf_free(extra_ie);
}