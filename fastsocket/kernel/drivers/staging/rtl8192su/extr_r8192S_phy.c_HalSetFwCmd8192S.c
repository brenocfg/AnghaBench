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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct r8192_priv {scalar_t__ CurrentFwCmdIO; scalar_t__ SetFwCmdInProgress; scalar_t__ bInHctTest; } ;
struct net_device {int dummy; } ;
typedef  scalar_t__ FW_CMD_IO_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_CMD ; 
 int /*<<< orphan*/  COMP_ERR ; 
 scalar_t__ FW_CMD_DIG_HALT ; 
 scalar_t__ FW_CMD_DIG_RESUME ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ TRUE ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_SetFwCmdIOCallback (struct net_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

bool HalSetFwCmd8192S(struct net_device* dev, FW_CMD_IO_TYPE	FwCmdIO)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	u16	FwCmdWaitCounter = 0;

	u16	FwCmdWaitLimit = 1000;

	//if(IS_HARDWARE_TYPE_8192SU(Adapter) && Adapter->bInHctTest)
	if(priv->bInHctTest)
		return true;

	RT_TRACE(COMP_CMD, "-->HalSetFwCmd8192S(): Set FW Cmd(%x), SetFwCmdInProgress(%d)\n", (u32)FwCmdIO, priv->SetFwCmdInProgress);

	// Will be done by high power respectively.
	if(FwCmdIO==FW_CMD_DIG_HALT || FwCmdIO==FW_CMD_DIG_RESUME)
	{
		RT_TRACE(COMP_CMD, "<--HalSetFwCmd8192S(): Set FW Cmd(%x)\n", (u32)FwCmdIO);
		return false;
	}

#if 1
	while(priv->SetFwCmdInProgress && FwCmdWaitCounter<FwCmdWaitLimit)
	{
		//if(RT_USB_CANNOT_IO(Adapter))
		//{
		//	RT_TRACE(COMP_CMD, DBG_WARNING, ("HalSetFwCmd8192S(): USB can NOT IO!!\n"));
		//	return FALSE;
		//}

		RT_TRACE(COMP_CMD, "HalSetFwCmd8192S(): previous workitem not finish!!\n");
		return false;
		FwCmdWaitCounter ++;
		RT_TRACE(COMP_CMD, "HalSetFwCmd8192S(): Wait 10 ms (%d times)...\n", FwCmdWaitCounter);
		udelay(100);
	}

	if(FwCmdWaitCounter == FwCmdWaitLimit)
	{
		//RT_ASSERT(FALSE, ("SetFwCmdIOWorkItemCallback(): Wait too logn to set FW CMD\n"));
		RT_TRACE(COMP_CMD, "HalSetFwCmd8192S(): Wait too logn to set FW CMD\n");
		//return false;
	}
#endif
	if (priv->SetFwCmdInProgress)
	{
		RT_TRACE(COMP_ERR, "<--HalSetFwCmd8192S(): Set FW Cmd(%#x)\n", FwCmdIO);
		return false;
	}
	priv->SetFwCmdInProgress = TRUE;
	priv->CurrentFwCmdIO = FwCmdIO; // Update current FW Cmd for callback use.

	phy_SetFwCmdIOCallback(dev);
	return true;
}