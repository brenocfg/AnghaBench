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
struct r8180_priv {int rf_chip; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
#define  RF_ZEBRA2 129 
#define  RF_ZEBRA4 128 
 int WIRELESS_MODE_B ; 
 int WIRELESS_MODE_G ; 
 scalar_t__ ieee80211_priv (struct net_device*) ; 

u8
GetSupportedWirelessMode8185(
	struct net_device *dev
)
{
	u8			btSupportedWirelessMode = 0;
	struct r8180_priv *priv = (struct r8180_priv *)ieee80211_priv(dev);

	switch(priv->rf_chip)
	{
	case RF_ZEBRA2:
	case RF_ZEBRA4:
		btSupportedWirelessMode = (WIRELESS_MODE_B | WIRELESS_MODE_G);
		break;
	default:
		btSupportedWirelessMode = WIRELESS_MODE_B;
		break;
	}

	return btSupportedWirelessMode;
}