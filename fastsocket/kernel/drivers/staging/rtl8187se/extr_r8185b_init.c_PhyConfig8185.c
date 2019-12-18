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
struct r8180_priv {int RFProgType; int rf_chip; int InitialGain; int InitialGainBackUp; scalar_t__ bTxPowerTrack; scalar_t__ bDigMechanism; int /*<<< orphan*/  ReceiveConfig; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG4 ; 
 int /*<<< orphan*/  InitTxPwrTracking87SE (struct net_device*) ; 
 int /*<<< orphan*/  RCR ; 
#define  RF_ZEBRA2 129 
#define  RF_ZEBRA4 128 
 int /*<<< orphan*/  UpdateInitialGain (struct net_device*) ; 
 int /*<<< orphan*/  ZEBRA_Config_85BASIC_HardCode (struct net_device*) ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 
 int read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
PhyConfig8185(
	struct net_device *dev
	)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);
       write_nic_dword(dev, RCR, priv->ReceiveConfig);
	   priv->RFProgType = read_nic_byte(dev, CONFIG4) & 0x03;
     	// RF config
	switch(priv->rf_chip)
	{
	case RF_ZEBRA2:
	case RF_ZEBRA4:
		ZEBRA_Config_85BASIC_HardCode( dev);
		break;
	}
//{by amy 080312
	// Set default initial gain state to 4, approved by SD3 DZ, by Bruce, 2007-06-06.
	if(priv->bDigMechanism)
	{
		if(priv->InitialGain == 0)
			priv->InitialGain = 4;
		//printk("PhyConfig8185(): DIG is enabled, set default initial gain index to %d\n", priv->InitialGain);
	}

	//
	// Enable thermal meter indication to implement TxPower tracking on 87SE.
	// We initialize thermal meter here to avoid unsuccessful configuration.
	// Added by Roger, 2007.12.11.
	//
	if(priv->bTxPowerTrack)
		InitTxPwrTracking87SE(dev);

//by amy 080312}
	priv->InitialGainBackUp= priv->InitialGain;
	UpdateInitialGain(dev);

	return;
}