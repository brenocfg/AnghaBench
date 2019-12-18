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
typedef  int /*<<< orphan*/  u32 ;
struct ieee80211_local {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct ieee80211_chanctx {int /*<<< orphan*/  conf; int /*<<< orphan*/  driver_present; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* change_chanctx ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_drv_change_chanctx (struct ieee80211_local*,struct ieee80211_chanctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_drv_return_void (struct ieee80211_local*) ; 

__attribute__((used)) static inline void drv_change_chanctx(struct ieee80211_local *local,
				      struct ieee80211_chanctx *ctx,
				      u32 changed)
{
	trace_drv_change_chanctx(local, ctx, changed);
	if (local->ops->change_chanctx) {
		WARN_ON_ONCE(!ctx->driver_present);
		local->ops->change_chanctx(&local->hw, &ctx->conf, changed);
	}
	trace_drv_return_void(local);
}