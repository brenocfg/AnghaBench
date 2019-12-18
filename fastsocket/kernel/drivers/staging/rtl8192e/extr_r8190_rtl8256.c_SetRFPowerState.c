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
struct r8192_priv {scalar_t__ bHwRfOffAction; TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ eRFPowerState; } ;
typedef  scalar_t__ RT_RF_POWER_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_POWER ; 
 int /*<<< orphan*/  COMP_RF ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int) ; 
 int SetRFPowerState8190 (struct net_device*,scalar_t__) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

__attribute__((used)) static bool
SetRFPowerState(
	struct net_device* dev,
	RT_RF_POWER_STATE	eRFPowerState
	)
{
	struct r8192_priv *priv = ieee80211_priv(dev);

	bool bResult = false;

	RT_TRACE(COMP_RF,"---------> SetRFPowerState(): eRFPowerState(%d)\n", eRFPowerState);
#ifdef RTL8192E
	if(eRFPowerState == priv->ieee80211->eRFPowerState && priv->bHwRfOffAction == 0)
#else
	if(eRFPowerState == priv->ieee80211->eRFPowerState)
#endif
	{
		RT_TRACE(COMP_POWER, "<--------- SetRFPowerState(): discard the request for eRFPowerState(%d) is the same.\n", eRFPowerState);
		return bResult;
	}

	bResult = SetRFPowerState8190(dev, eRFPowerState);

	RT_TRACE(COMP_POWER, "<--------- SetRFPowerState(): bResult(%d)\n", bResult);

	return bResult;
}