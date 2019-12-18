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
struct wpa_authenticator {int dummy; } ;
typedef  enum wpa_alg { ____Placeholder_wpa_alg } wpa_alg ;

/* Variables and functions */
 int esp_wifi_set_ap_key_internal (int,int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static inline int wpa_auth_set_key(struct wpa_authenticator *wpa_auth,
                   int vlan_id,
                   enum wpa_alg alg, const u8 *addr, int idx,
                   u8 *key, size_t key_len)
{
    return esp_wifi_set_ap_key_internal(alg, addr, idx, key, key_len);
}