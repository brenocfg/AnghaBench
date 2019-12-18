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
typedef  int u8 ;
struct TYPE_4__ {int /*<<< orphan*/  chanctx_conf; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  flags; TYPE_1__ vif; } ;
struct TYPE_6__ {TYPE_2__* chan; } ;
struct ieee80211_chanctx_conf {TYPE_3__ def; } ;
struct TYPE_5__ {scalar_t__ band; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 int /*<<< orphan*/  IEEE80211_SDATA_OPERATING_GMODE ; 
 int /*<<< orphan*/  ieee80211_set_wmm_default (struct ieee80211_sub_if_data*,int) ; 
 struct ieee80211_chanctx_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void ieee80211_sta_def_wmm_params(struct ieee80211_sub_if_data *sdata,
				  const size_t supp_rates_len,
				  const u8 *supp_rates)
{
	struct ieee80211_chanctx_conf *chanctx_conf;
	int i, have_higher_than_11mbit = 0;

	/* cf. IEEE 802.11 9.2.12 */
	for (i = 0; i < supp_rates_len; i++)
		if ((supp_rates[i] & 0x7f) * 5 > 110)
			have_higher_than_11mbit = 1;

	rcu_read_lock();
	chanctx_conf = rcu_dereference(sdata->vif.chanctx_conf);

	if (chanctx_conf &&
	    chanctx_conf->def.chan->band == IEEE80211_BAND_2GHZ &&
	    have_higher_than_11mbit)
		sdata->flags |= IEEE80211_SDATA_OPERATING_GMODE;
	else
		sdata->flags &= ~IEEE80211_SDATA_OPERATING_GMODE;
	rcu_read_unlock();

	ieee80211_set_wmm_default(sdata, true);
}