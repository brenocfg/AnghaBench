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
typedef  int /*<<< orphan*/  const u8 ;
struct wpa_authenticator {int dummy; } ;
struct hostapd_data {int /*<<< orphan*/  conf; } ;

/* Variables and functions */
 scalar_t__ esp_wifi_get_hostap_private_internal () ; 
 scalar_t__ hostapd_get_psk (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static inline const u8 * wpa_auth_get_psk(struct wpa_authenticator *wpa_auth,
                      const u8 *addr, const u8 *prev_psk)
{
    struct hostapd_data *hapd = (struct hostapd_data *)esp_wifi_get_hostap_private_internal();

    if (!hapd){
        return NULL;
    }

    return (u8*)hostapd_get_psk(hapd->conf, addr, prev_psk);
}