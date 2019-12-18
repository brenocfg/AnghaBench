#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct nic {scalar_t__ mac; int flags; int /*<<< orphan*/  watchdog; int /*<<< orphan*/  netdev; int /*<<< orphan*/  cmd_lock; TYPE_2__* csr; int /*<<< orphan*/  mii; } ;
struct ethtool_cmd {scalar_t__ duplex; int /*<<< orphan*/  cmd; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmd_hi; } ;
struct TYPE_4__ {TYPE_1__ scb; } ;

/* Variables and functions */
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ DUPLEX_HALF ; 
 scalar_t__ E100_WATCHDOG_PERIOD ; 
 int /*<<< orphan*/  ETHTOOL_GSET ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 int /*<<< orphan*/  e100_adjust_adaptive_ifs (struct nic*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  e100_set_multicast_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e100_update_stats (struct nic*) ; 
 int /*<<< orphan*/  e100_write_flush (struct nic*) ; 
 scalar_t__ ethtool_cmd_speed (struct ethtool_cmd*) ; 
 int ich ; 
 int ich_10h_workaround ; 
 int ioread8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite8 (int,int /*<<< orphan*/ *) ; 
 int irq_sw_gen ; 
 scalar_t__ jiffies ; 
 scalar_t__ mac_82557_D100_C ; 
 int /*<<< orphan*/  mii_check_link (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mii_ethtool_gset (int /*<<< orphan*/ *,struct ethtool_cmd*) ; 
 scalar_t__ mii_link_ok (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_printk (struct nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  round_jiffies (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void e100_watchdog(unsigned long data)
{
	struct nic *nic = (struct nic *)data;
	struct ethtool_cmd cmd = { .cmd = ETHTOOL_GSET };
	u32 speed;

	netif_printk(nic, timer, KERN_DEBUG, nic->netdev,
		     "right now = %ld\n", jiffies);

	/* mii library handles link maintenance tasks */

	mii_ethtool_gset(&nic->mii, &cmd);
	speed = ethtool_cmd_speed(&cmd);

	if (mii_link_ok(&nic->mii) && !netif_carrier_ok(nic->netdev)) {
		netdev_info(nic->netdev, "NIC Link is Up %u Mbps %s Duplex\n",
			    speed == SPEED_100 ? 100 : 10,
			    cmd.duplex == DUPLEX_FULL ? "Full" : "Half");
	} else if (!mii_link_ok(&nic->mii) && netif_carrier_ok(nic->netdev)) {
		netdev_info(nic->netdev, "NIC Link is Down\n");
	}

	mii_check_link(&nic->mii);

	/* Software generated interrupt to recover from (rare) Rx
	 * allocation failure.
	 * Unfortunately have to use a spinlock to not re-enable interrupts
	 * accidentally, due to hardware that shares a register between the
	 * interrupt mask bit and the SW Interrupt generation bit */
	spin_lock_irq(&nic->cmd_lock);
	iowrite8(ioread8(&nic->csr->scb.cmd_hi) | irq_sw_gen,&nic->csr->scb.cmd_hi);
	e100_write_flush(nic);
	spin_unlock_irq(&nic->cmd_lock);

	e100_update_stats(nic);
	e100_adjust_adaptive_ifs(nic, speed, cmd.duplex);

	if (nic->mac <= mac_82557_D100_C)
		/* Issue a multicast command to workaround a 557 lock up */
		e100_set_multicast_list(nic->netdev);

	if (nic->flags & ich && speed == SPEED_10 && cmd.duplex == DUPLEX_HALF)
		/* Need SW workaround for ICH[x] 10Mbps/half duplex Tx hang. */
		nic->flags |= ich_10h_workaround;
	else
		nic->flags &= ~ich_10h_workaround;

	mod_timer(&nic->watchdog,
		  round_jiffies(jiffies + E100_WATCHDOG_PERIOD));
}