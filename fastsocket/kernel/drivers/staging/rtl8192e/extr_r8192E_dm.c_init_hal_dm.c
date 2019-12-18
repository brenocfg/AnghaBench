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
struct r8192_priv {int undecorated_smoothed_pwdb; int /*<<< orphan*/  gpio_change_rf_wq; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_dig_init (struct net_device*) ; 
 int /*<<< orphan*/  dm_gpio_change_rf_callback ; 
 int /*<<< orphan*/  dm_init_bandwidth_autoswitch (struct net_device*) ; 
 int /*<<< orphan*/  dm_init_ctstoself (struct net_device*) ; 
 int /*<<< orphan*/  dm_init_dynamic_txpower (struct net_device*) ; 
 int /*<<< orphan*/  dm_init_edca_turbo (struct net_device*) ; 
 int /*<<< orphan*/  dm_init_fsync (struct net_device*) ; 
 int /*<<< orphan*/  dm_init_rxpath_selection (struct net_device*) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  init_rate_adaptive (struct net_device*) ; 

void init_hal_dm(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);

	// Undecorated Smoothed Signal Strength, it can utilized to dynamic mechanism.
	priv->undecorated_smoothed_pwdb = -1;

	//Initial TX Power Control for near/far range , add by amy 2008/05/15, porting from windows code.
	dm_init_dynamic_txpower(dev);
	init_rate_adaptive(dev);
	//dm_initialize_txpower_tracking(dev);
	dm_dig_init(dev);
	dm_init_edca_turbo(dev);
	dm_init_bandwidth_autoswitch(dev);
	dm_init_fsync(dev);
	dm_init_rxpath_selection(dev);
	dm_init_ctstoself(dev);
#ifdef RTL8192E
	INIT_DELAYED_WORK(&priv->gpio_change_rf_wq,  dm_gpio_change_rf_callback);
#endif

}