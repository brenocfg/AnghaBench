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
struct dvb_net_priv {int /*<<< orphan*/  in_use; } ;

/* Variables and functions */
 int dvb_net_feed_stop (struct net_device*) ; 
 struct dvb_net_priv* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int dvb_net_stop(struct net_device *dev)
{
	struct dvb_net_priv *priv = netdev_priv(dev);

	priv->in_use--;
	return dvb_net_feed_stop(dev);
}