#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_10__ {int basic_rates; } ;
struct ieee80211_vif {TYPE_5__ bss_conf; } ;
struct ar9170 {TYPE_4__* hw; } ;
struct TYPE_7__ {TYPE_1__* chan; } ;
struct TYPE_8__ {TYPE_2__ chandef; } ;
struct TYPE_9__ {TYPE_3__ conf; } ;
struct TYPE_6__ {scalar_t__ band; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR9170_MAC_REG_BASIC_RATE ; 
 int /*<<< orphan*/  AR9170_MAC_REG_MANDATORY_RATE ; 
 scalar_t__ IEEE80211_BAND_5GHZ ; 
 struct ieee80211_vif* carl9170_get_main_vif (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_regwrite (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  carl9170_regwrite_begin (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_regwrite_finish () ; 
 int carl9170_regwrite_result () ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int carl9170_set_mac_rates(struct ar9170 *ar)
{
	struct ieee80211_vif *vif;
	u32 basic, mandatory;

	rcu_read_lock();
	vif = carl9170_get_main_vif(ar);

	if (!vif) {
		rcu_read_unlock();
		return 0;
	}

	basic = (vif->bss_conf.basic_rates & 0xf);
	basic |= (vif->bss_conf.basic_rates & 0xff0) << 4;
	rcu_read_unlock();

	if (ar->hw->conf.chandef.chan->band == IEEE80211_BAND_5GHZ)
		mandatory = 0xff00; /* OFDM 6/9/12/18/24/36/48/54 */
	else
		mandatory = 0xff0f; /* OFDM (6/9../54) + CCK (1/2/5.5/11) */

	carl9170_regwrite_begin(ar);
	carl9170_regwrite(AR9170_MAC_REG_BASIC_RATE, basic);
	carl9170_regwrite(AR9170_MAC_REG_MANDATORY_RATE, mandatory);
	carl9170_regwrite_finish();

	return carl9170_regwrite_result();
}