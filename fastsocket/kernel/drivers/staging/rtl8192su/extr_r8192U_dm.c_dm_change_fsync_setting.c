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
typedef  scalar_t__ u8 ;
struct r8192_priv {scalar_t__ framesyncMonitor; } ;
struct net_device {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

extern	void
dm_change_fsync_setting(
	struct net_device *dev,
	s32		DM_Type,
	s32		DM_Value)
{
	struct r8192_priv *priv = ieee80211_priv(dev);

	if (DM_Type == 0)	// monitor 0xc38 register
	{
		if(DM_Value > 1)
			DM_Value = 1;
		priv->framesyncMonitor = (u8)DM_Value;
		//DbgPrint("pHalData->framesyncMonitor = %d", pHalData->framesyncMonitor);
	}
}