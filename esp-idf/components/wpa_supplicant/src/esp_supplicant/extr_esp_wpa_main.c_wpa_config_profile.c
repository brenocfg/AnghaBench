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

/* Variables and functions */
 int /*<<< orphan*/  WPA_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WPA_PROTO_RSN ; 
 int /*<<< orphan*/  WPA_PROTO_WPA ; 
 int /*<<< orphan*/  esp_wifi_sta_get_prof_authmode_internal () ; 
 scalar_t__ esp_wifi_sta_prof_is_wpa2_internal () ; 
 scalar_t__ esp_wifi_sta_prof_is_wpa_internal () ; 
 int /*<<< orphan*/  wpa_set_profile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void  wpa_config_profile(void)
{
    if (esp_wifi_sta_prof_is_wpa_internal()) {
        wpa_set_profile(WPA_PROTO_WPA, esp_wifi_sta_get_prof_authmode_internal());
    } else if (esp_wifi_sta_prof_is_wpa2_internal()) {
        wpa_set_profile(WPA_PROTO_RSN, esp_wifi_sta_get_prof_authmode_internal());
    } else {
        WPA_ASSERT(0);
    }
}