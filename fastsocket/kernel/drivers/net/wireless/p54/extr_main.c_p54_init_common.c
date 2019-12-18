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
struct p54_tx_data {int dummy; } ;
struct p54_hdr {int dummy; } ;
struct p54_common {int basic_rate_mask; int noise; int /*<<< orphan*/ * curchan; int /*<<< orphan*/ * mc_maclist; int /*<<< orphan*/  work; int /*<<< orphan*/  beacon_comp; int /*<<< orphan*/  eeprom_comp; int /*<<< orphan*/  stat_comp; int /*<<< orphan*/  eeprom_mutex; int /*<<< orphan*/  conf_mutex; TYPE_1__* tx_stats; int /*<<< orphan*/  beacon_req_id; int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  tx_queue; int /*<<< orphan*/  tx_stats_lock; int /*<<< orphan*/  mode; struct ieee80211_hw* hw; } ;
struct ieee80211_hw {int flags; int channel_change_time; int queues; int max_rates; int max_rate_tries; int extra_tx_headroom; TYPE_2__* wiphy; struct p54_common* priv; } ;
struct TYPE_4__ {int interface_modes; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int limit; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int IEEE80211_HW_MFP_CAPABLE ; 
 int IEEE80211_HW_PS_NULLFUNC_STACK ; 
 int IEEE80211_HW_REPORTS_TX_ACK_STATUS ; 
 int IEEE80211_HW_RX_INCLUDES_FCS ; 
 int IEEE80211_HW_SIGNAL_DBM ; 
 int IEEE80211_HW_SUPPORTS_PS ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  NL80211_IFTYPE_STATION ; 
 int /*<<< orphan*/  NL80211_IFTYPE_UNSPECIFIED ; 
 size_t P54_QUEUE_BEACON ; 
 size_t P54_QUEUE_CAB ; 
 size_t P54_QUEUE_DATA ; 
 size_t P54_QUEUE_FWSCAN ; 
 size_t P54_QUEUE_MGMT ; 
 int /*<<< orphan*/  WIPHY_FLAG_PS_ON_BY_DEFAULT ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 struct ieee80211_hw* ieee80211_alloc_hw (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p54_ops ; 
 int /*<<< orphan*/  p54_reset_stats (struct p54_common*) ; 
 int /*<<< orphan*/  p54_work ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

struct ieee80211_hw *p54_init_common(size_t priv_data_len)
{
	struct ieee80211_hw *dev;
	struct p54_common *priv;

	dev = ieee80211_alloc_hw(priv_data_len, &p54_ops);
	if (!dev)
		return NULL;

	priv = dev->priv;
	priv->hw = dev;
	priv->mode = NL80211_IFTYPE_UNSPECIFIED;
	priv->basic_rate_mask = 0x15f;
	spin_lock_init(&priv->tx_stats_lock);
	skb_queue_head_init(&priv->tx_queue);
	skb_queue_head_init(&priv->tx_pending);
	dev->flags = IEEE80211_HW_RX_INCLUDES_FCS |
		     IEEE80211_HW_SIGNAL_DBM |
		     IEEE80211_HW_SUPPORTS_PS |
		     IEEE80211_HW_PS_NULLFUNC_STACK |
		     IEEE80211_HW_MFP_CAPABLE |
		     IEEE80211_HW_REPORTS_TX_ACK_STATUS;

	dev->wiphy->interface_modes = BIT(NL80211_IFTYPE_STATION) |
				      BIT(NL80211_IFTYPE_ADHOC) |
				      BIT(NL80211_IFTYPE_AP) |
				      BIT(NL80211_IFTYPE_MESH_POINT);

	dev->channel_change_time = 1000;	/* TODO: find actual value */
	priv->beacon_req_id = cpu_to_le32(0);
	priv->tx_stats[P54_QUEUE_BEACON].limit = 1;
	priv->tx_stats[P54_QUEUE_FWSCAN].limit = 1;
	priv->tx_stats[P54_QUEUE_MGMT].limit = 3;
	priv->tx_stats[P54_QUEUE_CAB].limit = 3;
	priv->tx_stats[P54_QUEUE_DATA].limit = 5;
	dev->queues = 1;
	priv->noise = -94;
	/*
	 * We support at most 8 tries no matter which rate they're at,
	 * we cannot support max_rates * max_rate_tries as we set it
	 * here, but setting it correctly to 4/2 or so would limit us
	 * artificially if the RC algorithm wants just two rates, so
	 * let's say 4/7, we'll redistribute it at TX time, see the
	 * comments there.
	 */
	dev->max_rates = 4;
	dev->max_rate_tries = 7;
	dev->extra_tx_headroom = sizeof(struct p54_hdr) + 4 +
				 sizeof(struct p54_tx_data);

	/*
	 * For now, disable PS by default because it affects
	 * link stability significantly.
	 */
	dev->wiphy->flags &= ~WIPHY_FLAG_PS_ON_BY_DEFAULT;

	mutex_init(&priv->conf_mutex);
	mutex_init(&priv->eeprom_mutex);
	init_completion(&priv->stat_comp);
	init_completion(&priv->eeprom_comp);
	init_completion(&priv->beacon_comp);
	INIT_DELAYED_WORK(&priv->work, p54_work);

	memset(&priv->mc_maclist[0], ~0, ETH_ALEN);
	priv->curchan = NULL;
	p54_reset_stats(priv);
	return dev;
}