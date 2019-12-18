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
struct wpa_group {int GN; int GN_igtk; int /*<<< orphan*/ * IGTK; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  GTK_len; int /*<<< orphan*/ * GTK; } ;
struct TYPE_2__ {scalar_t__ ieee80211w; int /*<<< orphan*/  wpa_group; } ;
struct wpa_authenticator {TYPE_1__ conf; } ;

/* Variables and functions */
 scalar_t__ NO_MGMT_FRAME_PROTECTION ; 
 int /*<<< orphan*/  WPA_ALG_IGTK ; 
 int /*<<< orphan*/  WPA_IGTK_LEN ; 
 int /*<<< orphan*/ * broadcast_ether_addr ; 
 scalar_t__ wpa_auth_set_key (struct wpa_authenticator*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_cipher_to_alg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wpa_group_config_group_keys(struct wpa_authenticator *wpa_auth,
                       struct wpa_group *group)
{
    int ret = 0;
    if (wpa_auth_set_key(wpa_auth, group->vlan_id,
                 wpa_cipher_to_alg(wpa_auth->conf.wpa_group),
                 (uint8_t *)broadcast_ether_addr, group->GN,
                 group->GTK[group->GN - 1], group->GTK_len) < 0)
        ret = -1;

#ifdef CONFIG_IEEE80211W
    if (wpa_auth->conf.ieee80211w != NO_MGMT_FRAME_PROTECTION &&
        wpa_auth_set_key(wpa_auth, group->vlan_id, WPA_ALG_IGTK,
        		 broadcast_ether_addr, group->GN_igtk,
                 group->IGTK[group->GN_igtk - 4],
                 WPA_IGTK_LEN) < 0)
        ret = -1;
#endif /* CONFIG_IEEE80211W */

    return ret;
}