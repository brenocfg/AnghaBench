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
struct efx_nic {int n_rx_channels; int /*<<< orphan*/  rx_indir_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ EFX_REV_FALCON_B0 ; 
 scalar_t__ efx_nic_rev (struct efx_nic*) ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 efx_ethtool_get_rxfh_indir_size(struct net_device *net_dev)
{
	struct efx_nic *efx = netdev_priv(net_dev);
	
	return ((efx_nic_rev(efx) < EFX_REV_FALCON_B0 ||
		efx->n_rx_channels == 1) ?
	               0 : ARRAY_SIZE(efx->rx_indir_table));
}