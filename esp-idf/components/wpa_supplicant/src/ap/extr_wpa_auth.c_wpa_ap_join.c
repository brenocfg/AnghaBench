#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct wpa_state_machine {int dummy; } ;
struct hostapd_data {TYPE_2__* wpa_auth; } ;
struct TYPE_5__ {scalar_t__ wpa; } ;
struct TYPE_6__ {TYPE_1__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ esp_wifi_get_hostap_private_internal () ; 
 int /*<<< orphan*/  wpa_auth_sta_associated (TYPE_2__*,struct wpa_state_machine*) ; 
 int /*<<< orphan*/  wpa_auth_sta_deinit (struct wpa_state_machine*) ; 
 struct wpa_state_machine* wpa_auth_sta_init (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,struct wpa_state_machine*) ; 
 scalar_t__ wpa_validate_wpa_ie (TYPE_2__*,struct wpa_state_machine*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool wpa_ap_join(void** sm, uint8_t *bssid, uint8_t *wpa_ie, uint8_t wpa_ie_len)
{
    struct hostapd_data *hapd = (struct hostapd_data*)esp_wifi_get_hostap_private_internal();
    struct wpa_state_machine   **wpa_sm;

    if (!sm || !bssid || !wpa_ie){
        return false;
    }

   
    wpa_sm = (struct wpa_state_machine  **)sm;

    if (hapd) {
        if (hapd->wpa_auth->conf.wpa) {
            if (*wpa_sm){
                wpa_auth_sta_deinit(*wpa_sm);
            }

            *wpa_sm = wpa_auth_sta_init(hapd->wpa_auth, bssid);
            wpa_printf( MSG_DEBUG, "init wpa sm=%p\n", *wpa_sm);

            if (*wpa_sm == NULL) {
                return false;
            }

            if (wpa_validate_wpa_ie(hapd->wpa_auth, *wpa_sm, wpa_ie, wpa_ie_len)) {
                return false;
            }
        }

        wpa_auth_sta_associated(hapd->wpa_auth, *wpa_sm);
    }

    return true;
}