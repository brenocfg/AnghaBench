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
typedef  int u16 ;
struct r8192_priv {int RFChangeInProgress; int /*<<< orphan*/  rf_ps_lock; TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int eRFPowerState; int /*<<< orphan*/  RfOffReason; } ;
typedef  int RT_RF_POWER_STATE ;
typedef  int /*<<< orphan*/  RT_RF_CHANGE_SOURCE ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  COMP_POWER ; 
 int /*<<< orphan*/  MgntDisconnect (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_CHANGE_BY_HW ; 
 int /*<<< orphan*/  RF_CHANGE_BY_IPS ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SetRFPowerState (struct net_device*,int) ; 
 int /*<<< orphan*/  disas_lv_ss ; 
#define  eRfOff 130 
#define  eRfOn 129 
#define  eRfSleep 128 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

bool
MgntActSet_RF_State(
	struct net_device* dev,
	RT_RF_POWER_STATE	StateToSet,
	RT_RF_CHANGE_SOURCE ChangeSource
	)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	bool 			bActionAllowed = false;
	bool 			bConnectBySSID = false;
	RT_RF_POWER_STATE	rtState;
	u16					RFWaitCounter = 0;
	unsigned long flag;
	RT_TRACE(COMP_POWER, "===>MgntActSet_RF_State(): StateToSet(%d)\n",StateToSet);

	//1//
	//1//<1>Prevent the race condition of RF state change.
	//1//
	// Only one thread can change the RF state at one time, and others should wait to be executed. By Bruce, 2007-11-28.

	while(true)
	{
		spin_lock_irqsave(&priv->rf_ps_lock,flag);
		if(priv->RFChangeInProgress)
		{
			spin_unlock_irqrestore(&priv->rf_ps_lock,flag);
			RT_TRACE(COMP_POWER, "MgntActSet_RF_State(): RF Change in progress! Wait to set..StateToSet(%d).\n", StateToSet);

			// Set RF after the previous action is done.
			while(priv->RFChangeInProgress)
			{
				RFWaitCounter ++;
				RT_TRACE(COMP_POWER, "MgntActSet_RF_State(): Wait 1 ms (%d times)...\n", RFWaitCounter);
				udelay(1000); // 1 ms

				// Wait too long, return FALSE to avoid to be stuck here.
				if(RFWaitCounter > 100)
				{
					RT_TRACE(COMP_ERR, "MgntActSet_RF_State(): Wait too logn to set RF\n");
					// TODO: Reset RF state?
					return false;
				}
			}
		}
		else
		{
			priv->RFChangeInProgress = true;
			spin_unlock_irqrestore(&priv->rf_ps_lock,flag);
			break;
		}
	}

	rtState = priv->ieee80211->eRFPowerState;

	switch(StateToSet)
	{
	case eRfOn:
		//
		// Turn On RF no matter the IPS setting because we need to update the RF state to Ndis under Vista, or
		// the Windows does not allow the driver to perform site survey any more. By Bruce, 2007-10-02.
		//

		priv->ieee80211->RfOffReason &= (~ChangeSource);

		if(! priv->ieee80211->RfOffReason)
		{
			priv->ieee80211->RfOffReason = 0;
			bActionAllowed = true;


			if(rtState == eRfOff && ChangeSource >=RF_CHANGE_BY_HW )
			{
				bConnectBySSID = true;
			}
		}
		else
			RT_TRACE(COMP_POWER, "MgntActSet_RF_State - eRfon reject pMgntInfo->RfOffReason= 0x%x, ChangeSource=0x%X\n", priv->ieee80211->RfOffReason, ChangeSource);

		break;

	case eRfOff:

			if (priv->ieee80211->RfOffReason > RF_CHANGE_BY_IPS)
			{
				//
				// 060808, Annie:
				// Disconnect to current BSS when radio off. Asked by QuanTa.
				//
				// Set all link status falg, by Bruce, 2007-06-26.
				//MgntActSet_802_11_DISASSOCIATE( Adapter, disas_lv_ss );
				MgntDisconnect(dev, disas_lv_ss);

				// Clear content of bssDesc[] and bssDesc4Query[] to avoid reporting old bss to UI.
				// 2007.05.28, by shien chang.

			}


		priv->ieee80211->RfOffReason |= ChangeSource;
		bActionAllowed = true;
		break;

	case eRfSleep:
		priv->ieee80211->RfOffReason |= ChangeSource;
		bActionAllowed = true;
		break;

	default:
		break;
	}

	if(bActionAllowed)
	{
		RT_TRACE(COMP_POWER, "MgntActSet_RF_State(): Action is allowed.... StateToSet(%d), RfOffReason(%#X)\n", StateToSet, priv->ieee80211->RfOffReason);
				// Config HW to the specified mode.
		SetRFPowerState(dev, StateToSet);
		// Turn on RF.
		if(StateToSet == eRfOn)
		{
			//Adapter->HalFunc.HalEnableRxHandler(Adapter);
			if(bConnectBySSID)
			{
				//MgntActSet_802_11_SSID(Adapter, Adapter->MgntInfo.Ssid.Octet, Adapter->MgntInfo.Ssid.Length, TRUE );
			}
		}
		// Turn off RF.
		else if(StateToSet == eRfOff)
		{
			//Adapter->HalFunc.HalDisableRxHandler(Adapter);
		}
	}
	else
	{
		RT_TRACE(COMP_POWER, "MgntActSet_RF_State(): Action is rejected.... StateToSet(%d), ChangeSource(%#X), RfOffReason(%#X)\n", StateToSet, ChangeSource, priv->ieee80211->RfOffReason);
	}

	// Release RF spinlock
	spin_lock_irqsave(&priv->rf_ps_lock,flag);
	priv->RFChangeInProgress = false;
	spin_unlock_irqrestore(&priv->rf_ps_lock,flag);

	RT_TRACE(COMP_POWER, "<===MgntActSet_RF_State()\n");
	return bActionAllowed;
}