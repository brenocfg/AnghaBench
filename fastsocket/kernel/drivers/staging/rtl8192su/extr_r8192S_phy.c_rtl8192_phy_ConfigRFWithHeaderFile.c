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
typedef  int u16 ;
struct r8192_priv {scalar_t__ rf_type; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  RT_STATUS ;
typedef  int RF90_RADIO_PATH_E ;

/* Variables and functions */
#define  RF90_PATH_A 131 
#define  RF90_PATH_B 130 
#define  RF90_PATH_C 129 
#define  RF90_PATH_D 128 
 scalar_t__ RF_2T2R_GREEN ; 
 int /*<<< orphan*/  RT_STATUS_SUCCESS ; 
 int RadioA_1T_ArrayLength ; 
 int RadioB_ArrayLength ; 
 int RadioB_GM_ArrayLength ; 
 int* Rtl819XRadioA_Array ; 
 int* Rtl819XRadioB_Array ; 
 int* Rtl819XRadioB_GM_Array ; 
 int /*<<< orphan*/  bRFRegOffsetMask ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  rtl8192_phy_SetRFReg (struct net_device*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

u8 rtl8192_phy_ConfigRFWithHeaderFile(struct net_device* dev, RF90_RADIO_PATH_E	eRFPath)
{

	struct r8192_priv *priv = ieee80211_priv(dev);
	int			i;
	//u32*	pRFArray;
	RT_STATUS	rtStatus = RT_STATUS_SUCCESS;
	u32			*Rtl819XRadioA_Array_Table;
	u32			*Rtl819XRadioB_Array_Table;
	//u32*	Rtl819XRadioC_Array_Table;
	//u32*	Rtl819XRadioD_Array_Table;
	u16			RadioA_ArrayLen,RadioB_ArrayLen;

	{	//2008.11.06 Modified by tynli
		RadioA_ArrayLen = RadioA_1T_ArrayLength;
		Rtl819XRadioA_Array_Table=Rtl819XRadioA_Array;
		Rtl819XRadioB_Array_Table=Rtl819XRadioB_Array;
		RadioB_ArrayLen = RadioB_ArrayLength;
	}

	if( priv->rf_type == RF_2T2R_GREEN )
	{
		Rtl819XRadioB_Array_Table = Rtl819XRadioB_GM_Array;
		RadioB_ArrayLen = RadioB_GM_ArrayLength;
	}
	else
	{
		Rtl819XRadioB_Array_Table = Rtl819XRadioB_Array;
		RadioB_ArrayLen = RadioB_ArrayLength;
	}

	rtStatus = RT_STATUS_SUCCESS;

	// When initialization, we want the delay function(mdelay(), delay_us()
	// ==> actually we call PlatformStallExecution()) to do NdisStallExecution()
	// [busy wait] instead of NdisMSleep(). So we acquire RT_INITIAL_SPINLOCK
	// to run at Dispatch level to achive it.
	//cosa PlatformAcquireSpinLock(Adapter, RT_INITIAL_SPINLOCK);

	switch(eRFPath){
		case RF90_PATH_A:
			for(i = 0;i<RadioA_ArrayLen; i=i+2){
				if(Rtl819XRadioA_Array_Table[i] == 0xfe)
					{ // Deay specific ms. Only RF configuration require delay.
//#if (DEV_BUS_TYPE == USB_INTERFACE)
						mdelay(1000);
				}
					else if (Rtl819XRadioA_Array_Table[i] == 0xfd)
						mdelay(5);
					else if (Rtl819XRadioA_Array_Table[i] == 0xfc)
						mdelay(1);
					else if (Rtl819XRadioA_Array_Table[i] == 0xfb)
						udelay(50);
						//PlatformStallExecution(50);
					else if (Rtl819XRadioA_Array_Table[i] == 0xfa)
						udelay(5);
					else if (Rtl819XRadioA_Array_Table[i] == 0xf9)
						udelay(1);
					else
					{
					rtl8192_phy_SetRFReg(dev, eRFPath, Rtl819XRadioA_Array_Table[i], bRFRegOffsetMask, Rtl819XRadioA_Array_Table[i+1]);
					}
			}
			break;
		case RF90_PATH_B:
			for(i = 0;i<RadioB_ArrayLen; i=i+2){
				if(Rtl819XRadioB_Array_Table[i] == 0xfe)
					{ // Deay specific ms. Only RF configuration require delay.
//#if (DEV_BUS_TYPE == USB_INTERFACE)
						mdelay(1000);
				}
					else if (Rtl819XRadioB_Array_Table[i] == 0xfd)
						mdelay(5);
					else if (Rtl819XRadioB_Array_Table[i] == 0xfc)
						mdelay(1);
					else if (Rtl819XRadioB_Array_Table[i] == 0xfb)
						udelay(50);
					else if (Rtl819XRadioB_Array_Table[i] == 0xfa)
						udelay(5);
					else if (Rtl819XRadioB_Array_Table[i] == 0xf9)
						udelay(1);
					else
					{
					rtl8192_phy_SetRFReg(dev, eRFPath, Rtl819XRadioB_Array_Table[i], bRFRegOffsetMask, Rtl819XRadioB_Array_Table[i+1]);
					}
			}
			break;
		case RF90_PATH_C:
			break;
		case RF90_PATH_D:
			break;
		default:
			break;
	}

	return rtStatus;

}