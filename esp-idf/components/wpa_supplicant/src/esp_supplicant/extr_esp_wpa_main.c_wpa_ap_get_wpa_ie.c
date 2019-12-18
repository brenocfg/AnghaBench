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
typedef  int /*<<< orphan*/  uint8_t ;
struct hostapd_data {TYPE_1__* wpa_auth; } ;
struct TYPE_2__ {int /*<<< orphan*/ * wpa_ie; int /*<<< orphan*/  wpa_ie_len; } ;

/* Variables and functions */
 scalar_t__ esp_wifi_get_hostap_private_internal () ; 

uint8_t  *wpa_ap_get_wpa_ie(uint8_t *ie_len)
{
    struct hostapd_data *hapd = (struct hostapd_data *)esp_wifi_get_hostap_private_internal();

    if (!hapd || !hapd->wpa_auth || !hapd->wpa_auth->wpa_ie) {
        return NULL;
    }

    *ie_len = hapd->wpa_auth->wpa_ie_len;
    return hapd->wpa_auth->wpa_ie;
}