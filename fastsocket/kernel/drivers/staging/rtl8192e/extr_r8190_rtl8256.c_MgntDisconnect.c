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
typedef  int /*<<< orphan*/  u8 ;
struct r8192_priv {TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ mPss; scalar_t__ mActingAsAp; int /*<<< orphan*/  AwakeTimer; } ;
struct TYPE_3__ {scalar_t__ state; scalar_t__ iw_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_DisassociateAllStation (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Adapter ; 
 int /*<<< orphan*/  COMP_MLME ; 
 int /*<<< orphan*/  DBG_LOUD ; 
 scalar_t__ IEEE80211_LINKED ; 
 scalar_t__ IW_MODE_ADHOC ; 
 scalar_t__ IW_MODE_INFRA ; 
 int /*<<< orphan*/  MgntDisconnectAP (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MgntDisconnectIBSS (struct net_device*) ; 
 int /*<<< orphan*/  PlatformSetTimer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int TRUE ; 
 scalar_t__ eAwake ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 TYPE_2__* pMgntInfo ; 
 int /*<<< orphan*/  unspec_reason ; 

__attribute__((used)) static bool
MgntDisconnect(
	struct net_device* dev,
	u8 asRsn
)
{
	struct r8192_priv *priv = ieee80211_priv(dev);

	//
	// Schedule an workitem to wake up for ps mode, 070109, by rcnjko.
	//
#ifdef TO_DO
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
	// Follow 8180 AP mode, 2005.05.30, by rcnjko.
#ifdef TO_DO
	if(pMgntInfo->mActingAsAp)
	{
		RT_TRACE(COMP_MLME, DBG_LOUD, ("MgntDisconnect() ===> AP_DisassociateAllStation\n"));
		AP_DisassociateAllStation(Adapter, unspec_reason);
		return TRUE;
	}
#endif
	// Indication of disassociation event.
	//DrvIFIndicateDisassociation(Adapter, asRsn);

	// In adhoc mode, update beacon frame.
	if( priv->ieee80211->state == IEEE80211_LINKED )
	{
		if( priv->ieee80211->iw_mode == IW_MODE_ADHOC )
		{
			//RT_TRACE(COMP_MLME, "MgntDisconnect() ===> MgntDisconnectIBSS\n");
			MgntDisconnectIBSS(dev);
		}
		if( priv->ieee80211->iw_mode == IW_MODE_INFRA )
		{
			// We clear key here instead of MgntDisconnectAP() because that
			// MgntActSet_802_11_DISASSOCIATE() is an interface called by OS,
			// e.g. OID_802_11_DISASSOCIATE in Windows while as MgntDisconnectAP() is
			// used to handle disassociation related things to AP, e.g. send Disassoc
			// frame to AP.  2005.01.27, by rcnjko.
			//IEEE80211_DEBUG(IEEE80211_DL_TRACE,"MgntDisconnect() ===> MgntDisconnectAP\n");
			MgntDisconnectAP(dev, asRsn);
		}

		// Inidicate Disconnect, 2005.02.23, by rcnjko.
		//MgntIndicateMediaStatus( Adapter, RT_MEDIA_DISCONNECT, GENERAL_INDICATE);
	}

	return true;
}