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
struct b43_phy {int /*<<< orphan*/  channel; struct b43_phy_operations* ops; } ;
struct b43_wldev {int /*<<< orphan*/  wl; struct b43_phy phy; } ;
struct b43_phy_operations {int (* init ) (struct b43_wldev*) ;int /*<<< orphan*/  (* software_rfkill ) (struct b43_wldev*,int) ;int /*<<< orphan*/  (* exit ) (struct b43_wldev*) ;int /*<<< orphan*/  (* get_default_chan ) (struct b43_wldev*) ;} ;

/* Variables and functions */
 int b43_switch_channel (struct b43_wldev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (struct b43_wldev*) ; 
 int /*<<< orphan*/  stub2 (struct b43_wldev*,int) ; 
 int stub3 (struct b43_wldev*) ; 
 int /*<<< orphan*/  stub4 (struct b43_wldev*) ; 
 int /*<<< orphan*/  stub5 (struct b43_wldev*) ; 
 int /*<<< orphan*/  stub6 (struct b43_wldev*,int) ; 

int b43_phy_init(struct b43_wldev *dev)
{
	struct b43_phy *phy = &dev->phy;
	const struct b43_phy_operations *ops = phy->ops;
	int err;

	phy->channel = ops->get_default_chan(dev);

	ops->software_rfkill(dev, false);
	err = ops->init(dev);
	if (err) {
		b43err(dev->wl, "PHY init failed\n");
		goto err_block_rf;
	}
	/* Make sure to switch hardware and firmware (SHM) to
	 * the default channel. */
	err = b43_switch_channel(dev, ops->get_default_chan(dev));
	if (err) {
		b43err(dev->wl, "PHY init: Channel switch to default failed\n");
		goto err_phy_exit;
	}

	return 0;

err_phy_exit:
	if (ops->exit)
		ops->exit(dev);
err_block_rf:
	ops->software_rfkill(dev, true);

	return err;
}