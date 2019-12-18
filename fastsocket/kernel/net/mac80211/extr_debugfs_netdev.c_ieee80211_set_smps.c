#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  mtx; } ;
struct TYPE_7__ {TYPE_2__ mgd; } ;
struct TYPE_5__ {scalar_t__ type; } ;
struct ieee80211_sub_if_data {TYPE_3__ u; TYPE_1__ vif; struct ieee80211_local* local; } ;
struct TYPE_8__ {int flags; } ;
struct ieee80211_local {TYPE_4__ hw; } ;
typedef  enum ieee80211_smps_mode { ____Placeholder_ieee80211_smps_mode } ieee80211_smps_mode ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int IEEE80211_HW_SUPPORTS_DYNAMIC_SMPS ; 
 int IEEE80211_HW_SUPPORTS_STATIC_SMPS ; 
 int IEEE80211_SMPS_AUTOMATIC ; 
 int IEEE80211_SMPS_DYNAMIC ; 
 int IEEE80211_SMPS_STATIC ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int __ieee80211_request_smps (struct ieee80211_sub_if_data*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ieee80211_set_smps(struct ieee80211_sub_if_data *sdata,
			      enum ieee80211_smps_mode smps_mode)
{
	struct ieee80211_local *local = sdata->local;
	int err;

	if (!(local->hw.flags & IEEE80211_HW_SUPPORTS_STATIC_SMPS) &&
	    smps_mode == IEEE80211_SMPS_STATIC)
		return -EINVAL;

	/* auto should be dynamic if in PS mode */
	if (!(local->hw.flags & IEEE80211_HW_SUPPORTS_DYNAMIC_SMPS) &&
	    (smps_mode == IEEE80211_SMPS_DYNAMIC ||
	     smps_mode == IEEE80211_SMPS_AUTOMATIC))
		return -EINVAL;

	/* supported only on managed interfaces for now */
	if (sdata->vif.type != NL80211_IFTYPE_STATION)
		return -EOPNOTSUPP;

	mutex_lock(&sdata->u.mgd.mtx);
	err = __ieee80211_request_smps(sdata, smps_mode);
	mutex_unlock(&sdata->u.mgd.mtx);

	return err;
}