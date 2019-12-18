#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int use_4addr; } ;
struct TYPE_4__ {TYPE_1__ mgd; } ;
struct ieee80211_sub_if_data {TYPE_2__ u; scalar_t__ drop_unencrypted; int /*<<< orphan*/  vif; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int NL80211_IFTYPE_STATION ; 
 int ieee80211_runtime_change_iftype (struct ieee80211_sub_if_data*,int) ; 
 scalar_t__ ieee80211_sdata_running (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_setup_sdata (struct ieee80211_sub_if_data*,int) ; 
 int /*<<< orphan*/  ieee80211_teardown_sdata (struct ieee80211_sub_if_data*) ; 
 int ieee80211_vif_type_p2p (int /*<<< orphan*/ *) ; 

int ieee80211_if_change_type(struct ieee80211_sub_if_data *sdata,
			     enum nl80211_iftype type)
{
	int ret;

	ASSERT_RTNL();

	if (type == ieee80211_vif_type_p2p(&sdata->vif))
		return 0;

	if (ieee80211_sdata_running(sdata)) {
		ret = ieee80211_runtime_change_iftype(sdata, type);
		if (ret)
			return ret;
	} else {
		/* Purge and reset type-dependent state. */
		ieee80211_teardown_sdata(sdata);
		ieee80211_setup_sdata(sdata, type);
	}

	/* reset some values that shouldn't be kept across type changes */
	sdata->drop_unencrypted = 0;
	if (type == NL80211_IFTYPE_STATION)
		sdata->u.mgd.use_4addr = false;

	return 0;
}