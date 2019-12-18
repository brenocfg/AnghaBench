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
struct wpa_group {void* reject_4way_hs_for_entropy; void* first_sta_seen; } ;
struct wpa_authenticator {int dummy; } ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 void* TRUE ; 
 int random_pool_ready () ; 
 int /*<<< orphan*/  wpa_group_config_group_keys (struct wpa_authenticator*,struct wpa_group*) ; 
 int /*<<< orphan*/  wpa_group_init_gmk_and_counter (struct wpa_authenticator*,struct wpa_group*) ; 
 int /*<<< orphan*/  wpa_gtk_update (struct wpa_authenticator*,struct wpa_group*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void wpa_group_ensure_init(struct wpa_authenticator *wpa_auth,
                  struct wpa_group *group)
{
    if (group->first_sta_seen)
        return;
    /*
     * System has run bit further than at the time hostapd was started
     * potentially very early during boot up. This provides better chances
     * of collecting more randomness on embedded systems. Re-initialize the
     * GMK and Counter here to improve their strength if there was not
     * enough entropy available immediately after system startup.
     */
    wpa_printf( MSG_DEBUG, "WPA: Re-initialize GMK/Counter on first "
           "station\n");
    if (random_pool_ready() != 1) {
        wpa_printf( MSG_INFO, "WPA: Not enough entropy in random pool "
               "to proceed - reject first 4-way handshake");
        group->reject_4way_hs_for_entropy = TRUE;
    } else {
        group->first_sta_seen = TRUE;
        group->reject_4way_hs_for_entropy = FALSE;
    }

    wpa_group_init_gmk_and_counter(wpa_auth, group);
    wpa_gtk_update(wpa_auth, group);
    wpa_group_config_group_keys(wpa_auth, group);
}