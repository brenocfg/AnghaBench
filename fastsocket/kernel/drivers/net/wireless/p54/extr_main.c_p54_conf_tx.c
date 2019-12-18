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
typedef  size_t u16 ;
struct p54_common {int /*<<< orphan*/  conf_mutex; int /*<<< orphan*/ * qos_params; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_tx_queue_params {int /*<<< orphan*/  txop; int /*<<< orphan*/  cw_max; int /*<<< orphan*/  cw_min; int /*<<< orphan*/  aifs; } ;
struct ieee80211_hw {size_t queues; struct p54_common* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  P54_SET_QUEUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int p54_set_edcf (struct p54_common*) ; 

__attribute__((used)) static int p54_conf_tx(struct ieee80211_hw *dev,
		       struct ieee80211_vif *vif, u16 queue,
		       const struct ieee80211_tx_queue_params *params)
{
	struct p54_common *priv = dev->priv;
	int ret;

	mutex_lock(&priv->conf_mutex);
	if (queue < dev->queues) {
		P54_SET_QUEUE(priv->qos_params[queue], params->aifs,
			params->cw_min, params->cw_max, params->txop);
		ret = p54_set_edcf(priv);
	} else
		ret = -EINVAL;
	mutex_unlock(&priv->conf_mutex);
	return ret;
}