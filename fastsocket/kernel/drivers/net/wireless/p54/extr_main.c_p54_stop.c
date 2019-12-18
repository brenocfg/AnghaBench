#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct p54_common {int /*<<< orphan*/  conf_mutex; scalar_t__ tsf_low32; scalar_t__ tsf_high32; int /*<<< orphan*/  beacon_req_id; TYPE_1__* tx_stats; int /*<<< orphan*/  tx_queue; int /*<<< orphan*/  tx_pending; int /*<<< orphan*/  (* stop ) (struct ieee80211_hw*) ;int /*<<< orphan*/  work; scalar_t__ softled_state; int /*<<< orphan*/  mode; } ;
struct ieee80211_hw {struct p54_common* priv; } ;
struct TYPE_2__ {scalar_t__ len; scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL80211_IFTYPE_UNSPECIFIED ; 
 int P54_QUEUE_NUM ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p54_set_leds (struct p54_common*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*) ; 

__attribute__((used)) static void p54_stop(struct ieee80211_hw *dev)
{
	struct p54_common *priv = dev->priv;
	int i;

	priv->mode = NL80211_IFTYPE_UNSPECIFIED;
	priv->softled_state = 0;
	cancel_delayed_work_sync(&priv->work);
	mutex_lock(&priv->conf_mutex);
	p54_set_leds(priv);
	priv->stop(dev);
	skb_queue_purge(&priv->tx_pending);
	skb_queue_purge(&priv->tx_queue);
	for (i = 0; i < P54_QUEUE_NUM; i++) {
		priv->tx_stats[i].count = 0;
		priv->tx_stats[i].len = 0;
	}

	priv->beacon_req_id = cpu_to_le32(0);
	priv->tsf_high32 = priv->tsf_low32 = 0;
	mutex_unlock(&priv->conf_mutex);
}