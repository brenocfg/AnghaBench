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
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  phy_id; } ;
struct nic {scalar_t__ phy; TYPE_1__ mii; int /*<<< orphan*/  blink_timer; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  E100_82552_LED_OVERRIDE ; 
 int HZ ; 
 int MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  MII_LED_CONTROL ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mdio_write (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 struct nic* netdev_priv (struct net_device*) ; 
 scalar_t__ phy_82552_v ; 

__attribute__((used)) static int e100_phys_id(struct net_device *netdev, u32 data)
{
	struct nic *nic = netdev_priv(netdev);
	u16 led_reg = (nic->phy == phy_82552_v) ? E100_82552_LED_OVERRIDE :
	              MII_LED_CONTROL;

	if (!data || data > (u32)(MAX_SCHEDULE_TIMEOUT / HZ))
		data = (u32)(MAX_SCHEDULE_TIMEOUT / HZ);
	mod_timer(&nic->blink_timer, jiffies);
	msleep_interruptible(data * 1000);
	del_timer_sync(&nic->blink_timer);
	mdio_write(netdev, nic->mii.phy_id, led_reg, 0);

	return 0;
}