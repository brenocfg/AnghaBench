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
struct r8192_priv {int IrpPendingCount; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  RESET_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_RESET ; 
 int FALSE ; 
 scalar_t__ HalRxCheckStuck819xUsb (struct net_device*) ; 
 int /*<<< orphan*/  RESET_TYPE_NORESET ; 
 int /*<<< orphan*/  RESET_TYPE_SILENT ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*) ; 
 int TRUE ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

RESET_TYPE
RxCheckStuck(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	//int                     i;
	bool        bRxCheck = FALSE;

//       RT_TRACE(COMP_RESET," ==> RxCheckStuck()\n");
	//PlatformAcquireSpinLock(Adapter, RT_RX_SPINLOCK);

	 if(priv->IrpPendingCount > 1)
	 	bRxCheck = TRUE;
       //PlatformReleaseSpinLock(Adapter, RT_RX_SPINLOCK);

//       RT_TRACE(COMP_RESET,"bRxCheck is %d \n",bRxCheck);
	if(bRxCheck)
	{
		if(HalRxCheckStuck819xUsb(dev))
		{
			RT_TRACE(COMP_RESET, "RxStuck Condition\n");
			return RESET_TYPE_SILENT;
		}
	}
	return RESET_TYPE_NORESET;
}