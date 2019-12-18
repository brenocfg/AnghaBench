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
struct port_info {int /*<<< orphan*/  tx_chan; int /*<<< orphan*/  adapter; } ;
struct net_device {int /*<<< orphan*/ * dev_addr; } ;
struct ethtool_wolinfo {int wolopts; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCAST_CRC ; 
 int EINVAL ; 
 int WAKE_BCAST ; 
 int WAKE_MAGIC ; 
 int WOL_SUPPORTED ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  t4_wol_magic_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int t4_wol_pat_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned long long,unsigned long long,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	int err = 0;
	struct port_info *pi = netdev_priv(dev);

	if (wol->wolopts & ~WOL_SUPPORTED)
		return -EINVAL;
	t4_wol_magic_enable(pi->adapter, pi->tx_chan,
			    (wol->wolopts & WAKE_MAGIC) ? dev->dev_addr : NULL);
	if (wol->wolopts & WAKE_BCAST) {
		err = t4_wol_pat_enable(pi->adapter, pi->tx_chan, 0xfe, ~0ULL,
					~0ULL, 0, false);
		if (!err)
			err = t4_wol_pat_enable(pi->adapter, pi->tx_chan, 1,
						~6ULL, ~0ULL, BCAST_CRC, true);
	} else
		t4_wol_pat_enable(pi->adapter, pi->tx_chan, 0, 0, 0, 0, false);
	return err;
}