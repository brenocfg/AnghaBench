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
struct netvsc_device_info {int /*<<< orphan*/  mac_adr; int /*<<< orphan*/  ring_size; } ;
struct net_device_context {int /*<<< orphan*/  work; int /*<<< orphan*/  dwork; struct hv_device* device_ctx; } ;
struct net_device {int features; int /*<<< orphan*/  dev_addr; int /*<<< orphan*/ * netdev_ops; } ;
struct hv_vmbus_device_id {int dummy; } ;
struct hv_device {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int NETIF_F_HW_VLAN_TX ; 
 int NETIF_F_SG ; 
 int /*<<< orphan*/  SET_ETHTOOL_OPS (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_NETDEV_DEV (struct net_device*,int /*<<< orphan*/ *) ; 
 struct net_device* alloc_etherdev (int) ; 
 int /*<<< orphan*/  device_ops ; 
 int /*<<< orphan*/  do_set_multicast ; 
 int /*<<< orphan*/  ethtool_ops ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  hv_set_drvdata (struct hv_device*,struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netvsc_send_garp ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int register_netdev (struct net_device*) ; 
 int /*<<< orphan*/  ring_size ; 
 int rndis_filter_device_add (struct hv_device*,struct netvsc_device_info*) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int netvsc_probe(struct hv_device *dev,
			const struct hv_vmbus_device_id *dev_id)
{
	struct net_device *net = NULL;
	struct net_device_context *net_device_ctx;
	struct netvsc_device_info device_info;
	int ret;

	net = alloc_etherdev(sizeof(struct net_device_context));
	if (!net)
		return -ENOMEM;

	/* Set initial state */
	netif_carrier_off(net);

	net_device_ctx = netdev_priv(net);
	net_device_ctx->device_ctx = dev;
	hv_set_drvdata(dev, net);
	INIT_DELAYED_WORK(&net_device_ctx->dwork, netvsc_send_garp);
	INIT_WORK(&net_device_ctx->work, do_set_multicast);

	net->netdev_ops = &device_ops;

	/* TODO: Add GSO and Checksum offload */
	/* net->hw_features = NETIF_F_SG; */
	net->features = NETIF_F_SG | NETIF_F_HW_VLAN_TX;

	SET_ETHTOOL_OPS(net, &ethtool_ops);
	SET_NETDEV_DEV(net, &dev->device);

	ret = register_netdev(net);
	if (ret != 0) {
		pr_err("Unable to register netdev.\n");
		free_netdev(net);
		goto out;
	}

	/* Notify the netvsc driver of the new device */
	device_info.ring_size = ring_size;
	ret = rndis_filter_device_add(dev, &device_info);
	if (ret != 0) {
		netdev_err(net, "unable to add netvsc device (ret %d)\n", ret);
		unregister_netdev(net);
		free_netdev(net);
		hv_set_drvdata(dev, NULL);
		return ret;
	}
	memcpy(net->dev_addr, device_info.mac_adr, ETH_ALEN);

	netif_carrier_on(net);

out:
	return ret;
}