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
struct wpa_group {int GN; int GN_igtk; int /*<<< orphan*/ * IGTK; int /*<<< orphan*/  GNonce; int /*<<< orphan*/  GMK; int /*<<< orphan*/  Counter; int /*<<< orphan*/  GTK_len; int /*<<< orphan*/ * GTK; } ;
struct TYPE_2__ {scalar_t__ ieee80211w; } ;
struct wpa_authenticator {int /*<<< orphan*/  addr; TYPE_1__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ NO_MGMT_FRAME_PROTECTION ; 
 int /*<<< orphan*/  WPA_IGTK_LEN ; 
 int /*<<< orphan*/  WPA_NONCE_LEN ; 
 int /*<<< orphan*/  inc_byte_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_gmk_to_gtk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wpa_gtk_update(struct wpa_authenticator *wpa_auth,
              struct wpa_group *group)
{
    int ret = 0;

    memcpy(group->GNonce, group->Counter, WPA_NONCE_LEN);
    inc_byte_array(group->Counter, WPA_NONCE_LEN);

    if (wpa_gmk_to_gtk(group->GMK, "Group key expansion",
               wpa_auth->addr, group->GNonce,
               group->GTK[group->GN - 1], group->GTK_len) < 0)
        ret = -1;
    wpa_hexdump_key(MSG_DEBUG, "GTK",
            group->GTK[group->GN - 1], group->GTK_len);

#ifdef CONFIG_IEEE80211W
    if (wpa_auth->conf.ieee80211w != NO_MGMT_FRAME_PROTECTION) {
        memcpy(group->GNonce, group->Counter, WPA_NONCE_LEN);
        inc_byte_array(group->Counter, WPA_NONCE_LEN);
        if (wpa_gmk_to_gtk(group->GMK, "IGTK key expansion",
                   wpa_auth->addr, group->GNonce,
                   group->IGTK[group->GN_igtk - 4],
                   WPA_IGTK_LEN) < 0)
            ret = -1;
        wpa_hexdump_key(MSG_DEBUG, "IGTK",
                group->IGTK[group->GN_igtk - 4], WPA_IGTK_LEN);
    }
#endif /* CONFIG_IEEE80211W */

    return ret;
}