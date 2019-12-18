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
struct wpa_group {scalar_t__ wpa_group_state; scalar_t__ GKeyDoneStations; scalar_t__ GTKReKey; scalar_t__ GTKAuthenticator; scalar_t__ GInit; } ;
struct wpa_authenticator {int dummy; } ;

/* Variables and functions */
 scalar_t__ WPA_GROUP_GTK_INIT ; 
 scalar_t__ WPA_GROUP_SETKEYS ; 
 scalar_t__ WPA_GROUP_SETKEYSDONE ; 
 int /*<<< orphan*/  wpa_group_gtk_init (struct wpa_authenticator*,struct wpa_group*) ; 
 int /*<<< orphan*/  wpa_group_setkeys (struct wpa_authenticator*,struct wpa_group*) ; 
 int /*<<< orphan*/  wpa_group_setkeysdone (struct wpa_authenticator*,struct wpa_group*) ; 

__attribute__((used)) static void wpa_group_sm_step(struct wpa_authenticator *wpa_auth,
                  struct wpa_group *group)
{
    if (group->GInit) {
        wpa_group_gtk_init(wpa_auth, group);
    } else if (group->wpa_group_state == WPA_GROUP_GTK_INIT &&
           group->GTKAuthenticator) {
        wpa_group_setkeysdone(wpa_auth, group);
    } else if (group->wpa_group_state == WPA_GROUP_SETKEYSDONE &&
           group->GTKReKey) {
        wpa_group_setkeys(wpa_auth, group);
    } else if (group->wpa_group_state == WPA_GROUP_SETKEYS) {
        if (group->GKeyDoneStations == 0)
            wpa_group_setkeysdone(wpa_auth, group);
        else if (group->GTKReKey)
            wpa_group_setkeys(wpa_auth, group);
    }
}