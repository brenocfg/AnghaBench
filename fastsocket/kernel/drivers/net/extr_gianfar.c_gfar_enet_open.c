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
struct net_device {int /*<<< orphan*/  dev; } ;
struct gfar_private {int /*<<< orphan*/  wol_en; int /*<<< orphan*/  napi; int /*<<< orphan*/  rx_recycle; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_set_wakeup_enable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfar_set_mac_address (struct net_device*) ; 
 int init_phy (struct net_device*) ; 
 int /*<<< orphan*/  init_registers (struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 struct gfar_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int startup_gfar (struct net_device*) ; 

__attribute__((used)) static int gfar_enet_open(struct net_device *dev)
{
	struct gfar_private *priv = netdev_priv(dev);
	int err;

	napi_enable(&priv->napi);

	skb_queue_head_init(&priv->rx_recycle);

	/* Initialize a bunch of registers */
	init_registers(dev);

	gfar_set_mac_address(dev);

	err = init_phy(dev);

	if(err) {
		napi_disable(&priv->napi);
		return err;
	}

	err = startup_gfar(dev);
	if (err) {
		napi_disable(&priv->napi);
		return err;
	}

	netif_start_queue(dev);

	device_set_wakeup_enable(&dev->dev, priv->wol_en);

	return err;
}