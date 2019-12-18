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
struct r8192_priv {int rf_type; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
#define  RF_1T1R 131 
#define  RF_1T2R 130 
#define  RF_2T2R 129 
#define  RF_2T2R_GREEN 128 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

u8 FirmwareHeaderMapRfType(struct net_device *dev)
{
	struct r8192_priv 	*priv = ieee80211_priv(dev);
	switch(priv->rf_type)
	{
		case RF_1T1R: 	return 0x11;
		case RF_1T2R: 	return 0x12;
		case RF_2T2R: 	return 0x22;
		case RF_2T2R_GREEN: 	return 0x92;
		default:
			RT_TRACE(COMP_INIT, "Unknown RF type(%x)\n",priv->rf_type);
			break;
	}
	return 0x22;
}