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
struct net_device {int dummy; } ;
struct efx_nic {int /*<<< orphan*/  rx_checksum_enabled; } ;

/* Variables and functions */
 struct efx_nic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 efx_ethtool_get_rx_csum(struct net_device *net_dev)
{
	struct efx_nic *efx = netdev_priv(net_dev);

	return efx->rx_checksum_enabled;
}