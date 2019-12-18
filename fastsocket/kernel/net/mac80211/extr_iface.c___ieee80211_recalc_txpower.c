#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int txpower; } ;
struct TYPE_8__ {TYPE_3__ bss_conf; int /*<<< orphan*/  chanctx_conf; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  local; TYPE_4__ vif; int /*<<< orphan*/  ap_power_level; int /*<<< orphan*/  user_power_level; } ;
struct TYPE_6__ {TYPE_1__* chan; } ;
struct ieee80211_chanctx_conf {TYPE_2__ def; } ;
struct TYPE_5__ {int max_power; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_UNSET_POWER_LEVEL ; 
 int /*<<< orphan*/  ieee80211_hw_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 struct ieee80211_chanctx_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

bool __ieee80211_recalc_txpower(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_chanctx_conf *chanctx_conf;
	int power;

	rcu_read_lock();
	chanctx_conf = rcu_dereference(sdata->vif.chanctx_conf);
	if (!chanctx_conf) {
		rcu_read_unlock();
		return false;
	}

	power = chanctx_conf->def.chan->max_power;
	rcu_read_unlock();

	if (sdata->user_power_level != IEEE80211_UNSET_POWER_LEVEL)
		power = min(power, sdata->user_power_level);

	if (sdata->ap_power_level != IEEE80211_UNSET_POWER_LEVEL)
		power = min(power, sdata->ap_power_level);

	if (power != sdata->vif.bss_conf.txpower) {
		sdata->vif.bss_conf.txpower = power;
		ieee80211_hw_config(sdata->local, 0);
		return true;
	}

	return false;
}