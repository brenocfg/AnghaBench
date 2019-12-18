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
typedef  int u32 ;
struct ipw2100_priv {int hw_features; int /*<<< orphan*/  status; TYPE_2__* ieee; int /*<<< orphan*/  net_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  wiphy; } ;
struct TYPE_4__ {TYPE_1__ wdev; } ;

/* Variables and functions */
 int HW_FEATURE_RFKILL ; 
 int IPW_BIT_GPIO_RF_KILL ; 
 int /*<<< orphan*/  IPW_REG_GPIO ; 
 int MAX_RF_KILL_CHECKS ; 
 int /*<<< orphan*/  RF_KILL_CHECK_DELAY ; 
 int /*<<< orphan*/  STATUS_RF_KILL_HW ; 
 int /*<<< orphan*/  read_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_rfkill_set_hw_state (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rf_kill_active(struct ipw2100_priv *priv)
{
#define MAX_RF_KILL_CHECKS 5
#define RF_KILL_CHECK_DELAY 40

	unsigned short value = 0;
	u32 reg = 0;
	int i;

	if (!(priv->hw_features & HW_FEATURE_RFKILL)) {
		wiphy_rfkill_set_hw_state(priv->ieee->wdev.wiphy, false);
		priv->status &= ~STATUS_RF_KILL_HW;
		return 0;
	}

	for (i = 0; i < MAX_RF_KILL_CHECKS; i++) {
		udelay(RF_KILL_CHECK_DELAY);
		read_register(priv->net_dev, IPW_REG_GPIO, &reg);
		value = (value << 1) | ((reg & IPW_BIT_GPIO_RF_KILL) ? 0 : 1);
	}

	if (value == 0) {
		wiphy_rfkill_set_hw_state(priv->ieee->wdev.wiphy, true);
		priv->status |= STATUS_RF_KILL_HW;
	} else {
		wiphy_rfkill_set_hw_state(priv->ieee->wdev.wiphy, false);
		priv->status &= ~STATUS_RF_KILL_HW;
	}

	return (value == 0);
}