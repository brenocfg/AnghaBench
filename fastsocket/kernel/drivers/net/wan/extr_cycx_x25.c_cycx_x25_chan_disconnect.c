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
struct cycx_x25_channel {int /*<<< orphan*/  lcn; int /*<<< orphan*/  link; int /*<<< orphan*/  card; scalar_t__ svc; } ;

/* Variables and functions */
 int /*<<< orphan*/  WAN_DISCONNECTED ; 
 int /*<<< orphan*/  WAN_DISCONNECTING ; 
 int /*<<< orphan*/  cycx_x25_set_chan_state (struct net_device*,int /*<<< orphan*/ ) ; 
 struct cycx_x25_channel* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  x25_clear_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cycx_x25_chan_disconnect(struct net_device *dev)
{
	struct cycx_x25_channel *chan = netdev_priv(dev);

	if (chan->svc) {
		x25_clear_call(chan->card, chan->link, chan->lcn, 0, 0);
		cycx_x25_set_chan_state(dev, WAN_DISCONNECTING);
	} else
		cycx_x25_set_chan_state(dev, WAN_DISCONNECTED);
}