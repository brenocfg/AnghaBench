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
typedef  int /*<<< orphan*/  u8 ;
struct hostapd_wpa_psk {int /*<<< orphan*/  const* psk; int /*<<< orphan*/  addr; scalar_t__ group; struct hostapd_wpa_psk* next; } ;
struct TYPE_2__ {struct hostapd_wpa_psk* wpa_psk; } ;
struct hostapd_bss_config {TYPE_1__ ssid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

const u8 * hostapd_get_psk(const struct hostapd_bss_config *conf,
			   const u8 *addr, const u8 *prev_psk)
{
    struct hostapd_wpa_psk *psk;
    int next_ok = prev_psk == NULL;

    for (psk = conf->ssid.wpa_psk; psk != NULL; psk = psk->next) {
        if (next_ok &&
            (psk->group || memcmp(psk->addr, addr, ETH_ALEN) == 0))
            return psk->psk;

        if (psk->psk == prev_psk)
            next_ok = 1;
    }

    return NULL;
}