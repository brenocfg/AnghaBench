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
struct ethtool_channels {scalar_t__ combined_count; scalar_t__ other_count; scalar_t__ tx_count; scalar_t__ rx_count; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 scalar_t__ BNX2X_MAX_RSS_COUNT (struct bnx2x*) ; 
 int /*<<< orphan*/  BNX2X_MSG_ETHTOOL ; 
 scalar_t__ BNX2X_NUM_ETH_QUEUES (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  LOAD_NORMAL ; 
 int /*<<< orphan*/  UNLOAD_NORMAL ; 
 int /*<<< orphan*/  bnx2x_change_num_queues (struct bnx2x*,scalar_t__) ; 
 int bnx2x_nic_load (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnx2x_nic_unload (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int bnx2x_set_channels(struct net_device *dev,
			      struct ethtool_channels *channels)
{
	struct bnx2x *bp = netdev_priv(dev);

	DP(BNX2X_MSG_ETHTOOL,
	   "set-channels command parameters: rx = %d, tx = %d, other = %d, combined = %d\n",
	   channels->rx_count, channels->tx_count, channels->other_count,
	   channels->combined_count);

	/* We don't support separate rx / tx channels.
	 * We don't allow setting 'other' channels.
	 */
	if (channels->rx_count || channels->tx_count || channels->other_count
	    || (channels->combined_count == 0) ||
	    (channels->combined_count > BNX2X_MAX_RSS_COUNT(bp))) {
		DP(BNX2X_MSG_ETHTOOL, "command parameters not supported\n");
		return -EINVAL;
	}

	/* Check if there was a change in the active parameters */
	if (channels->combined_count == BNX2X_NUM_ETH_QUEUES(bp)) {
		DP(BNX2X_MSG_ETHTOOL, "No change in active parameters\n");
		return 0;
	}

	/* Set the requested number of queues in bp context.
	 * Note that the actual number of queues created during load may be
	 * less than requested if memory is low.
	 */
	if (unlikely(!netif_running(dev))) {
		bnx2x_change_num_queues(bp, channels->combined_count);
		return 0;
	}
	bnx2x_nic_unload(bp, UNLOAD_NORMAL, true);
	bnx2x_change_num_queues(bp, channels->combined_count);
	return bnx2x_nic_load(bp, LOAD_NORMAL);
}