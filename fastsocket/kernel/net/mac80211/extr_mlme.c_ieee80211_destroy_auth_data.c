#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct ieee80211_mgd_auth_data* auth_data; scalar_t__ flags; int /*<<< orphan*/  bssid; int /*<<< orphan*/  mtx; } ;
struct TYPE_8__ {TYPE_4__ mgd; } ;
struct ieee80211_sub_if_data {TYPE_3__ u; TYPE_2__* local; } ;
struct ieee80211_mgd_auth_data {TYPE_5__* bss; } ;
struct TYPE_10__ {int /*<<< orphan*/  bssid; } ;
struct TYPE_6__ {int /*<<< orphan*/  wiphy; } ;
struct TYPE_7__ {TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSS_CHANGED_BSSID ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  cfg80211_put_bss (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  ieee80211_bss_info_change_notify (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_vif_release_channel (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_mgd_auth_data*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sta_info_destroy_addr (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ieee80211_destroy_auth_data(struct ieee80211_sub_if_data *sdata,
					bool assoc)
{
	struct ieee80211_mgd_auth_data *auth_data = sdata->u.mgd.auth_data;

	lockdep_assert_held(&sdata->u.mgd.mtx);

	if (!assoc) {
		sta_info_destroy_addr(sdata, auth_data->bss->bssid);

		memset(sdata->u.mgd.bssid, 0, ETH_ALEN);
		ieee80211_bss_info_change_notify(sdata, BSS_CHANGED_BSSID);
		sdata->u.mgd.flags = 0;
		ieee80211_vif_release_channel(sdata);
	}

	cfg80211_put_bss(sdata->local->hw.wiphy, auth_data->bss);
	kfree(auth_data);
	sdata->u.mgd.auth_data = NULL;
}