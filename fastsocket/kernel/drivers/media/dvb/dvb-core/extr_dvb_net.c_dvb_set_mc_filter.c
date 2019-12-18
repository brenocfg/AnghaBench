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
struct net_device {int dummy; } ;
struct dvb_net_priv {size_t multi_num; int /*<<< orphan*/ * multi_macs; } ;
struct dev_mc_list {int /*<<< orphan*/  dmi_addr; } ;

/* Variables and functions */
 size_t DVB_NET_MULTICAST_MAX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dvb_net_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int dvb_set_mc_filter (struct net_device *dev, struct dev_mc_list *mc)
{
	struct dvb_net_priv *priv = netdev_priv(dev);

	if (priv->multi_num == DVB_NET_MULTICAST_MAX)
		return -ENOMEM;

	memcpy(priv->multi_macs[priv->multi_num], mc->dmi_addr, 6);

	priv->multi_num++;
	return 0;
}