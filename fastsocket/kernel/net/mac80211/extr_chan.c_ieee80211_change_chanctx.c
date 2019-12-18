#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cfg80211_chan_def {int dummy; } ;
struct ieee80211_local {struct cfg80211_chan_def _oper_chandef; int /*<<< orphan*/  use_chanctx; } ;
struct TYPE_2__ {struct cfg80211_chan_def def; } ;
struct ieee80211_chanctx {TYPE_1__ conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CHANCTX_CHANGE_WIDTH ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  cfg80211_chandef_compatible (struct cfg80211_chan_def*,struct cfg80211_chan_def const*) ; 
 scalar_t__ cfg80211_chandef_identical (struct cfg80211_chan_def*,struct cfg80211_chan_def const*) ; 
 int /*<<< orphan*/  drv_change_chanctx (struct ieee80211_local*,struct ieee80211_chanctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_hw_config (struct ieee80211_local*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ieee80211_change_chanctx(struct ieee80211_local *local,
				     struct ieee80211_chanctx *ctx,
				     const struct cfg80211_chan_def *chandef)
{
	if (cfg80211_chandef_identical(&ctx->conf.def, chandef))
		return;

	WARN_ON(!cfg80211_chandef_compatible(&ctx->conf.def, chandef));

	ctx->conf.def = *chandef;
	drv_change_chanctx(local, ctx, IEEE80211_CHANCTX_CHANGE_WIDTH);

	if (!local->use_chanctx) {
		local->_oper_chandef = *chandef;
		ieee80211_hw_config(local, 0);
	}
}