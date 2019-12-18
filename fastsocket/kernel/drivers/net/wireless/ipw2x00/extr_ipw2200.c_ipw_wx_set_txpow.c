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
struct TYPE_2__ {scalar_t__ value; scalar_t__ flags; int /*<<< orphan*/  fixed; int /*<<< orphan*/  disabled; } ;
union iwreq_data {TYPE_1__ power; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct ipw_priv {scalar_t__ tx_power; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int EINVAL ; 
 scalar_t__ IPW_TX_POWER_DEFAULT ; 
 scalar_t__ IPW_TX_POWER_MAX ; 
 scalar_t__ IPW_TX_POWER_MIN ; 
 scalar_t__ IW_TXPOW_DBM ; 
 scalar_t__ ipw_radio_kill_sw (struct ipw_priv*,int /*<<< orphan*/ ) ; 
 int ipw_set_tx_power (struct ipw_priv*) ; 
 struct ipw_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw_wx_set_txpow(struct net_device *dev,
			    struct iw_request_info *info,
			    union iwreq_data *wrqu, char *extra)
{
	struct ipw_priv *priv = libipw_priv(dev);
	int err = 0;

	mutex_lock(&priv->mutex);
	if (ipw_radio_kill_sw(priv, wrqu->power.disabled)) {
		err = -EINPROGRESS;
		goto out;
	}

	if (!wrqu->power.fixed)
		wrqu->power.value = IPW_TX_POWER_DEFAULT;

	if (wrqu->power.flags != IW_TXPOW_DBM) {
		err = -EINVAL;
		goto out;
	}

	if ((wrqu->power.value > IPW_TX_POWER_MAX) ||
	    (wrqu->power.value < IPW_TX_POWER_MIN)) {
		err = -EINVAL;
		goto out;
	}

	priv->tx_power = wrqu->power.value;
	err = ipw_set_tx_power(priv);
      out:
	mutex_unlock(&priv->mutex);
	return err;
}