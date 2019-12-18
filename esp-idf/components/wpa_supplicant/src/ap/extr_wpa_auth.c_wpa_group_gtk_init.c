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
struct wpa_group {int GN; int GM; int GN_igtk; int GM_igtk; int /*<<< orphan*/  GTK; int /*<<< orphan*/  wpa_group_state; int /*<<< orphan*/  changed; int /*<<< orphan*/  vlan_id; } ;
struct wpa_authenticator {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  WPA_GROUP_GTK_INIT ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_gtk_update (struct wpa_authenticator*,struct wpa_group*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wpa_group_gtk_init(struct wpa_authenticator *wpa_auth,
                   struct wpa_group *group)
{
    wpa_printf( MSG_DEBUG, "WPA: group state machine entering state "
           "GTK_INIT (VLAN-ID %d)\n", group->vlan_id);
    group->changed = FALSE; /* GInit is not cleared here; avoid loop */
    group->wpa_group_state = WPA_GROUP_GTK_INIT;

    /* GTK[0..N] = 0 */
    memset(group->GTK, 0, sizeof(group->GTK));
    group->GN = 1;
    group->GM = 2;
#ifdef CONFIG_IEEE80211W
    group->GN_igtk = 4;
    group->GM_igtk = 5;
#endif /* CONFIG_IEEE80211W */
    /* GTK[GN] = CalcGTK() */
    wpa_gtk_update(wpa_auth, group);
}