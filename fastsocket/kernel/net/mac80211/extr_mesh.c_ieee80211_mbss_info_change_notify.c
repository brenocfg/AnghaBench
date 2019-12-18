#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  mesh; } ;
struct TYPE_4__ {scalar_t__ enable_beacon; } ;
struct TYPE_5__ {TYPE_1__ bss_conf; } ;
struct ieee80211_sub_if_data {TYPE_3__ u; TYPE_2__ vif; } ;

/* Variables and functions */
 int BSS_CHANGED_BASIC_RATES ; 
 int BSS_CHANGED_BEACON ; 
 int BSS_CHANGED_BEACON_INT ; 
 int BSS_CHANGED_HT ; 
 int /*<<< orphan*/  ieee80211_bss_info_change_notify (struct ieee80211_sub_if_data*,int) ; 
 scalar_t__ ieee80211_mesh_rebuild_beacon (int /*<<< orphan*/ *) ; 

void ieee80211_mbss_info_change_notify(struct ieee80211_sub_if_data *sdata,
				       u32 changed)
{
	if (sdata->vif.bss_conf.enable_beacon &&
	    (changed & (BSS_CHANGED_BEACON |
			BSS_CHANGED_HT |
			BSS_CHANGED_BASIC_RATES |
			BSS_CHANGED_BEACON_INT)))
		if (ieee80211_mesh_rebuild_beacon(&sdata->u.mesh))
			return;
	ieee80211_bss_info_change_notify(sdata, changed);
}