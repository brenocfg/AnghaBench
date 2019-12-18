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
struct netvsc_device {struct net_device* ndev; } ;
struct net_device_context {int /*<<< orphan*/  dwork; } ;
struct net_device {int dummy; } ;
struct hv_device {int dummy; } ;

/* Variables and functions */
 struct netvsc_device* hv_get_drvdata (struct hv_device*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void netvsc_linkstatus_callback(struct hv_device *device_obj,
				       unsigned int status)
{
	struct net_device *net;
	struct net_device_context *ndev_ctx;
	struct netvsc_device *net_device;

	net_device = hv_get_drvdata(device_obj);
	net = net_device->ndev;

	if (!net) {
		netdev_err(net, "got link status but net device "
				"not initialized yet\n");
		return;
	}

	if (status == 1) {
		netif_carrier_on(net);
		ndev_ctx = netdev_priv(net);
		schedule_delayed_work(&ndev_ctx->dwork, 0);
		schedule_delayed_work(&ndev_ctx->dwork, msecs_to_jiffies(20));
	} else {
		netif_carrier_off(net);
	}
}