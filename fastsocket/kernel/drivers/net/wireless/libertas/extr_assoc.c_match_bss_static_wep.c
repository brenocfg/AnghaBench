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
struct lbs_802_11_security {int /*<<< orphan*/  WPA2enabled; int /*<<< orphan*/  WPAenabled; scalar_t__ wep_enabled; } ;
struct bss_descriptor {int capability; } ;

/* Variables and functions */
 int WLAN_CAPABILITY_PRIVACY ; 

__attribute__((used)) static inline int match_bss_static_wep(struct lbs_802_11_security *secinfo,
				       struct bss_descriptor *match_bss)
{
	if (secinfo->wep_enabled && !secinfo->WPAenabled
	    && !secinfo->WPA2enabled
	    && (match_bss->capability & WLAN_CAPABILITY_PRIVACY))
		return 1;
	else
		return 0;
}