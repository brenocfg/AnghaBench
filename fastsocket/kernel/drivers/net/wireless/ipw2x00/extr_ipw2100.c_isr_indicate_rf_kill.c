#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ipw2100_priv {int /*<<< orphan*/  rf_kill; scalar_t__ stop_rf_kill; int /*<<< orphan*/  status; TYPE_3__* ieee; TYPE_1__* net_dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  wiphy; } ;
struct TYPE_6__ {TYPE_2__ wdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  HZ ; 
 int /*<<< orphan*/  IPW_DEBUG_INFO (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATUS_RF_KILL_HW ; 
 int /*<<< orphan*/  cancel_delayed_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  round_jiffies_relative (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wiphy_rfkill_set_hw_state (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void isr_indicate_rf_kill(struct ipw2100_priv *priv, u32 status)
{
	IPW_DEBUG_INFO("%s: RF Kill state changed to radio OFF.\n",
		       priv->net_dev->name);

	/* RF_KILL is now enabled (else we wouldn't be here) */
	wiphy_rfkill_set_hw_state(priv->ieee->wdev.wiphy, true);
	priv->status |= STATUS_RF_KILL_HW;

	/* Make sure the RF Kill check timer is running */
	priv->stop_rf_kill = 0;
	cancel_delayed_work(&priv->rf_kill);
	schedule_delayed_work(&priv->rf_kill, round_jiffies_relative(HZ));
}