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
struct wpa_sm {int dummy; } ;
struct wpa_eapol_ie_parse {int dummy; } ;

/* Variables and functions */

int   ieee80211w_set_keys(struct wpa_sm *sm,
                   struct wpa_eapol_ie_parse *ie)
{
     return 0;
}