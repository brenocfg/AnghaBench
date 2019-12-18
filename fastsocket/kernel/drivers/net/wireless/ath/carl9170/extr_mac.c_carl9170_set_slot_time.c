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
struct TYPE_10__ {scalar_t__ use_short_slot; } ;
struct ieee80211_vif {TYPE_5__ bss_conf; } ;
struct ar9170 {TYPE_4__* hw; } ;
struct TYPE_7__ {TYPE_1__* chan; } ;
struct TYPE_8__ {TYPE_2__ chandef; } ;
struct TYPE_9__ {TYPE_3__ conf; } ;
struct TYPE_6__ {scalar_t__ band; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR9170_MAC_REG_SLOT_TIME ; 
 scalar_t__ IEEE80211_BAND_5GHZ ; 
 struct ieee80211_vif* carl9170_get_main_vif (struct ar9170*) ; 
 int carl9170_write_reg (struct ar9170*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

int carl9170_set_slot_time(struct ar9170 *ar)
{
	struct ieee80211_vif *vif;
	u32 slottime = 20;

	rcu_read_lock();
	vif = carl9170_get_main_vif(ar);
	if (!vif) {
		rcu_read_unlock();
		return 0;
	}

	if ((ar->hw->conf.chandef.chan->band == IEEE80211_BAND_5GHZ) ||
	    vif->bss_conf.use_short_slot)
		slottime = 9;

	rcu_read_unlock();

	return carl9170_write_reg(ar, AR9170_MAC_REG_SLOT_TIME,
				  slottime << 10);
}