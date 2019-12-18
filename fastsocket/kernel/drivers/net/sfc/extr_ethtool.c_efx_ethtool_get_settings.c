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
struct net_device {int dummy; } ;
struct ethtool_cmd {int supported; int /*<<< orphan*/  duplex; } ;
struct efx_link_state {scalar_t__ fd; int /*<<< orphan*/  speed; } ;
struct efx_nic {int /*<<< orphan*/  mac_lock; TYPE_1__* phy_op; struct efx_link_state link_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* get_settings ) (struct efx_nic*,struct ethtool_cmd*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 scalar_t__ LOOPBACK_INTERNAL (struct efx_nic*) ; 
 int SUPPORTED_1000baseT_Half ; 
 int SUPPORTED_Asym_Pause ; 
 int SUPPORTED_Pause ; 
 int /*<<< orphan*/  ethtool_cmd_speed_set (struct ethtool_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct efx_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct efx_nic*,struct ethtool_cmd*) ; 

__attribute__((used)) static int efx_ethtool_get_settings(struct net_device *net_dev,
				    struct ethtool_cmd *ecmd)
{
	struct efx_nic *efx = netdev_priv(net_dev);
	struct efx_link_state *link_state = &efx->link_state;

	mutex_lock(&efx->mac_lock);
	efx->phy_op->get_settings(efx, ecmd);
	mutex_unlock(&efx->mac_lock);

	/* GMAC does not support 1000Mbps HD */
	ecmd->supported &= ~SUPPORTED_1000baseT_Half;
	/* Both MACs support pause frames (bidirectional and respond-only) */
	ecmd->supported |= SUPPORTED_Pause | SUPPORTED_Asym_Pause;

	if (LOOPBACK_INTERNAL(efx)) {
		ethtool_cmd_speed_set(ecmd, link_state->speed);
		ecmd->duplex = link_state->fd ? DUPLEX_FULL : DUPLEX_HALF;
	}

	return 0;
}