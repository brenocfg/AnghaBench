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
struct sky2_hw {struct net_device** dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct net_device {int /*<<< orphan*/  last_rx; TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/ * rxqaddr ; 
 int /*<<< orphan*/  sky2_rx_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sky2_rx_done(struct sky2_hw *hw, unsigned port,
				unsigned packets, unsigned bytes)
{
	if (packets) {
		struct net_device *dev = hw->dev[port];

		dev->stats.rx_packets += packets;
		dev->stats.rx_bytes += bytes;
		dev->last_rx = jiffies;
		sky2_rx_update(netdev_priv(dev), rxqaddr[port]);
	}
}