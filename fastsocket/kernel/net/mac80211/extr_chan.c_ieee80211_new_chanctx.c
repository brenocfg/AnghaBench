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
typedef  scalar_t__ u32 ;
struct cfg80211_chan_def {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  radar_enabled; } ;
struct TYPE_5__ {TYPE_1__ conf; scalar_t__ chanctx_data_size; } ;
struct ieee80211_local {int /*<<< orphan*/  mtx; int /*<<< orphan*/  chanctx_list; struct cfg80211_chan_def _oper_chandef; int /*<<< orphan*/  use_chanctx; TYPE_2__ hw; int /*<<< orphan*/  chanctx_mtx; } ;
struct TYPE_6__ {int rx_chains_static; int rx_chains_dynamic; int /*<<< orphan*/  radar_enabled; struct cfg80211_chan_def def; } ;
struct ieee80211_chanctx {int mode; int /*<<< orphan*/  list; TYPE_3__ conf; } ;
typedef  enum ieee80211_chanctx_mode { ____Placeholder_ieee80211_chanctx_mode } ieee80211_chanctx_mode ;

/* Variables and functions */
 int ENOMEM ; 
 struct ieee80211_chanctx* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int drv_add_chanctx (struct ieee80211_local*,struct ieee80211_chanctx*) ; 
 int /*<<< orphan*/  ieee80211_hw_config (struct ieee80211_local*,scalar_t__) ; 
 scalar_t__ ieee80211_idle_off (struct ieee80211_local*) ; 
 int /*<<< orphan*/  ieee80211_is_radar_required (struct ieee80211_local*) ; 
 int /*<<< orphan*/  ieee80211_recalc_idle (struct ieee80211_local*) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_chanctx*) ; 
 struct ieee80211_chanctx* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ieee80211_chanctx *
ieee80211_new_chanctx(struct ieee80211_local *local,
		      const struct cfg80211_chan_def *chandef,
		      enum ieee80211_chanctx_mode mode)
{
	struct ieee80211_chanctx *ctx;
	u32 changed;
	int err;

	lockdep_assert_held(&local->chanctx_mtx);

	ctx = kzalloc(sizeof(*ctx) + local->hw.chanctx_data_size, GFP_KERNEL);
	if (!ctx)
		return ERR_PTR(-ENOMEM);

	ctx->conf.def = *chandef;
	ctx->conf.rx_chains_static = 1;
	ctx->conf.rx_chains_dynamic = 1;
	ctx->mode = mode;
	ctx->conf.radar_enabled = ieee80211_is_radar_required(local);
	if (!local->use_chanctx)
		local->hw.conf.radar_enabled = ctx->conf.radar_enabled;

	/* acquire mutex to prevent idle from changing */
	mutex_lock(&local->mtx);
	/* turn idle off *before* setting channel -- some drivers need that */
	changed = ieee80211_idle_off(local);
	if (changed)
		ieee80211_hw_config(local, changed);

	if (!local->use_chanctx) {
		local->_oper_chandef = *chandef;
		ieee80211_hw_config(local, 0);
	} else {
		err = drv_add_chanctx(local, ctx);
		if (err) {
			kfree(ctx);
			ctx = ERR_PTR(err);

			ieee80211_recalc_idle(local);
			goto out;
		}
	}

	/* and keep the mutex held until the new chanctx is on the list */
	list_add_rcu(&ctx->list, &local->chanctx_list);

 out:
	mutex_unlock(&local->mtx);

	return ctx;
}