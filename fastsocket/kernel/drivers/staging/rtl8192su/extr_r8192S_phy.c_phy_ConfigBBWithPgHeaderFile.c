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
typedef  int u32 ;
typedef  int u16 ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  RT_STATUS ;

/* Variables and functions */
 scalar_t__ BaseBand_Config_PHY_REG ; 
 int /*<<< orphan*/  COMP_SEND ; 
 int PHY_REG_Array_PGLength ; 
 int /*<<< orphan*/  RT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*) ; 
 int* Rtl819XPHY_REG_Array_PG ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static RT_STATUS
phy_ConfigBBWithPgHeaderFile(struct net_device* dev,u8 ConfigType)
{
	int i;
	//u8 ArrayLength;
	u32*	Rtl819XPHY_REGArray_Table_PG;
	u16	PHY_REGArrayPGLen;
	//struct r8192_priv *priv = ieee80211_priv(dev);
//#if (HAL_CODE_BASE != RTL8192_S)
	// Default: pHalData->RF_Type = RF_2T2R.

	PHY_REGArrayPGLen = PHY_REG_Array_PGLength;
	Rtl819XPHY_REGArray_Table_PG = Rtl819XPHY_REG_Array_PG;

	if(ConfigType == BaseBand_Config_PHY_REG)
	{
		for(i=0;i<PHY_REGArrayPGLen;i=i+3)
		{
			if (Rtl819XPHY_REGArray_Table_PG[i] == 0xfe)
				mdelay(50);
			else if (Rtl819XPHY_REGArray_Table_PG[i] == 0xfd)
				mdelay(5);
			else if (Rtl819XPHY_REGArray_Table_PG[i] == 0xfc)
				mdelay(1);
			else if (Rtl819XPHY_REGArray_Table_PG[i] == 0xfb)
				udelay(50);
			else if (Rtl819XPHY_REGArray_Table_PG[i] == 0xfa)
				udelay(5);
			else if (Rtl819XPHY_REGArray_Table_PG[i] == 0xf9)
				udelay(1);
			rtl8192_setBBreg(dev, Rtl819XPHY_REGArray_Table_PG[i], Rtl819XPHY_REGArray_Table_PG[i+1], Rtl819XPHY_REGArray_Table_PG[i+2]);
			//RT_TRACE(COMP_SEND, "The Rtl819XPHY_REGArray_Table_PG[0] is %lx Rtl819XPHY_REGArray_Table_PG[1] is %lx \n",
			//		Rtl819XPHY_REGArray_Table_PG[i], Rtl819XPHY_REGArray_Table_PG[i+1]);
		}
	}else{
		RT_TRACE(COMP_SEND, "phy_ConfigBBWithPgHeaderFile(): ConfigType != BaseBand_Config_PHY_REG\n");
	}
	return RT_STATUS_SUCCESS;

}