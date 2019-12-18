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
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  aid; } ;
struct sta_info {TYPE_2__ sta; int /*<<< orphan*/ * ps_tx_buf; int /*<<< orphan*/  sdata; } ;
struct sk_buff {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ * vif; scalar_t__ jiffies; } ;
struct ieee80211_tx_info {int flags; TYPE_1__ control; } ;
struct ieee80211_tx_data {TYPE_5__* sdata; TYPE_3__* skb; struct ieee80211_local* local; struct sta_info* sta; } ;
struct ieee80211_local {scalar_t__ total_ps_buffered; int /*<<< orphan*/  sta_cleanup; int /*<<< orphan*/  hw; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
typedef  int /*<<< orphan*/  ieee80211_tx_result ;
struct TYPE_10__ {int /*<<< orphan*/  vif; } ;
struct TYPE_9__ {scalar_t__ data; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (TYPE_3__*) ; 
 int IEEE80211_TX_CTL_NO_PS_BUFFER ; 
 int IEEE80211_TX_INTFL_NEED_TXPROCESSING ; 
 scalar_t__ STA_INFO_CLEANUP_INTERVAL ; 
 scalar_t__ STA_MAX_TX_BUFFER ; 
 scalar_t__ TOTAL_MAX_TX_BUFFER ; 
 int /*<<< orphan*/  TX_CONTINUE ; 
 int /*<<< orphan*/  TX_QUEUED ; 
 int /*<<< orphan*/  WLAN_STA_PS_DRIVER ; 
 int /*<<< orphan*/  WLAN_STA_PS_STA ; 
 int /*<<< orphan*/  ieee80211_free_txskb (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  ieee80211_is_action (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_deauth (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_is_disassoc (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_mgmt (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ps_dbg (TYPE_5__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  purge_old_ps_buffers (struct ieee80211_local*) ; 
 int /*<<< orphan*/  round_jiffies (scalar_t__) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 int skb_get_queue_mapping (TYPE_3__*) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  sta_info_recalc_tim (struct sta_info*) ; 
 int test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_pending (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static ieee80211_tx_result
ieee80211_tx_h_unicast_ps_buf(struct ieee80211_tx_data *tx)
{
	struct sta_info *sta = tx->sta;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(tx->skb);
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)tx->skb->data;
	struct ieee80211_local *local = tx->local;

	if (unlikely(!sta))
		return TX_CONTINUE;

	if (unlikely((test_sta_flag(sta, WLAN_STA_PS_STA) ||
		      test_sta_flag(sta, WLAN_STA_PS_DRIVER)) &&
		     !(info->flags & IEEE80211_TX_CTL_NO_PS_BUFFER))) {
		int ac = skb_get_queue_mapping(tx->skb);

		/* only deauth, disassoc and action are bufferable MMPDUs */
		if (ieee80211_is_mgmt(hdr->frame_control) &&
		    !ieee80211_is_deauth(hdr->frame_control) &&
		    !ieee80211_is_disassoc(hdr->frame_control) &&
		    !ieee80211_is_action(hdr->frame_control)) {
			info->flags |= IEEE80211_TX_CTL_NO_PS_BUFFER;
			return TX_CONTINUE;
		}

		ps_dbg(sta->sdata, "STA %pM aid %d: PS buffer for AC %d\n",
		       sta->sta.addr, sta->sta.aid, ac);
		if (tx->local->total_ps_buffered >= TOTAL_MAX_TX_BUFFER)
			purge_old_ps_buffers(tx->local);
		if (skb_queue_len(&sta->ps_tx_buf[ac]) >= STA_MAX_TX_BUFFER) {
			struct sk_buff *old = skb_dequeue(&sta->ps_tx_buf[ac]);
			ps_dbg(tx->sdata,
			       "STA %pM TX buffer for AC %d full - dropping oldest frame\n",
			       sta->sta.addr, ac);
			ieee80211_free_txskb(&local->hw, old);
		} else
			tx->local->total_ps_buffered++;

		info->control.jiffies = jiffies;
		info->control.vif = &tx->sdata->vif;
		info->flags |= IEEE80211_TX_INTFL_NEED_TXPROCESSING;
		skb_queue_tail(&sta->ps_tx_buf[ac], tx->skb);

		if (!timer_pending(&local->sta_cleanup))
			mod_timer(&local->sta_cleanup,
				  round_jiffies(jiffies +
						STA_INFO_CLEANUP_INTERVAL));

		/*
		 * We queued up some frames, so the TIM bit might
		 * need to be set, recalculate it.
		 */
		sta_info_recalc_tim(sta);

		return TX_QUEUED;
	} else if (unlikely(test_sta_flag(sta, WLAN_STA_PS_STA))) {
		ps_dbg(tx->sdata,
		       "STA %pM in PS mode, but polling/in SP -> send frame\n",
		       sta->sta.addr);
	}

	return TX_CONTINUE;
}