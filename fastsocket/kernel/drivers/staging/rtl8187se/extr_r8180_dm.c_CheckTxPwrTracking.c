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
struct r8180_priv {scalar_t__ bToUpdateTxPwr; int /*<<< orphan*/  bTxPowerTrack; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ ieee80211_priv (struct net_device*) ; 

bool
CheckTxPwrTracking(	struct net_device *dev)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);

	if(!priv->bTxPowerTrack)
	{
		return false;
	}

//lzm reserved 080826
	//if(priv->bScanInProgress)
	//{
	//	return false;
	//}

	//if 87SE is in High Power , don't do Tx Power Tracking. asked by SD3 ED. 2008-08-08 Isaiah
	if(priv->bToUpdateTxPwr)
	{
		return false;
	}

	return true;
}