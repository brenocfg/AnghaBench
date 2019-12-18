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
struct r8192_priv {scalar_t__ bInHctTest; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ mActingAsAp; } ;
struct TYPE_4__ {TYPE_1__ MgntInfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_dm_CheckRateAdaptive (struct net_device*) ; 
 TYPE_2__* Adapter ; 
 int /*<<< orphan*/  dm_CheckAggrPolicy (struct net_device*) ; 
 int /*<<< orphan*/  dm_CheckProtection (struct net_device*) ; 
 int /*<<< orphan*/  dm_bandwidth_autoswitch (struct net_device*) ; 
 int /*<<< orphan*/  dm_check_edca_turbo (struct net_device*) ; 
 int /*<<< orphan*/  dm_check_fsync (struct net_device*) ; 
 int /*<<< orphan*/  dm_check_pbc_gpio (struct net_device*) ; 
 int /*<<< orphan*/  dm_check_rate_adaptive (struct net_device*) ; 
 int /*<<< orphan*/  dm_check_rfctrl_gpio (struct net_device*) ; 
 int /*<<< orphan*/  dm_check_rx_path_selection (struct net_device*) ; 
 int /*<<< orphan*/  dm_check_txpower_tracking (struct net_device*) ; 
 int /*<<< orphan*/  dm_check_txrateandretrycount (struct net_device*) ; 
 int /*<<< orphan*/  dm_ctrl_initgain_byrssi (struct net_device*) ; 
 int /*<<< orphan*/  dm_ctstoself (struct net_device*) ; 
 int /*<<< orphan*/  dm_dynamic_txpower (struct net_device*) ; 
 int /*<<< orphan*/  dm_send_rssi_tofw (struct net_device*) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

extern  void    hal_dm_watchdog(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);

	if(priv->bInHctTest)
		return;


	dm_check_rfctrl_gpio(dev);

	// Add by hpfan 2008-03-11
	dm_check_pbc_gpio(dev);
	dm_check_txrateandretrycount(dev); //moved by tynli
	dm_check_edca_turbo(dev);

	dm_CheckAggrPolicy(dev);

#ifdef TO_DO_LIST
	dm_CheckProtection(dev);
#endif

	// ====================================================
	// If any dynamic mechanism is ready, put it above this return;
	// ====================================================
	//if (IS_HARDWARE_TYPE_8192S(dev))
	return;

#ifdef TO_DO_LIST
	if(Adapter->MgntInfo.mActingAsAp)
	{
		AP_dm_CheckRateAdaptive(dev);
		//return;
	}
	else
#endif
	{
		dm_check_rate_adaptive(dev);
	}
	dm_dynamic_txpower(dev);

	dm_check_txpower_tracking(dev);
	dm_ctrl_initgain_byrssi(dev);//LZM TMP 090302

	dm_bandwidth_autoswitch(dev);

	dm_check_rx_path_selection(dev);//LZM TMP 090302
	dm_check_fsync(dev);

	dm_send_rssi_tofw(dev);

	dm_ctstoself(dev);

}