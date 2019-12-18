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
typedef  int /*<<< orphan*/  uint ;
struct net_device {int dummy; } ;
struct fec_enet_private {int mii_phy_task_queued; int /*<<< orphan*/  phy_task; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mii_display_config ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mii_queue_config(uint mii_reg, struct net_device *dev)
{
	struct fec_enet_private *fep = netdev_priv(dev);

	if (fep->mii_phy_task_queued)
		return;

	fep->mii_phy_task_queued = 1;
	INIT_WORK(&fep->phy_task, mii_display_config);
	schedule_work(&fep->phy_task);
}