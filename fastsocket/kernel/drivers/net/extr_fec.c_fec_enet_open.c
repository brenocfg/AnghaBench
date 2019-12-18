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
struct fec_enet_private {int link; int opened; TYPE_1__* phy; scalar_t__ sequence_done; } ;
struct TYPE_2__ {int /*<<< orphan*/  startup; int /*<<< orphan*/  config; int /*<<< orphan*/  ack_int; } ;

/* Variables and functions */
 int fec_enet_alloc_buffers (struct net_device*) ; 
 int /*<<< orphan*/  fec_restart (struct net_device*,int) ; 
 int /*<<< orphan*/  mii_do_cmd (struct net_device*,int /*<<< orphan*/ ) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_cmd_config ; 
 int /*<<< orphan*/  schedule () ; 

__attribute__((used)) static int
fec_enet_open(struct net_device *dev)
{
	struct fec_enet_private *fep = netdev_priv(dev);
	int ret;

	/* I should reset the ring buffers here, but I don't yet know
	 * a simple way to do that.
	 */

	ret = fec_enet_alloc_buffers(dev);
	if (ret)
		return ret;

	fep->sequence_done = 0;
	fep->link = 0;

	fec_restart(dev, 1);

	if (fep->phy) {
		mii_do_cmd(dev, fep->phy->ack_int);
		mii_do_cmd(dev, fep->phy->config);
		mii_do_cmd(dev, phy_cmd_config);  /* display configuration */

		/* Poll until the PHY tells us its configuration
		 * (not link state).
		 * Request is initiated by mii_do_cmd above, but answer
		 * comes by interrupt.
		 * This should take about 25 usec per register at 2.5 MHz,
		 * and we read approximately 5 registers.
		 */
		while(!fep->sequence_done)
			schedule();

		mii_do_cmd(dev, fep->phy->startup);
	}

	/* Set the initial link state to true. A lot of hardware
	 * based on this device does not implement a PHY interrupt,
	 * so we are never notified of link change.
	 */
	fep->link = 1;

	netif_start_queue(dev);
	fep->opened = 1;
	return 0;
}