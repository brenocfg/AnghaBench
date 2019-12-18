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
 int AGCTAB_ArrayLength ; 
 scalar_t__ BaseBand_Config_AGC_TAB ; 
 scalar_t__ BaseBand_Config_PHY_REG ; 
 int PHY_REG_2T2RArrayLength ; 
 int /*<<< orphan*/  RT_STATUS_SUCCESS ; 
 int* Rtl819XAGCTAB_Array ; 
 int* Rtl819XPHY_REG_Array ; 
 int /*<<< orphan*/  bMaskDWord ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static	RT_STATUS
phy_ConfigBBWithHeaderFile(struct net_device* dev,u8 ConfigType)
{
	int 		i;
	//u8 		ArrayLength;
	u32*	Rtl819XPHY_REGArray_Table;
	u32*	Rtl819XAGCTAB_Array_Table;
	u16		PHY_REGArrayLen, AGCTAB_ArrayLen;
	//struct r8192_priv *priv = ieee80211_priv(dev);
//#if (HAL_CODE_BASE != RTL8192_S)
	/*if(Adapter->bInHctTest)
	{

		AGCTAB_ArrayLen = AGCTAB_ArrayLengthDTM;
		Rtl819XAGCTAB_Array_Table = Rtl819XAGCTAB_ArrayDTM;

		if(pHalData->RF_Type == RF_2T4R)
		{
			PHY_REGArrayLen = PHY_REGArrayLengthDTM;
			Rtl819XPHY_REGArray_Table = Rtl819XPHY_REGArrayDTM;
		}
		else if (pHalData->RF_Type == RF_1T2R)
		{
			PHY_REGArrayLen = PHY_REG_1T2RArrayLengthDTM;
			Rtl819XPHY_REGArray_Table = Rtl819XPHY_REG_1T2RArrayDTM;
		}

	}
	else
	*/
	//{
	//
	// 2008.11.06 Modified by tynli.
	//
	AGCTAB_ArrayLen = AGCTAB_ArrayLength;
	Rtl819XAGCTAB_Array_Table = Rtl819XAGCTAB_Array;
	PHY_REGArrayLen = PHY_REG_2T2RArrayLength; // Default RF_type: 2T2R
	Rtl819XPHY_REGArray_Table = Rtl819XPHY_REG_Array;
	//}

	if(ConfigType == BaseBand_Config_PHY_REG)
	{
		for(i=0;i<PHY_REGArrayLen;i=i+2)
		{
			if (Rtl819XPHY_REGArray_Table[i] == 0xfe)
				mdelay(50);
			else if (Rtl819XPHY_REGArray_Table[i] == 0xfd)
				mdelay(5);
			else if (Rtl819XPHY_REGArray_Table[i] == 0xfc)
				mdelay(1);
			else if (Rtl819XPHY_REGArray_Table[i] == 0xfb)
				udelay(50);
			else if (Rtl819XPHY_REGArray_Table[i] == 0xfa)
				udelay(5);
			else if (Rtl819XPHY_REGArray_Table[i] == 0xf9)
				udelay(1);
			rtl8192_setBBreg(dev, Rtl819XPHY_REGArray_Table[i], bMaskDWord, Rtl819XPHY_REGArray_Table[i+1]);
			//RT_TRACE(COMP_SEND, "The Rtl819XPHY_REGArray_Table[0] is %lx Rtl819XPHY_REGArray[1] is %lx \n",Rtl819XPHY_REGArray_Table[i], Rtl819XPHY_REGArray_Table[i+1]);

		}
	}
	else if(ConfigType == BaseBand_Config_AGC_TAB){
		for(i=0;i<AGCTAB_ArrayLen;i=i+2)
		{
			rtl8192_setBBreg(dev, Rtl819XAGCTAB_Array_Table[i], bMaskDWord, Rtl819XAGCTAB_Array_Table[i+1]);
		}
	}
//#endif	// #if (HAL_CODE_BASE != RTL8192_S)
	return RT_STATUS_SUCCESS;
}