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
struct sockaddr {int /*<<< orphan*/  sa_data; } ;
struct net_device {int /*<<< orphan*/  addr_len; int /*<<< orphan*/  dev_addr; } ;
struct dvb_net_priv {int /*<<< orphan*/  restart_net_feed_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dvb_net_priv* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dvb_net_set_mac (struct net_device *dev, void *p)
{
	struct dvb_net_priv *priv = netdev_priv(dev);
	struct sockaddr *addr=p;

	memcpy(dev->dev_addr, addr->sa_data, dev->addr_len);

	if (netif_running(dev))
		schedule_work(&priv->restart_net_feed_wq);

	return 0;
}