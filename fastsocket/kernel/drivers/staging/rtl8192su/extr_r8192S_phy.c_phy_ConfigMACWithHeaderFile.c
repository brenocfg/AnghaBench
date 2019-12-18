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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  RT_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 int MAC_2T_ArrayLength ; 
 int /*<<< orphan*/  RT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*) ; 
 int* Rtl819XMAC_Array ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static	RT_STATUS
phy_ConfigMACWithHeaderFile(struct net_device* dev)
{
	u32					i = 0;
	u32					ArrayLength = 0;
	u32*					ptrArray;
	//struct r8192_priv 	*priv = ieee80211_priv(dev);

//#if (HAL_CODE_BASE != RTL8192_S)
	/*if(Adapter->bInHctTest)
	{
		RT_TRACE(COMP_INIT, DBG_LOUD, ("Rtl819XMACPHY_ArrayDTM\n"));
		ArrayLength = MACPHY_ArrayLengthDTM;
		ptrArray = Rtl819XMACPHY_ArrayDTM;
	}
	else if(pHalData->bTXPowerDataReadFromEEPORM)
	{
//		RT_TRACE(COMP_INIT, DBG_LOUD, ("Rtl819XMACPHY_Array_PG\n"));
//		ArrayLength = MACPHY_Array_PGLength;
//		ptrArray = Rtl819XMACPHY_Array_PG;

	}else*/
	{ //2008.11.06 Modified by tynli.
		RT_TRACE(COMP_INIT, "Read Rtl819XMACPHY_Array\n");
		ArrayLength = MAC_2T_ArrayLength;
		ptrArray = Rtl819XMAC_Array;
	}

	/*for(i = 0 ;i < ArrayLength;i=i+3){
		RT_TRACE(COMP_SEND, DBG_LOUD, ("The Rtl819XMACPHY_Array[0] is %lx Rtl819XMACPHY_Array[1] is %lx Rtl819XMACPHY_Array[2] is %lx\n",ptrArray[i], ptrArray[i+1], ptrArray[i+2]));
		if(ptrArray[i] == 0x318)
		{
			ptrArray[i+2] = 0x00000800;
			//DbgPrint("ptrArray[i], ptrArray[i+1], ptrArray[i+2] = %x, %x, %x\n",
			//	ptrArray[i], ptrArray[i+1], ptrArray[i+2]);
		}
		PHY_SetBBReg(Adapter, ptrArray[i], ptrArray[i+1], ptrArray[i+2]);
	}*/
	for(i = 0 ;i < ArrayLength;i=i+2){ // Add by tynli for 2 column
		write_nic_byte(dev, ptrArray[i], (u8)ptrArray[i+1]);
	}
//#endif
	return RT_STATUS_SUCCESS;
}