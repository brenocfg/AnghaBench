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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct ipw2100_priv {int /*<<< orphan*/  action_mutex; TYPE_1__ reset_work; scalar_t__ reset_backoff; int /*<<< orphan*/  mac_addr; int /*<<< orphan*/  config; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_CUSTOM_MAC ; 
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  ipw2100_reset_adapter (int /*<<< orphan*/ *) ; 
 int ipw2100_set_mac_address (struct ipw2100_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/ ) ; 
 struct ipw2100_priv* libipw_priv (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw2100_set_address(struct net_device *dev, void *p)
{
	struct ipw2100_priv *priv = libipw_priv(dev);
	struct sockaddr *addr = p;
	int err = 0;

	if (!is_valid_ether_addr(addr->sa_data))
		return -EADDRNOTAVAIL;

	mutex_lock(&priv->action_mutex);

	priv->config |= CFG_CUSTOM_MAC;
	memcpy(priv->mac_addr, addr->sa_data, ETH_ALEN);

	err = ipw2100_set_mac_address(priv, 0);
	if (err)
		goto done;

	priv->reset_backoff = 0;
	mutex_unlock(&priv->action_mutex);
	ipw2100_reset_adapter(&priv->reset_work.work);
	return 0;

      done:
	mutex_unlock(&priv->action_mutex);
	return err;
}