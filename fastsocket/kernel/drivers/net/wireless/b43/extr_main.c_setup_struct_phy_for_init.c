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
struct b43_wldev {int dummy; } ;
struct b43_phy {int hardware_power_control; int phy_locked; int radio_locked; int /*<<< orphan*/  txerr_cnt; int /*<<< orphan*/  next_txpwr_check_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43_PHY_TX_BADNESS_LIMIT ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  modparam_hwpctl ; 

__attribute__((used)) static void setup_struct_phy_for_init(struct b43_wldev *dev,
				      struct b43_phy *phy)
{
	phy->hardware_power_control = !!modparam_hwpctl;
	phy->next_txpwr_check_time = jiffies;
	/* PHY TX errors counter. */
	atomic_set(&phy->txerr_cnt, B43_PHY_TX_BADNESS_LIMIT);

#if B43_DEBUG
	phy->phy_locked = false;
	phy->radio_locked = false;
#endif
}