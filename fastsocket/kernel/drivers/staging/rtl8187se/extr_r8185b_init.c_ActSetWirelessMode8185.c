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
typedef  int u8 ;
struct r8180_priv {int rf_chip; int /*<<< orphan*/  ChannelAccessSetting; struct ieee80211_device* ieee80211; } ;
struct net_device {int dummy; } ;
struct ieee80211_device {int mode; } ;
typedef  int WIRELESS_MODE ;

/* Variables and functions */
 int /*<<< orphan*/  ActUpdateChannelAccessSetting (struct net_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DMESG (char*) ; 
 int /*<<< orphan*/  DMESGW (char*,int,...) ; 
 int GetSupportedWirelessMode8185 (struct net_device*) ; 
#define  RF_ZEBRA2 129 
#define  RF_ZEBRA4 128 
 int WIRELESS_MODE_A ; 
 int WIRELESS_MODE_AUTO ; 
 int WIRELESS_MODE_B ; 
 int WIRELESS_MODE_G ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 

void
ActSetWirelessMode8185(
	struct net_device *dev,
	u8				btWirelessMode
	)
{
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);
	struct ieee80211_device *ieee = priv->ieee80211;
	//PMGNT_INFO		pMgntInfo = &(Adapter->MgntInfo);
	u8	btSupportedWirelessMode = GetSupportedWirelessMode8185(dev);

	if( (btWirelessMode & btSupportedWirelessMode) == 0 )
	{ // Don't switch to unsupported wireless mode, 2006.02.15, by rcnjko.
		DMESGW("ActSetWirelessMode8185(): WirelessMode(%d) is not supported (%d)!\n",
			btWirelessMode, btSupportedWirelessMode);
		return;
	}

	// 1. Assign wireless mode to swtich if necessary.
	if (btWirelessMode == WIRELESS_MODE_AUTO)
	{
		if((btSupportedWirelessMode & WIRELESS_MODE_A))
		{
			btWirelessMode = WIRELESS_MODE_A;
		}
		else if((btSupportedWirelessMode & WIRELESS_MODE_G))
		{
			btWirelessMode = WIRELESS_MODE_G;
		}
		else if((btSupportedWirelessMode & WIRELESS_MODE_B))
		{
			btWirelessMode = WIRELESS_MODE_B;
		}
		else
		{
			DMESGW("ActSetWirelessMode8185(): No valid wireless mode supported, btSupportedWirelessMode(%x)!!!\n",
					 btSupportedWirelessMode);
			btWirelessMode = WIRELESS_MODE_B;
		}
	}


	// 2. Swtich band: RF or BB specific actions,
	// for example, refresh tables in omc8255, or change initial gain if necessary.
	switch(priv->rf_chip)
	{
	case RF_ZEBRA2:
	case RF_ZEBRA4:
		{
			// Nothing to do for Zebra to switch band.
			// Update current wireless mode if we swtich to specified band successfully.
			ieee->mode = (WIRELESS_MODE)btWirelessMode;
		}
		break;

	default:
		DMESGW("ActSetWirelessMode8185(): unsupported RF: 0x%X !!!\n", priv->rf_chip);
		break;
	}

	// 3. Change related setting.
	if( ieee->mode == WIRELESS_MODE_A ){
		DMESG("WIRELESS_MODE_A\n");
	}
	else if( ieee->mode == WIRELESS_MODE_B ){
		DMESG("WIRELESS_MODE_B\n");
	}
	else if( ieee->mode == WIRELESS_MODE_G ){
		DMESG("WIRELESS_MODE_G\n");
	}

	ActUpdateChannelAccessSetting( dev, ieee->mode, &priv->ChannelAccessSetting);
}