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
typedef  void* u8 ;
struct r8192_priv {int /*<<< orphan*/  rate_adaptive; } ;
struct net_device {int dummy; } ;
typedef  int s32 ;
typedef  TYPE_1__* prate_adaptive ;
struct TYPE_4__ {void** rf_rssi; void* cck_method; void* diff_TH; void* SS_TH_low; void* DbgMode; void* Enable; } ;
struct TYPE_3__ {int ping_rssi_thresh_for_ra; void* ping_rssi_enable; } ;

/* Variables and functions */
 int CCK_Rx_Version_1 ; 
 int CCK_Rx_Version_MAX ; 
 TYPE_2__ DM_RxPathSelTable ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

extern void
dm_change_rxpath_selection_setting(
	struct net_device *dev,
	s32		DM_Type,
	s32		DM_Value)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	prate_adaptive 	pRA = (prate_adaptive)&(priv->rate_adaptive);


	if(DM_Type == 0)
	{
		if(DM_Value > 1)
			DM_Value = 1;
		DM_RxPathSelTable.Enable = (u8)DM_Value;
	}
	else if(DM_Type == 1)
	{
		if(DM_Value > 1)
			DM_Value = 1;
		DM_RxPathSelTable.DbgMode = (u8)DM_Value;
	}
	else if(DM_Type == 2)
	{
		if(DM_Value > 40)
			DM_Value = 40;
		DM_RxPathSelTable.SS_TH_low = (u8)DM_Value;
	}
	else if(DM_Type == 3)
	{
		if(DM_Value > 25)
			DM_Value = 25;
		DM_RxPathSelTable.diff_TH = (u8)DM_Value;
	}
	else if(DM_Type == 4)
	{
		if(DM_Value >= CCK_Rx_Version_MAX)
			DM_Value = CCK_Rx_Version_1;
		DM_RxPathSelTable.cck_method= (u8)DM_Value;
	}
	else if(DM_Type == 10)
	{
		if(DM_Value > 100)
			DM_Value = 50;
		DM_RxPathSelTable.rf_rssi[0] = (u8)DM_Value;
	}
	else if(DM_Type == 11)
	{
		if(DM_Value > 100)
			DM_Value = 50;
		DM_RxPathSelTable.rf_rssi[1] = (u8)DM_Value;
	}
	else if(DM_Type == 12)
	{
		if(DM_Value > 100)
			DM_Value = 50;
		DM_RxPathSelTable.rf_rssi[2] = (u8)DM_Value;
	}
	else if(DM_Type == 13)
	{
		if(DM_Value > 100)
			DM_Value = 50;
		DM_RxPathSelTable.rf_rssi[3] = (u8)DM_Value;
	}
	else if(DM_Type == 20)
	{
		if(DM_Value > 1)
			DM_Value = 1;
		pRA->ping_rssi_enable = (u8)DM_Value;
	}
	else if(DM_Type == 21)
	{
		if(DM_Value > 30)
			DM_Value = 30;
		pRA->ping_rssi_thresh_for_ra = DM_Value;
	}
}