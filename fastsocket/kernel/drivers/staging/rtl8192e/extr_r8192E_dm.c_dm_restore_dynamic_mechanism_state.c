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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {scalar_t__ rate_adaptive_disabled; int /*<<< orphan*/  last_ratr; } ;
struct r8192_priv {scalar_t__ rf_type; scalar_t__ btxpower_tracking; scalar_t__ btxpower_trackingInit; TYPE_1__* ieee80211; TYPE_2__ rate_adaptive; int /*<<< orphan*/  up; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {scalar_t__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_RATE ; 
 int /*<<< orphan*/  RATE_ALL_OFDM_2SS ; 
 int /*<<< orphan*/  RATR0 ; 
 scalar_t__ RF_1T2R ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UFWP ; 
 scalar_t__ WIRELESS_MODE_N_24G ; 
 scalar_t__ WIRELESS_MODE_N_5G ; 
 int /*<<< orphan*/  dm_bb_initialgain_restore (struct net_device*) ; 
 int /*<<< orphan*/  dm_txpower_reset_recovery (struct net_device*) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void dm_restore_dynamic_mechanism_state(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	u32 	reg_ratr = priv->rate_adaptive.last_ratr;

	if(!priv->up)
	{
		RT_TRACE(COMP_RATE, "<---- dm_restore_dynamic_mechanism_state(): driver is going to unload\n");
		return;
	}

	//
	// Restore previous state for rate adaptive
	//
	if(priv->rate_adaptive.rate_adaptive_disabled)
		return;
	// TODO: Only 11n mode is implemented currently,
	if( !(priv->ieee80211->mode==WIRELESS_MODE_N_24G ||
		 priv->ieee80211->mode==WIRELESS_MODE_N_5G))
		 return;
	{
			/* 2007/11/15 MH Copy from 8190PCI. */
			u32 ratr_value;
			ratr_value = reg_ratr;
			if(priv->rf_type == RF_1T2R)	// 1T2R, Spatial Stream 2 should be disabled
			{
				ratr_value &=~ (RATE_ALL_OFDM_2SS);
				//DbgPrint("HW_VAR_TATR_0 from 0x%x ==> 0x%x\n", ((pu4Byte)(val))[0], ratr_value);
			}
			//DbgPrint("set HW_VAR_TATR_0 = 0x%x\n", ratr_value);
			//cosa PlatformEFIOWrite4Byte(Adapter, RATR0, ((pu4Byte)(val))[0]);
			write_nic_dword(dev, RATR0, ratr_value);
			write_nic_byte(dev, UFWP, 1);
	}
	//Resore TX Power Tracking Index
	if(priv->btxpower_trackingInit && priv->btxpower_tracking){
		dm_txpower_reset_recovery(dev);
	}

	//
	//Restore BB Initial Gain
	//
	dm_bb_initialgain_restore(dev);

}