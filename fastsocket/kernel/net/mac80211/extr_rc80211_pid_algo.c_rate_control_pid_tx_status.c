#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct rc_pid_sta_info {scalar_t__ txrate_idx; scalar_t__ last_sample; int /*<<< orphan*/  tx_num_xmit; scalar_t__ tx_num_failed; int /*<<< orphan*/  events; } ;
struct rc_pid_info {int /*<<< orphan*/  sampling_period; } ;
struct TYPE_4__ {TYPE_1__* rates; } ;
struct ieee80211_tx_info {int flags; TYPE_2__ status; } ;
struct ieee80211_supported_band {int dummy; } ;
struct ieee80211_sta {int dummy; } ;
struct TYPE_3__ {scalar_t__ idx; int count; } ;

/* Variables and functions */
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_STAT_ACK ; 
 int /*<<< orphan*/  jiffies ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rate_control_pid_event_tx_status (int /*<<< orphan*/ *,struct ieee80211_tx_info*) ; 
 int /*<<< orphan*/  rate_control_pid_sample (struct rc_pid_info*,struct ieee80211_supported_band*,struct ieee80211_sta*,struct rc_pid_sta_info*) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void rate_control_pid_tx_status(void *priv, struct ieee80211_supported_band *sband,
				       struct ieee80211_sta *sta, void *priv_sta,
				       struct sk_buff *skb)
{
	struct rc_pid_info *pinfo = priv;
	struct rc_pid_sta_info *spinfo = priv_sta;
	unsigned long period;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	if (!spinfo)
		return;

	/* Ignore all frames that were sent with a different rate than the rate
	 * we currently advise mac80211 to use. */
	if (info->status.rates[0].idx != spinfo->txrate_idx)
		return;

	spinfo->tx_num_xmit++;

#ifdef CONFIG_MAC80211_DEBUGFS
	rate_control_pid_event_tx_status(&spinfo->events, info);
#endif

	/* We count frames that totally failed to be transmitted as two bad
	 * frames, those that made it out but had some retries as one good and
	 * one bad frame. */
	if (!(info->flags & IEEE80211_TX_STAT_ACK)) {
		spinfo->tx_num_failed += 2;
		spinfo->tx_num_xmit++;
	} else if (info->status.rates[0].count > 1) {
		spinfo->tx_num_failed++;
		spinfo->tx_num_xmit++;
	}

	/* Update PID controller state. */
	period = msecs_to_jiffies(pinfo->sampling_period);
	if (time_after(jiffies, spinfo->last_sample + period))
		rate_control_pid_sample(pinfo, sband, sta, spinfo);
}