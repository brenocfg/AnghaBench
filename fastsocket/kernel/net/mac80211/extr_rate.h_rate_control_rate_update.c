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
struct ieee80211_sta {int dummy; } ;
struct sta_info {struct ieee80211_sta sta; int /*<<< orphan*/  sdata; void* rate_ctrl_priv; } ;
struct rate_control_ref {int /*<<< orphan*/  priv; TYPE_1__* ops; } ;
struct ieee80211_supported_band {int dummy; } ;
struct ieee80211_local {struct rate_control_ref* rate_ctrl; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* rate_update ) (int /*<<< orphan*/ ,struct ieee80211_supported_band*,struct ieee80211_sta*,void*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  drv_sta_rc_update (struct ieee80211_local*,int /*<<< orphan*/ ,struct ieee80211_sta*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct ieee80211_supported_band*,struct ieee80211_sta*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rate_control_rate_update(struct ieee80211_local *local,
				    struct ieee80211_supported_band *sband,
				    struct sta_info *sta, u32 changed)
{
	struct rate_control_ref *ref = local->rate_ctrl;
	struct ieee80211_sta *ista = &sta->sta;
	void *priv_sta = sta->rate_ctrl_priv;

	if (ref && ref->ops->rate_update)
		ref->ops->rate_update(ref->priv, sband, ista,
				      priv_sta, changed);
	drv_sta_rc_update(local, sta->sdata, &sta->sta, changed);
}