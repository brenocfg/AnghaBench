#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_tx_queue_params {int cw_max; int cw_min; int txop; int aifs; int uapsd; } ;
struct TYPE_11__ {int qos; } ;
struct TYPE_12__ {scalar_t__ type; TYPE_5__ bss_conf; int /*<<< orphan*/  chanctx_conf; } ;
struct ieee80211_sub_if_data {int flags; TYPE_6__ vif; struct ieee80211_tx_queue_params* tx_conf; struct ieee80211_local* local; } ;
struct TYPE_8__ {int queues; } ;
struct ieee80211_local {TYPE_2__ hw; TYPE_1__* ops; } ;
struct TYPE_10__ {TYPE_3__* chan; } ;
struct ieee80211_chanctx_conf {TYPE_4__ def; } ;
typedef  int /*<<< orphan*/  qparam ;
struct TYPE_9__ {scalar_t__ band; } ;
struct TYPE_7__ {int /*<<< orphan*/  conf_tx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSS_CHANGED_QOS ; 
#define  IEEE80211_AC_BE 131 
#define  IEEE80211_AC_BK 130 
#define  IEEE80211_AC_VI 129 
#define  IEEE80211_AC_VO 128 
 scalar_t__ IEEE80211_BAND_2GHZ ; 
 int IEEE80211_NUM_ACS ; 
 int IEEE80211_SDATA_OPERATING_GMODE ; 
 scalar_t__ NL80211_IFTYPE_MONITOR ; 
 scalar_t__ NL80211_IFTYPE_P2P_DEVICE ; 
 scalar_t__ NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  drv_conf_tx (struct ieee80211_local*,struct ieee80211_sub_if_data*,int,struct ieee80211_tx_queue_params*) ; 
 int /*<<< orphan*/  ieee80211_bss_info_change_notify (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ieee80211_tx_queue_params*,int /*<<< orphan*/ ,int) ; 
 struct ieee80211_chanctx_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void ieee80211_set_wmm_default(struct ieee80211_sub_if_data *sdata,
			       bool bss_notify)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_tx_queue_params qparam;
	struct ieee80211_chanctx_conf *chanctx_conf;
	int ac;
	bool use_11b, enable_qos;
	int aCWmin, aCWmax;

	if (!local->ops->conf_tx)
		return;

	if (local->hw.queues < IEEE80211_NUM_ACS)
		return;

	memset(&qparam, 0, sizeof(qparam));

	rcu_read_lock();
	chanctx_conf = rcu_dereference(sdata->vif.chanctx_conf);
	use_11b = (chanctx_conf &&
		   chanctx_conf->def.chan->band == IEEE80211_BAND_2GHZ) &&
		 !(sdata->flags & IEEE80211_SDATA_OPERATING_GMODE);
	rcu_read_unlock();

	/*
	 * By default disable QoS in STA mode for old access points, which do
	 * not support 802.11e. New APs will provide proper queue parameters,
	 * that we will configure later.
	 */
	enable_qos = (sdata->vif.type != NL80211_IFTYPE_STATION);

	for (ac = 0; ac < IEEE80211_NUM_ACS; ac++) {
		/* Set defaults according to 802.11-2007 Table 7-37 */
		aCWmax = 1023;
		if (use_11b)
			aCWmin = 31;
		else
			aCWmin = 15;

		if (enable_qos) {
			switch (ac) {
			case IEEE80211_AC_BK:
				qparam.cw_max = aCWmax;
				qparam.cw_min = aCWmin;
				qparam.txop = 0;
				qparam.aifs = 7;
				break;
			/* never happens but let's not leave undefined */
			default:
			case IEEE80211_AC_BE:
				qparam.cw_max = aCWmax;
				qparam.cw_min = aCWmin;
				qparam.txop = 0;
				qparam.aifs = 3;
				break;
			case IEEE80211_AC_VI:
				qparam.cw_max = aCWmin;
				qparam.cw_min = (aCWmin + 1) / 2 - 1;
				if (use_11b)
					qparam.txop = 6016/32;
				else
					qparam.txop = 3008/32;
				qparam.aifs = 2;
				break;
			case IEEE80211_AC_VO:
				qparam.cw_max = (aCWmin + 1) / 2 - 1;
				qparam.cw_min = (aCWmin + 1) / 4 - 1;
				if (use_11b)
					qparam.txop = 3264/32;
				else
					qparam.txop = 1504/32;
				qparam.aifs = 2;
				break;
			}
		} else {
			/* Confiure old 802.11b/g medium access rules. */
			qparam.cw_max = aCWmax;
			qparam.cw_min = aCWmin;
			qparam.txop = 0;
			qparam.aifs = 2;
		}

		qparam.uapsd = false;

		sdata->tx_conf[ac] = qparam;
		drv_conf_tx(local, sdata, ac, &qparam);
	}

	if (sdata->vif.type != NL80211_IFTYPE_MONITOR &&
	    sdata->vif.type != NL80211_IFTYPE_P2P_DEVICE) {
		sdata->vif.bss_conf.qos = enable_qos;
		if (bss_notify)
			ieee80211_bss_info_change_notify(sdata,
							 BSS_CHANGED_QOS);
	}
}