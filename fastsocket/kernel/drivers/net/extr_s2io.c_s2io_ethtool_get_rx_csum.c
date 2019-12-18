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
typedef  int /*<<< orphan*/  u32 ;
struct s2io_nic {int /*<<< orphan*/  rx_csum; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct s2io_nic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 s2io_ethtool_get_rx_csum(struct net_device *dev)
{
	struct s2io_nic *sp = netdev_priv(dev);

	return sp->rx_csum;
}