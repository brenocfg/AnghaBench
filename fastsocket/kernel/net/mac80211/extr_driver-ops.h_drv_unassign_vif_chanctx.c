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
struct ieee80211_sub_if_data {int /*<<< orphan*/  vif; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct ieee80211_chanctx {int /*<<< orphan*/  conf; int /*<<< orphan*/  driver_present; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unassign_vif_chanctx ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  check_sdata_in_driver (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_drv_return_void (struct ieee80211_local*) ; 
 int /*<<< orphan*/  trace_drv_unassign_vif_chanctx (struct ieee80211_local*,struct ieee80211_sub_if_data*,struct ieee80211_chanctx*) ; 

__attribute__((used)) static inline void drv_unassign_vif_chanctx(struct ieee80211_local *local,
					    struct ieee80211_sub_if_data *sdata,
					    struct ieee80211_chanctx *ctx)
{
	check_sdata_in_driver(sdata);

	trace_drv_unassign_vif_chanctx(local, sdata, ctx);
	if (local->ops->unassign_vif_chanctx) {
		WARN_ON_ONCE(!ctx->driver_present);
		local->ops->unassign_vif_chanctx(&local->hw,
						 &sdata->vif,
						 &ctx->conf);
	}
	trace_drv_return_void(local);
}