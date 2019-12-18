#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct sta_info {unsigned long driver_buffered_tids; struct sk_buff_head* ps_tx_buf; struct sk_buff_head* tx_filtered; struct ieee80211_sub_if_data* sdata; } ;
struct sk_buff_head {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;
struct ieee80211_tx_info {int flags; } ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  total_ps_buffered; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;
typedef  enum ieee80211_frame_release_type { ____Placeholder_ieee80211_frame_release_type } ieee80211_frame_release_type ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  IEEE80211_FCTL_MOREDATA ; 
 int IEEE80211_FRAME_RELEASE_PSPOLL ; 
 int IEEE80211_FRAME_RELEASE_UAPSD ; 
 int IEEE80211_NUM_ACS ; 
 int IEEE80211_QOS_CTL_EOSP ; 
 int IEEE80211_QOS_CTL_TID_MASK ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTL_NO_PS_BUFFER ; 
 int IEEE80211_TX_CTL_REQ_TX_STATUS ; 
 int IEEE80211_TX_STATUS_EOSP ; 
 int /*<<< orphan*/  WLAN_STA_SP ; 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_tail (struct sk_buff_head*,struct sk_buff*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv_allow_buffered_frames (struct ieee80211_local*,struct sta_info*,int,int,int,int) ; 
 int /*<<< orphan*/  drv_release_buffered_frames (struct ieee80211_local*,struct sta_info*,unsigned long,int,int,int) ; 
 int ffs (int) ; 
 int hweight16 (unsigned long) ; 
 int /*<<< orphan*/  ieee80211_add_pending_skbs (struct ieee80211_local*,struct sk_buff_head*) ; 
 int* ieee80211_get_qos_ctl (struct ieee80211_hdr*) ; 
 scalar_t__ ieee80211_is_data_qos (int /*<<< orphan*/ ) ; 
 scalar_t__ ieee80211_is_qos_nullfunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_send_null_response (struct ieee80211_sub_if_data*,struct sta_info*,int,int) ; 
 unsigned long ieee80211_tids_for_ac (int) ; 
 int /*<<< orphan*/  set_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (struct sk_buff_head*) ; 
 scalar_t__ skb_queue_empty (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  sta_info_recalc_tim (struct sta_info*) ; 

__attribute__((used)) static void
ieee80211_sta_ps_deliver_response(struct sta_info *sta,
				  int n_frames, u8 ignored_acs,
				  enum ieee80211_frame_release_type reason)
{
	struct ieee80211_sub_if_data *sdata = sta->sdata;
	struct ieee80211_local *local = sdata->local;
	bool found = false;
	bool more_data = false;
	int ac;
	unsigned long driver_release_tids = 0;
	struct sk_buff_head frames;

	/* Service or PS-Poll period starts */
	set_sta_flag(sta, WLAN_STA_SP);

	__skb_queue_head_init(&frames);

	/*
	 * Get response frame(s) and more data bit for it.
	 */
	for (ac = 0; ac < IEEE80211_NUM_ACS; ac++) {
		unsigned long tids;

		if (ignored_acs & BIT(ac))
			continue;

		tids = ieee80211_tids_for_ac(ac);

		if (!found) {
			driver_release_tids = sta->driver_buffered_tids & tids;
			if (driver_release_tids) {
				found = true;
			} else {
				struct sk_buff *skb;

				while (n_frames > 0) {
					skb = skb_dequeue(&sta->tx_filtered[ac]);
					if (!skb) {
						skb = skb_dequeue(
							&sta->ps_tx_buf[ac]);
						if (skb)
							local->total_ps_buffered--;
					}
					if (!skb)
						break;
					n_frames--;
					found = true;
					__skb_queue_tail(&frames, skb);
				}
			}

			/*
			 * If the driver has data on more than one TID then
			 * certainly there's more data if we release just a
			 * single frame now (from a single TID).
			 */
			if (reason == IEEE80211_FRAME_RELEASE_PSPOLL &&
			    hweight16(driver_release_tids) > 1) {
				more_data = true;
				driver_release_tids =
					BIT(ffs(driver_release_tids) - 1);
				break;
			}
		}

		if (!skb_queue_empty(&sta->tx_filtered[ac]) ||
		    !skb_queue_empty(&sta->ps_tx_buf[ac])) {
			more_data = true;
			break;
		}
	}

	if (!found) {
		int tid;

		/*
		 * For PS-Poll, this can only happen due to a race condition
		 * when we set the TIM bit and the station notices it, but
		 * before it can poll for the frame we expire it.
		 *
		 * For uAPSD, this is said in the standard (11.2.1.5 h):
		 *	At each unscheduled SP for a non-AP STA, the AP shall
		 *	attempt to transmit at least one MSDU or MMPDU, but no
		 *	more than the value specified in the Max SP Length field
		 *	in the QoS Capability element from delivery-enabled ACs,
		 *	that are destined for the non-AP STA.
		 *
		 * Since we have no other MSDU/MMPDU, transmit a QoS null frame.
		 */

		/* This will evaluate to 1, 3, 5 or 7. */
		tid = 7 - ((ffs(~ignored_acs) - 1) << 1);

		ieee80211_send_null_response(sdata, sta, tid, reason);
		return;
	}

	if (!driver_release_tids) {
		struct sk_buff_head pending;
		struct sk_buff *skb;
		int num = 0;
		u16 tids = 0;

		skb_queue_head_init(&pending);

		while ((skb = __skb_dequeue(&frames))) {
			struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
			struct ieee80211_hdr *hdr = (void *) skb->data;
			u8 *qoshdr = NULL;

			num++;

			/*
			 * Tell TX path to send this frame even though the
			 * STA may still remain is PS mode after this frame
			 * exchange.
			 */
			info->flags |= IEEE80211_TX_CTL_NO_PS_BUFFER;

			/*
			 * Use MoreData flag to indicate whether there are
			 * more buffered frames for this STA
			 */
			if (more_data || !skb_queue_empty(&frames))
				hdr->frame_control |=
					cpu_to_le16(IEEE80211_FCTL_MOREDATA);
			else
				hdr->frame_control &=
					cpu_to_le16(~IEEE80211_FCTL_MOREDATA);

			if (ieee80211_is_data_qos(hdr->frame_control) ||
			    ieee80211_is_qos_nullfunc(hdr->frame_control))
				qoshdr = ieee80211_get_qos_ctl(hdr);

			/* end service period after last frame */
			if (skb_queue_empty(&frames)) {
				if (reason == IEEE80211_FRAME_RELEASE_UAPSD &&
				    qoshdr)
					*qoshdr |= IEEE80211_QOS_CTL_EOSP;

				info->flags |= IEEE80211_TX_STATUS_EOSP |
					       IEEE80211_TX_CTL_REQ_TX_STATUS;
			}

			if (qoshdr)
				tids |= BIT(*qoshdr & IEEE80211_QOS_CTL_TID_MASK);
			else
				tids |= BIT(0);

			__skb_queue_tail(&pending, skb);
		}

		drv_allow_buffered_frames(local, sta, tids, num,
					  reason, more_data);

		ieee80211_add_pending_skbs(local, &pending);

		sta_info_recalc_tim(sta);
	} else {
		/*
		 * We need to release a frame that is buffered somewhere in the
		 * driver ... it'll have to handle that.
		 * Note that, as per the comment above, it'll also have to see
		 * if there is more than just one frame on the specific TID that
		 * we're releasing from, and it needs to set the more-data bit
		 * accordingly if we tell it that there's no more data. If we do
		 * tell it there's more data, then of course the more-data bit
		 * needs to be set anyway.
		 */
		drv_release_buffered_frames(local, sta, driver_release_tids,
					    n_frames, reason, more_data);

		/*
		 * Note that we don't recalculate the TIM bit here as it would
		 * most likely have no effect at all unless the driver told us
		 * that the TID became empty before returning here from the
		 * release function.
		 * Either way, however, when the driver tells us that the TID
		 * became empty we'll do the TIM recalculation.
		 */
	}
}