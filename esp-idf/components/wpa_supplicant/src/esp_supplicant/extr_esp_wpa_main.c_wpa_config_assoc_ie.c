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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WIFI_APPIE_RSN ; 
 int /*<<< orphan*/  WIFI_APPIE_WPA ; 
 int /*<<< orphan*/  esp_wifi_set_appie_internal (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int) ; 

void  wpa_config_assoc_ie(u8 proto, u8 *assoc_buf, u32 assoc_wpa_ie_len)
{
    if (proto == BIT(0)) {
        esp_wifi_set_appie_internal(WIFI_APPIE_WPA, assoc_buf, assoc_wpa_ie_len, 1);
    } else {
        esp_wifi_set_appie_internal(WIFI_APPIE_RSN, assoc_buf, assoc_wpa_ie_len, 1);
    }
}