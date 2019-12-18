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
struct ieee80211_sta {int dummy; } ;
struct sta_info {void* rate_ctrl_priv; struct ieee80211_sta sta; struct rate_control_ref* rate_ctrl; } ;
struct rate_control_ref {int /*<<< orphan*/  priv; TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_sta ) (int /*<<< orphan*/ ,struct ieee80211_sta*,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct ieee80211_sta*,void*) ; 

__attribute__((used)) static inline void rate_control_free_sta(struct sta_info *sta)
{
	struct rate_control_ref *ref = sta->rate_ctrl;
	struct ieee80211_sta *ista = &sta->sta;
	void *priv_sta = sta->rate_ctrl_priv;

	ref->ops->free_sta(ref->priv, ista, priv_sta);
}