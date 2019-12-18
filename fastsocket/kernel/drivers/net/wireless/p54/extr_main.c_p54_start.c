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
struct p54_common {int (* open ) (struct ieee80211_hw*) ;int /*<<< orphan*/  conf_mutex; scalar_t__ softled_state; int /*<<< orphan*/  work; int /*<<< orphan*/  mode; int /*<<< orphan*/  bssid; int /*<<< orphan*/ * qos_params; } ;
struct ieee80211_hw {struct p54_common* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  NL80211_IFTYPE_MONITOR ; 
 int /*<<< orphan*/  NL80211_IFTYPE_UNSPECIFIED ; 
 int /*<<< orphan*/  P54_SET_QUEUE (int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  ieee80211_queue_delayed_work (struct ieee80211_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int p54_set_edcf (struct p54_common*) ; 
 int p54_set_leds (struct p54_common*) ; 
 int p54_setup_mac (struct p54_common*) ; 
 int stub1 (struct ieee80211_hw*) ; 

__attribute__((used)) static int p54_start(struct ieee80211_hw *dev)
{
	struct p54_common *priv = dev->priv;
	int err;

	mutex_lock(&priv->conf_mutex);
	err = priv->open(dev);
	if (err)
		goto out;
	P54_SET_QUEUE(priv->qos_params[0], 0x0002, 0x0003, 0x0007, 47);
	P54_SET_QUEUE(priv->qos_params[1], 0x0002, 0x0007, 0x000f, 94);
	P54_SET_QUEUE(priv->qos_params[2], 0x0003, 0x000f, 0x03ff, 0);
	P54_SET_QUEUE(priv->qos_params[3], 0x0007, 0x000f, 0x03ff, 0);
	err = p54_set_edcf(priv);
	if (err)
		goto out;

	memset(priv->bssid, ~0, ETH_ALEN);
	priv->mode = NL80211_IFTYPE_MONITOR;
	err = p54_setup_mac(priv);
	if (err) {
		priv->mode = NL80211_IFTYPE_UNSPECIFIED;
		goto out;
	}

	ieee80211_queue_delayed_work(dev, &priv->work, 0);

	priv->softled_state = 0;
	err = p54_set_leds(priv);

out:
	mutex_unlock(&priv->conf_mutex);
	return err;
}