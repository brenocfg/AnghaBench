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
typedef  int /*<<< orphan*/  RF90_RADIO_PATH_E ;
typedef  int HT_CHANNEL_WIDTH ;

/* Variables and functions */
 int BIT10 ; 
 int BIT11 ; 
#define  HT_CHANNEL_WIDTH_20 129 
#define  HT_CHANNEL_WIDTH_20_40 128 
 int /*<<< orphan*/  RF90_PATH_A ; 
 int /*<<< orphan*/  RF_CHNLBW ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rFPGA0_AnalogParameter2 ; 
 int /*<<< orphan*/  rtl8192_phy_SetRFReg (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 

void PHY_SetRF0222DBandwidth(struct net_device* dev , HT_CHANNEL_WIDTH	 Bandwidth)	//20M or 40M
{
	u8			eRFPath;
	struct r8192_priv *priv = ieee80211_priv(dev);


	//if (IS_HARDWARE_TYPE_8192S(dev))
	if (1)
	{
#ifndef RTL92SE_FPGA_VERIFY
		switch(Bandwidth)
		{
			case HT_CHANNEL_WIDTH_20:
#ifdef FIB_MODIFICATION
				write_nic_byte(dev, rFPGA0_AnalogParameter2, 0x58);
#endif
				rtl8192_phy_SetRFReg(dev, (RF90_RADIO_PATH_E)RF90_PATH_A, RF_CHNLBW, BIT10|BIT11, 0x01);
				break;
			case HT_CHANNEL_WIDTH_20_40:
#ifdef FIB_MODIFICATION
				write_nic_byte(dev, rFPGA0_AnalogParameter2, 0x18);
#endif
				rtl8192_phy_SetRFReg(dev, (RF90_RADIO_PATH_E)RF90_PATH_A, RF_CHNLBW, BIT10|BIT11, 0x00);
				break;
			default:
				;//RT_TRACE(COMP_DBG, DBG_LOUD, ("PHY_SetRF8225Bandwidth(): unknown Bandwidth: %#X\n",Bandwidth ));
				break;
		}
#endif
	}
	else
	{
	for(eRFPath = 0; eRFPath <priv->NumTotalRFPath; eRFPath++)
	{
		switch(Bandwidth)
		{
			case HT_CHANNEL_WIDTH_20:
					//rtl8192_phy_SetRFReg(Adapter, (RF90_RADIO_PATH_E)RF90_PATH_A, RF_CHNLBW, (BIT10|BIT11), 0x01);
				break;
			case HT_CHANNEL_WIDTH_20_40:
					//rtl8192_phy_SetRFReg(Adapter, (RF90_RADIO_PATH_E)RF90_PATH_A, RF_CHNLBW, (BIT10|BIT11), 0x00);
				break;
			default:
				;//RT_TRACE(COMP_DBG, DBG_LOUD, ("PHY_SetRF8225Bandwidth(): unknown Bandwidth: %#X\n",Bandwidth ));
				break;

		}
	}
	}

}