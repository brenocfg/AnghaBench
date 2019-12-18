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
struct ethtool_ringparam {scalar_t__ rx_pending; scalar_t__ tx_pending; } ;
struct bnx2x {scalar_t__ recovery_state; scalar_t__ rx_ring_size; scalar_t__ tx_ring_size; scalar_t__ disable_tpa; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_MSG_ETHTOOL ; 
 scalar_t__ BNX2X_RECOVERY_DONE ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,...) ; 
 int EAGAIN ; 
 int EINVAL ; 
 scalar_t__ IS_MF_FCOE_AFEX (struct bnx2x*) ; 
 scalar_t__ MAX_RX_AVAIL ; 
 scalar_t__ MAX_SKB_FRAGS ; 
 scalar_t__ MAX_TX_AVAIL ; 
 scalar_t__ MIN_RX_SIZE_NONTPA ; 
 scalar_t__ MIN_RX_SIZE_TPA ; 
 int bnx2x_reload_if_running (struct net_device*) ; 
 struct bnx2x* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int bnx2x_set_ringparam(struct net_device *dev,
			       struct ethtool_ringparam *ering)
{
	struct bnx2x *bp = netdev_priv(dev);

	DP(BNX2X_MSG_ETHTOOL,
	   "set ring params command parameters: rx_pending = %d, tx_pending = %d\n",
	   ering->rx_pending, ering->tx_pending);

	if (bp->recovery_state != BNX2X_RECOVERY_DONE) {
		DP(BNX2X_MSG_ETHTOOL,
		   "Handling parity error recovery. Try again later\n");
		return -EAGAIN;
	}

	if ((ering->rx_pending > MAX_RX_AVAIL) ||
	    (ering->rx_pending < (bp->disable_tpa ? MIN_RX_SIZE_NONTPA :
						    MIN_RX_SIZE_TPA)) ||
	    (ering->tx_pending > (IS_MF_FCOE_AFEX(bp) ? 0 : MAX_TX_AVAIL)) ||
	    (ering->tx_pending <= MAX_SKB_FRAGS + 4)) {
		DP(BNX2X_MSG_ETHTOOL, "Command parameters not supported\n");
		return -EINVAL;
	}

	bp->rx_ring_size = ering->rx_pending;
	bp->tx_ring_size = ering->tx_pending;

	return bnx2x_reload_if_running(dev);
}