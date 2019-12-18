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
struct tg3 {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ ASIC_REV_57766 ; 
 int EINVAL ; 
 int /*<<< orphan*/  RESET_KIND_SHUTDOWN ; 
 int TG3_MAX_MTU (struct tg3*) ; 
 int TG3_MIN_MTU ; 
 struct tg3* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 scalar_t__ tg3_asic_rev (struct tg3*) ; 
 int /*<<< orphan*/  tg3_full_lock (struct tg3*,int) ; 
 int /*<<< orphan*/  tg3_full_unlock (struct tg3*) ; 
 int /*<<< orphan*/  tg3_halt (struct tg3*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tg3_netif_start (struct tg3*) ; 
 int /*<<< orphan*/  tg3_netif_stop (struct tg3*) ; 
 int /*<<< orphan*/  tg3_phy_start (struct tg3*) ; 
 int /*<<< orphan*/  tg3_phy_stop (struct tg3*) ; 
 int tg3_restart_hw (struct tg3*,int) ; 
 int /*<<< orphan*/  tg3_set_mtu (struct net_device*,struct tg3*,int) ; 

__attribute__((used)) static int tg3_change_mtu(struct net_device *dev, int new_mtu)
{
	struct tg3 *tp = netdev_priv(dev);
	int err;
	bool reset_phy = false;

	if (new_mtu < TG3_MIN_MTU || new_mtu > TG3_MAX_MTU(tp))
		return -EINVAL;

	if (!netif_running(dev)) {
		/* We'll just catch it later when the
		 * device is up'd.
		 */
		tg3_set_mtu(dev, tp, new_mtu);
		return 0;
	}

	tg3_phy_stop(tp);

	tg3_netif_stop(tp);

	tg3_full_lock(tp, 1);

	tg3_halt(tp, RESET_KIND_SHUTDOWN, 1);

	tg3_set_mtu(dev, tp, new_mtu);

	/* Reset PHY, otherwise the read DMA engine will be in a mode that
	 * breaks all requests to 256 bytes.
	 */
	if (tg3_asic_rev(tp) == ASIC_REV_57766)
		reset_phy = true;

	err = tg3_restart_hw(tp, reset_phy);

	if (!err)
		tg3_netif_start(tp);

	tg3_full_unlock(tp);

	if (!err)
		tg3_phy_start(tp);

	return err;
}