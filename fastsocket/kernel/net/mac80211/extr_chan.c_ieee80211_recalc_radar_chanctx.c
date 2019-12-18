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
struct TYPE_4__ {int radar_enabled; } ;
struct TYPE_5__ {TYPE_1__ conf; } ;
struct ieee80211_local {int radar_detect_enabled; TYPE_2__ hw; int /*<<< orphan*/  use_chanctx; int /*<<< orphan*/  chanctx_mtx; } ;
struct TYPE_6__ {int radar_enabled; } ;
struct ieee80211_chanctx {TYPE_3__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CHANCTX_CHANGE_RADAR ; 
 int /*<<< orphan*/  IEEE80211_CONF_CHANGE_CHANNEL ; 
 int /*<<< orphan*/  drv_change_chanctx (struct ieee80211_local*,struct ieee80211_chanctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_hw_config (struct ieee80211_local*,int /*<<< orphan*/ ) ; 
 int ieee80211_is_radar_required (struct ieee80211_local*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void ieee80211_recalc_radar_chanctx(struct ieee80211_local *local,
				    struct ieee80211_chanctx *chanctx)
{
	bool radar_enabled;

	lockdep_assert_held(&local->chanctx_mtx);

	radar_enabled = ieee80211_is_radar_required(local);

	if (radar_enabled == chanctx->conf.radar_enabled)
		return;

	chanctx->conf.radar_enabled = radar_enabled;
	local->radar_detect_enabled = chanctx->conf.radar_enabled;

	if (!local->use_chanctx) {
		local->hw.conf.radar_enabled = chanctx->conf.radar_enabled;
		ieee80211_hw_config(local, IEEE80211_CONF_CHANGE_CHANNEL);
	}

	drv_change_chanctx(local, chanctx, IEEE80211_CHANCTX_CHANGE_RADAR);
}