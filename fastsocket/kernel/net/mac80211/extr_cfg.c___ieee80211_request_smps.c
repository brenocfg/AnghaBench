#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_11__ {int req_smps; scalar_t__ powersave; TYPE_4__* associated; int /*<<< orphan*/  mtx; } ;
struct TYPE_12__ {TYPE_5__ mgd; } ;
struct TYPE_7__ {scalar_t__ width; } ;
struct TYPE_8__ {TYPE_1__ chandef; } ;
struct TYPE_9__ {TYPE_2__ bss_conf; } ;
struct ieee80211_sub_if_data {TYPE_6__ u; TYPE_3__ vif; } ;
typedef  enum ieee80211_smps_mode { ____Placeholder_ieee80211_smps_mode } ieee80211_smps_mode ;
struct TYPE_10__ {int /*<<< orphan*/ * bssid; } ;

/* Variables and functions */
 int IEEE80211_SMPS_AUTOMATIC ; 
 int IEEE80211_SMPS_DYNAMIC ; 
 int IEEE80211_SMPS_OFF ; 
 scalar_t__ NL80211_CHAN_WIDTH_20_NOHT ; 
 int ieee80211_send_smps_action (struct ieee80211_sub_if_data*,int,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

int __ieee80211_request_smps(struct ieee80211_sub_if_data *sdata,
			     enum ieee80211_smps_mode smps_mode)
{
	const u8 *ap;
	enum ieee80211_smps_mode old_req;
	int err;

	lockdep_assert_held(&sdata->u.mgd.mtx);

	old_req = sdata->u.mgd.req_smps;
	sdata->u.mgd.req_smps = smps_mode;

	if (old_req == smps_mode &&
	    smps_mode != IEEE80211_SMPS_AUTOMATIC)
		return 0;

	/*
	 * If not associated, or current association is not an HT
	 * association, there's no need to do anything, just store
	 * the new value until we associate.
	 */
	if (!sdata->u.mgd.associated ||
	    sdata->vif.bss_conf.chandef.width == NL80211_CHAN_WIDTH_20_NOHT)
		return 0;

	ap = sdata->u.mgd.associated->bssid;

	if (smps_mode == IEEE80211_SMPS_AUTOMATIC) {
		if (sdata->u.mgd.powersave)
			smps_mode = IEEE80211_SMPS_DYNAMIC;
		else
			smps_mode = IEEE80211_SMPS_OFF;
	}

	/* send SM PS frame to AP */
	err = ieee80211_send_smps_action(sdata, smps_mode,
					 ap, ap);
	if (err)
		sdata->u.mgd.req_smps = old_req;

	return err;
}