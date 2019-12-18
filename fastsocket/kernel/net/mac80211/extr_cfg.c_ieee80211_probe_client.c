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
typedef  int /*<<< orphan*/  u8 ;
typedef  unsigned long u64 ;
struct wiphy {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  addr; } ;
struct sta_info {TYPE_4__ sta; } ;
struct sk_buff {int priority; struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct ieee80211_tx_info {int flags; } ;
struct TYPE_10__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  chanctx_conf; } ;
struct ieee80211_sub_if_data {TYPE_5__ vif; struct ieee80211_local* local; } ;
struct ieee80211_qos_hdr {void* qos_ctrl; scalar_t__ seq_ctrl; int /*<<< orphan*/  addr3; int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr1; scalar_t__ duration_id; void* frame_control; } ;
struct TYPE_8__ {scalar_t__ extra_tx_headroom; } ;
struct ieee80211_local {TYPE_3__ hw; } ;
struct TYPE_7__ {TYPE_1__* chan; } ;
struct ieee80211_chanctx_conf {TYPE_2__ def; } ;
typedef  enum ieee80211_band { ____Placeholder_ieee80211_band } ieee80211_band ;
typedef  void* __le16 ;
struct TYPE_6__ {int band; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOLINK ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IEEE80211_AC_VO ; 
 struct ieee80211_sub_if_data* IEEE80211_DEV_TO_SUB_IF (struct net_device*) ; 
 int IEEE80211_FCTL_FROMDS ; 
 int IEEE80211_FTYPE_DATA ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_STYPE_NULLFUNC ; 
 int IEEE80211_STYPE_QOS_NULLFUNC ; 
 int IEEE80211_TX_CTL_REQ_TX_STATUS ; 
 int IEEE80211_TX_INTFL_NL80211_FRAME_TX ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WLAN_STA_WME ; 
 void* cpu_to_le16 (int) ; 
 struct sk_buff* dev_alloc_skb (scalar_t__) ; 
 int /*<<< orphan*/  ieee80211_xmit (struct ieee80211_sub_if_data*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  local_bh_disable () ; 
 int /*<<< orphan*/  local_bh_enable () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ieee80211_chanctx_conf* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  skb_set_queue_mapping (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sta_info* sta_info_get (struct ieee80211_sub_if_data*,int /*<<< orphan*/  const*) ; 
 int test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ieee80211_probe_client(struct wiphy *wiphy, struct net_device *dev,
				  const u8 *peer, u64 *cookie)
{
	struct ieee80211_sub_if_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_qos_hdr *nullfunc;
	struct sk_buff *skb;
	int size = sizeof(*nullfunc);
	__le16 fc;
	bool qos;
	struct ieee80211_tx_info *info;
	struct sta_info *sta;
	struct ieee80211_chanctx_conf *chanctx_conf;
	enum ieee80211_band band;

	rcu_read_lock();
	chanctx_conf = rcu_dereference(sdata->vif.chanctx_conf);
	if (WARN_ON(!chanctx_conf)) {
		rcu_read_unlock();
		return -EINVAL;
	}
	band = chanctx_conf->def.chan->band;
	sta = sta_info_get(sdata, peer);
	if (sta) {
		qos = test_sta_flag(sta, WLAN_STA_WME);
	} else {
		rcu_read_unlock();
		return -ENOLINK;
	}

	if (qos) {
		fc = cpu_to_le16(IEEE80211_FTYPE_DATA |
				 IEEE80211_STYPE_QOS_NULLFUNC |
				 IEEE80211_FCTL_FROMDS);
	} else {
		size -= 2;
		fc = cpu_to_le16(IEEE80211_FTYPE_DATA |
				 IEEE80211_STYPE_NULLFUNC |
				 IEEE80211_FCTL_FROMDS);
	}

	skb = dev_alloc_skb(local->hw.extra_tx_headroom + size);
	if (!skb) {
		rcu_read_unlock();
		return -ENOMEM;
	}

	skb->dev = dev;

	skb_reserve(skb, local->hw.extra_tx_headroom);

	nullfunc = (void *) skb_put(skb, size);
	nullfunc->frame_control = fc;
	nullfunc->duration_id = 0;
	memcpy(nullfunc->addr1, sta->sta.addr, ETH_ALEN);
	memcpy(nullfunc->addr2, sdata->vif.addr, ETH_ALEN);
	memcpy(nullfunc->addr3, sdata->vif.addr, ETH_ALEN);
	nullfunc->seq_ctrl = 0;

	info = IEEE80211_SKB_CB(skb);

	info->flags |= IEEE80211_TX_CTL_REQ_TX_STATUS |
		       IEEE80211_TX_INTFL_NL80211_FRAME_TX;

	skb_set_queue_mapping(skb, IEEE80211_AC_VO);
	skb->priority = 7;
	if (qos)
		nullfunc->qos_ctrl = cpu_to_le16(7);

	local_bh_disable();
	ieee80211_xmit(sdata, skb, band);
	local_bh_enable();
	rcu_read_unlock();

	*cookie = (unsigned long) skb;
	return 0;
}