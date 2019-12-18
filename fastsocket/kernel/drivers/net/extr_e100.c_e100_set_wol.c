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
struct nic {TYPE_1__* pdev; int /*<<< orphan*/  flags; } ;
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int /*<<< orphan*/  wolopts; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  WAKE_MAGIC ; 
 int /*<<< orphan*/  device_can_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_wakeup_enable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e100_configure ; 
 int /*<<< orphan*/  e100_exec_cb (struct nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  wol_magic ; 

__attribute__((used)) static int e100_set_wol(struct net_device *netdev, struct ethtool_wolinfo *wol)
{
	struct nic *nic = netdev_priv(netdev);

	if ((wol->wolopts && wol->wolopts != WAKE_MAGIC) ||
	    !device_can_wakeup(&nic->pdev->dev))
		return -EOPNOTSUPP;

	if (wol->wolopts)
		nic->flags |= wol_magic;
	else
		nic->flags &= ~wol_magic;

	device_set_wakeup_enable(&nic->pdev->dev, wol->wolopts);

	e100_exec_cb(nic, NULL, e100_configure);

	return 0;
}