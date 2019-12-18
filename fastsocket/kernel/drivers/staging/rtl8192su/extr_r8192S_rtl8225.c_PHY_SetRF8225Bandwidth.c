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
typedef  scalar_t__ u8 ;
struct r8192_priv {scalar_t__ NumTotalRFPath; } ;
struct net_device {int dummy; } ;
typedef  int HT_CHANNEL_WIDTH ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_DBG ; 
#define  HT_CHANNEL_WIDTH_20 129 
#define  HT_CHANNEL_WIDTH_20_40 128 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,...) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

void PHY_SetRF8225Bandwidth(struct net_device* dev ,HT_CHANNEL_WIDTH Bandwidth)	//20M or 40M
{
	u8			eRFPath;
	struct r8192_priv *priv = ieee80211_priv(dev);

	//for(eRFPath = RF90_PATH_A; eRFPath <pHalData->NumTotalRFPath; eRFPath++)
	for(eRFPath = 0; eRFPath <priv->NumTotalRFPath; eRFPath++)
	{
		switch(Bandwidth)
		{
			case HT_CHANNEL_WIDTH_20:
				// TODO: Update the parameters here
				break;
			case HT_CHANNEL_WIDTH_20_40:
				RT_TRACE(COMP_DBG, "SetChannelBandwidth8190Pci():8225 does not support 40M mode\n");
				break;
			default:
				RT_TRACE(COMP_DBG, "PHY_SetRF8225Bandwidth(): unknown Bandwidth: %#X\n",Bandwidth );
				break;

		}
	}

}