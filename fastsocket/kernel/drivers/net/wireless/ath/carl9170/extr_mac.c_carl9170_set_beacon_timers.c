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
typedef  int u32 ;
struct TYPE_4__ {int beacon_int; int dtim_period; } ;
struct ieee80211_vif {int type; TYPE_1__ bss_conf; scalar_t__ drv_priv; } ;
struct carl9170_vif_info {scalar_t__ enable_beacon; } ;
struct ar9170 {int beacon_enabled; int global_beacon_int; int global_pretbtt; TYPE_3__* hw; } ;
struct TYPE_5__ {int ps_dtim_period; } ;
struct TYPE_6__ {TYPE_2__ conf; } ;

/* Variables and functions */
 int AR9170_MAC_BCN_AP_MODE ; 
 int /*<<< orphan*/  AR9170_MAC_BCN_DTIM ; 
 int AR9170_MAC_BCN_IBSS_MODE ; 
 int /*<<< orphan*/  AR9170_MAC_BCN_PERIOD ; 
 int AR9170_MAC_BCN_PWR_MGT ; 
 int AR9170_MAC_BCN_STA_PS ; 
 int /*<<< orphan*/  AR9170_MAC_PRETBTT ; 
 int /*<<< orphan*/  AR9170_MAC_PRETBTT2 ; 
 int /*<<< orphan*/  AR9170_MAC_REG_BCN_PERIOD ; 
 int /*<<< orphan*/  AR9170_MAC_REG_PRETBTT ; 
 int CARL9170_PRETBTT_KUS ; 
 int ERANGE ; 
#define  NL80211_IFTYPE_ADHOC 130 
#define  NL80211_IFTYPE_AP 129 
#define  NL80211_IFTYPE_MESH_POINT 128 
 int NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  SET_VAL (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct ieee80211_vif* carl9170_get_main_vif (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_regwrite (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  carl9170_regwrite_begin (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_regwrite_finish () ; 
 int carl9170_regwrite_result () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int carl9170_set_beacon_timers(struct ar9170 *ar)
{
	struct ieee80211_vif *vif;
	u32 v = 0;
	u32 pretbtt = 0;

	rcu_read_lock();
	vif = carl9170_get_main_vif(ar);

	if (vif) {
		struct carl9170_vif_info *mvif;
		mvif = (void *) vif->drv_priv;

		if (mvif->enable_beacon && !WARN_ON(!ar->beacon_enabled)) {
			ar->global_beacon_int = vif->bss_conf.beacon_int /
						ar->beacon_enabled;

			SET_VAL(AR9170_MAC_BCN_DTIM, v,
				vif->bss_conf.dtim_period);

			switch (vif->type) {
			case NL80211_IFTYPE_MESH_POINT:
			case NL80211_IFTYPE_ADHOC:
				v |= AR9170_MAC_BCN_IBSS_MODE;
				break;
			case NL80211_IFTYPE_AP:
				v |= AR9170_MAC_BCN_AP_MODE;
				break;
			default:
				WARN_ON_ONCE(1);
				break;
			}
		} else if (vif->type == NL80211_IFTYPE_STATION) {
			ar->global_beacon_int = vif->bss_conf.beacon_int;

			SET_VAL(AR9170_MAC_BCN_DTIM, v,
				ar->hw->conf.ps_dtim_period);

			v |= AR9170_MAC_BCN_STA_PS |
			     AR9170_MAC_BCN_PWR_MGT;
		}

		if (ar->global_beacon_int) {
			if (ar->global_beacon_int < 15) {
				rcu_read_unlock();
				return -ERANGE;
			}

			ar->global_pretbtt = ar->global_beacon_int -
					CARL9170_PRETBTT_KUS;
		} else {
			ar->global_pretbtt = 0;
		}
	} else {
		ar->global_beacon_int = 0;
		ar->global_pretbtt = 0;
	}

	rcu_read_unlock();

	SET_VAL(AR9170_MAC_BCN_PERIOD, v, ar->global_beacon_int);
	SET_VAL(AR9170_MAC_PRETBTT, pretbtt, ar->global_pretbtt);
	SET_VAL(AR9170_MAC_PRETBTT2, pretbtt, ar->global_pretbtt);

	carl9170_regwrite_begin(ar);
	carl9170_regwrite(AR9170_MAC_REG_PRETBTT, pretbtt);
	carl9170_regwrite(AR9170_MAC_REG_BCN_PERIOD, v);
	carl9170_regwrite_finish();
	return carl9170_regwrite_result();
}