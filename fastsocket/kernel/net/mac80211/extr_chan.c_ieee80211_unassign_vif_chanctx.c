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
struct TYPE_3__ {int idle; } ;
struct TYPE_4__ {scalar_t__ type; TYPE_1__ bss_conf; int /*<<< orphan*/  chanctx_conf; } ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; TYPE_2__ vif; } ;
struct ieee80211_local {int /*<<< orphan*/  chanctx_mtx; } ;
struct ieee80211_chanctx {scalar_t__ refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSS_CHANGED_IDLE ; 
 scalar_t__ NL80211_IFTYPE_MONITOR ; 
 scalar_t__ NL80211_IFTYPE_P2P_DEVICE ; 
 int /*<<< orphan*/  drv_unassign_vif_chanctx (struct ieee80211_local*,struct ieee80211_sub_if_data*,struct ieee80211_chanctx*) ; 
 int /*<<< orphan*/  ieee80211_bss_info_change_notify (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_recalc_chanctx_chantype (struct ieee80211_local*,struct ieee80211_chanctx*) ; 
 int /*<<< orphan*/  ieee80211_recalc_radar_chanctx (struct ieee80211_local*,struct ieee80211_chanctx*) ; 
 int /*<<< orphan*/  ieee80211_recalc_smps_chanctx (struct ieee80211_local*,struct ieee80211_chanctx*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ieee80211_unassign_vif_chanctx(struct ieee80211_sub_if_data *sdata,
					   struct ieee80211_chanctx *ctx)
{
	struct ieee80211_local *local = sdata->local;

	lockdep_assert_held(&local->chanctx_mtx);

	ctx->refcount--;
	rcu_assign_pointer(sdata->vif.chanctx_conf, NULL);

	sdata->vif.bss_conf.idle = true;

	if (sdata->vif.type != NL80211_IFTYPE_P2P_DEVICE &&
	    sdata->vif.type != NL80211_IFTYPE_MONITOR)
		ieee80211_bss_info_change_notify(sdata, BSS_CHANGED_IDLE);

	drv_unassign_vif_chanctx(local, sdata, ctx);

	if (ctx->refcount > 0) {
		ieee80211_recalc_chanctx_chantype(sdata->local, ctx);
		ieee80211_recalc_smps_chanctx(local, ctx);
		ieee80211_recalc_radar_chanctx(local, ctx);
	}
}