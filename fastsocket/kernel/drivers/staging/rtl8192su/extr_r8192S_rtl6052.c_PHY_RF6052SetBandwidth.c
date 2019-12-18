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
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  RF90_RADIO_PATH_E ;
typedef  int HT_CHANNEL_WIDTH ;

/* Variables and functions */
 int BIT10 ; 
 int BIT11 ; 
 int /*<<< orphan*/  COMP_DBG ; 
#define  HT_CHANNEL_WIDTH_20 129 
#define  HT_CHANNEL_WIDTH_20_40 128 
 int /*<<< orphan*/  RF90_PATH_A ; 
 int /*<<< orphan*/  RF_CHNLBW ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rtl8192_phy_SetRFReg (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void PHY_RF6052SetBandwidth(struct net_device* dev, HT_CHANNEL_WIDTH Bandwidth)	//20M or 40M
{
	//u8				eRFPath;
	//struct r8192_priv 	*priv = ieee80211_priv(dev);


	//if (priv->card_8192 == NIC_8192SE)
	{
		switch(Bandwidth)
		{
			case HT_CHANNEL_WIDTH_20:
				//if (priv->card_8192_version >= VERSION_8192S_BCUT)
				//	rtl8192_setBBreg(dev, rFPGA0_AnalogParameter2, 0xff, 0x58);

				rtl8192_phy_SetRFReg(dev, (RF90_RADIO_PATH_E)RF90_PATH_A, RF_CHNLBW, BIT10|BIT11, 0x01);
				break;
			case HT_CHANNEL_WIDTH_20_40:
				//if (priv->card_8192_version >= VERSION_8192S_BCUT)
				//	rtl8192_setBBreg(dev, rFPGA0_AnalogParameter2, 0xff, 0x18);

				rtl8192_phy_SetRFReg(dev, (RF90_RADIO_PATH_E)RF90_PATH_A, RF_CHNLBW, BIT10|BIT11, 0x00);
				break;
			default:
				RT_TRACE(COMP_DBG, "PHY_SetRF6052Bandwidth(): unknown Bandwidth: %#X\n",Bandwidth);
				break;
		}
	}
//	else
}