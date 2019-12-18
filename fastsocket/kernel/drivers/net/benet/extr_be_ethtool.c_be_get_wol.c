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
struct ethtool_wolinfo {int /*<<< orphan*/  sopass; int /*<<< orphan*/  wolopts; int /*<<< orphan*/  supported; } ;
struct be_adapter {scalar_t__ wol; } ;

/* Variables and functions */
 int /*<<< orphan*/  WAKE_MAGIC ; 
 scalar_t__ be_is_wol_supported (struct be_adapter*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct be_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void
be_get_wol(struct net_device *netdev, struct ethtool_wolinfo *wol)
{
	struct be_adapter *adapter = netdev_priv(netdev);

	if (be_is_wol_supported(adapter)) {
		wol->supported |= WAKE_MAGIC;
		if (adapter->wol)
			wol->wolopts |= WAKE_MAGIC;
	} else
		wol->wolopts = 0;
	memset(&wol->sopass, 0, sizeof(wol->sopass));
}