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
struct TYPE_6__ {int /*<<< orphan*/  aid; int /*<<< orphan*/  addr; } ;
struct sta_info {TYPE_3__ sta; TYPE_2__* ps_tx_buf; TYPE_2__* tx_filtered; scalar_t__ driver_buffered_tids; struct ieee80211_sub_if_data* sdata; } ;
struct sk_buff_head {int dummy; } ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; } ;
struct TYPE_4__ {int flags; } ;
struct ieee80211_local {int total_ps_buffered; TYPE_1__ hw; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int BITS_TO_LONGS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int IEEE80211_HW_AP_LINK_PS ; 
 int IEEE80211_NUM_ACS ; 
 int /*<<< orphan*/  IEEE80211_NUM_TIDS ; 
 int /*<<< orphan*/  STA_NOTIFY_AWAKE ; 
 int /*<<< orphan*/  WLAN_STA_SP ; 
 int /*<<< orphan*/  clear_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_sta_ps_flags ; 
 int /*<<< orphan*/  drv_sta_notify (struct ieee80211_local*,struct ieee80211_sub_if_data*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  ieee80211_add_pending_skbs_fn (struct ieee80211_local*,struct sk_buff_head*,int /*<<< orphan*/ ,struct sta_info*) ; 
 int /*<<< orphan*/  ps_dbg (struct ieee80211_sub_if_data*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  skb_queue_head_init (struct sk_buff_head*) ; 
 int skb_queue_len (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_splice_tail_init (TYPE_2__*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sta_info_recalc_tim (struct sta_info*) ; 

void ieee80211_sta_ps_deliver_wakeup(struct sta_info *sta)
{
	struct ieee80211_sub_if_data *sdata = sta->sdata;
	struct ieee80211_local *local = sdata->local;
	struct sk_buff_head pending;
	int filtered = 0, buffered = 0, ac;
	unsigned long flags;

	clear_sta_flag(sta, WLAN_STA_SP);

	BUILD_BUG_ON(BITS_TO_LONGS(IEEE80211_NUM_TIDS) > 1);
	sta->driver_buffered_tids = 0;

	if (!(local->hw.flags & IEEE80211_HW_AP_LINK_PS))
		drv_sta_notify(local, sdata, STA_NOTIFY_AWAKE, &sta->sta);

	skb_queue_head_init(&pending);

	/* Send all buffered frames to the station */
	for (ac = 0; ac < IEEE80211_NUM_ACS; ac++) {
		int count = skb_queue_len(&pending), tmp;

		spin_lock_irqsave(&sta->tx_filtered[ac].lock, flags);
		skb_queue_splice_tail_init(&sta->tx_filtered[ac], &pending);
		spin_unlock_irqrestore(&sta->tx_filtered[ac].lock, flags);
		tmp = skb_queue_len(&pending);
		filtered += tmp - count;
		count = tmp;

		spin_lock_irqsave(&sta->ps_tx_buf[ac].lock, flags);
		skb_queue_splice_tail_init(&sta->ps_tx_buf[ac], &pending);
		spin_unlock_irqrestore(&sta->ps_tx_buf[ac].lock, flags);
		tmp = skb_queue_len(&pending);
		buffered += tmp - count;
	}

	ieee80211_add_pending_skbs_fn(local, &pending, clear_sta_ps_flags, sta);

	local->total_ps_buffered -= buffered;

	sta_info_recalc_tim(sta);

	ps_dbg(sdata,
	       "STA %pM aid %d sending %d filtered/%d PS frames since STA not sleeping anymore\n",
	       sta->sta.addr, sta->sta.aid, filtered, buffered);
}