#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct r8180_priv {TYPE_2__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {scalar_t__ state; scalar_t__ iw_mode; } ;
struct TYPE_4__ {scalar_t__ mPss; int /*<<< orphan*/  AwakeTimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  Adapter ; 
 int /*<<< orphan*/  Dot11d_Reset (TYPE_2__*) ; 
 scalar_t__ IEEE80211_LINKED ; 
 scalar_t__ IS_DOT11D_ENABLE (TYPE_2__*) ; 
 scalar_t__ IW_MODE_ADHOC ; 
 scalar_t__ IW_MODE_INFRA ; 
 int /*<<< orphan*/  MgntDisconnectAP (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MgntDisconnectIBSS (struct net_device*) ; 
 int /*<<< orphan*/  PlatformSetTimer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ eAwake ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 TYPE_1__* pMgntInfo ; 

bool
MgntDisconnect(
	struct net_device *dev,
	u8			asRsn
)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);
	//
	// Schedule an workitem to wake up for ps mode, 070109, by rcnjko.
	//
#ifdef TODO
	if(pMgntInfo->mPss != eAwake)
	{
		//
		// Using AwkaeTimer to prevent mismatch ps state.
		// In the timer the state will be changed according to the RF is being awoke or not. By Bruce, 2007-10-31.
		//
		// PlatformScheduleWorkItem( &(pMgntInfo->AwakeWorkItem) );
		PlatformSetTimer( Adapter, &(pMgntInfo->AwakeTimer), 0 );
	}
#endif

	// Indication of disassociation event.
	//DrvIFIndicateDisassociation(Adapter, asRsn);
	if(IS_DOT11D_ENABLE(priv->ieee80211))
		Dot11d_Reset(priv->ieee80211);
	// In adhoc mode, update beacon frame.
	if( priv->ieee80211->state == IEEE80211_LINKED )
	{
		if( priv->ieee80211->iw_mode == IW_MODE_ADHOC )
		{
//			RT_TRACE(COMP_MLME, DBG_LOUD, ("MgntDisconnect() ===> MgntDisconnectIBSS\n"));
			//printk("MgntDisconnect() ===> MgntDisconnectIBSS\n");
			MgntDisconnectIBSS(dev);
		}
		if( priv->ieee80211->iw_mode == IW_MODE_INFRA )
		{
			// We clear key here instead of MgntDisconnectAP() because that
			// MgntActSet_802_11_DISASSOCIATE() is an interface called by OS,
			// e.g. OID_802_11_DISASSOCIATE in Windows while as MgntDisconnectAP() is
			// used to handle disassociation related things to AP, e.g. send Disassoc
			// frame to AP.  2005.01.27, by rcnjko.
//			SecClearAllKeys(Adapter);

//			RT_TRACE(COMP_MLME, DBG_LOUD, ("MgntDisconnect() ===> MgntDisconnectAP\n"));
			//printk("MgntDisconnect() ===> MgntDisconnectAP\n");
			MgntDisconnectAP(dev, asRsn);
		}

		// Inidicate Disconnect, 2005.02.23, by rcnjko.
//		MgntIndicateMediaStatus( Adapter, RT_MEDIA_DISCONNECT, GENERAL_INDICATE);
	}

	return true;
}