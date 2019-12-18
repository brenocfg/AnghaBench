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
struct wpabuf {int /*<<< orphan*/  used; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WIFI_APPIE_WPS_AR ; 
 int /*<<< orphan*/  WPS_REQ_ENROLLEE ; 
 int /*<<< orphan*/  esp_wifi_set_appie_internal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 
 scalar_t__ wpabuf_head (struct wpabuf*) ; 
 scalar_t__ wps_build_assoc_req_ie (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
wps_build_ic_appie_wps_ar(void)
{
    struct wpabuf *buf = (struct wpabuf *)wps_build_assoc_req_ie(WPS_REQ_ENROLLEE);

    wpa_printf(MSG_DEBUG, "wps build: wps ar");

    if (buf) {
        esp_wifi_set_appie_internal(WIFI_APPIE_WPS_AR, (uint8_t *)wpabuf_head(buf), buf->used, 0);
        wpabuf_free(buf);
    }
}