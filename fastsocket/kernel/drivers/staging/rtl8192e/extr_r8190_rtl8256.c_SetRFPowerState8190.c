#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct r8192_priv {int SetRFPowerStateInProgress; int rf_chip; TYPE_1__* ieee80211; int /*<<< orphan*/  bHwRfOffAction; int /*<<< orphan*/  rf_type; int /*<<< orphan*/ * txvopringhead; int /*<<< orphan*/ * txvopringtail; int /*<<< orphan*/ * txvipringhead; int /*<<< orphan*/ * txvipringtail; int /*<<< orphan*/ * txbepringhead; int /*<<< orphan*/ * txbepringtail; int /*<<< orphan*/ * txbkpringhead; int /*<<< orphan*/ * txbkpringtail; int /*<<< orphan*/ * txmapringhead; int /*<<< orphan*/ * txmapringtail; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/ * ptx_ring ;
struct TYPE_10__ {int /*<<< orphan*/  (* LedControlHandler ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_12__ {TYPE_2__ HalFunc; } ;
struct TYPE_11__ {int /*<<< orphan*/  bLeisurePs; } ;
struct TYPE_9__ {int eRFPowerState; int /*<<< orphan*/  state; int /*<<< orphan*/  RfOffReason; int /*<<< orphan*/  PowerSaveControl; } ;
typedef  int RT_RF_POWER_STATE ;
typedef  TYPE_3__* PRT_POWER_SAVE_CONTROL ;

/* Variables and functions */
 int /*<<< orphan*/  ANAPAR ; 
 TYPE_4__* Adapter ; 
 int /*<<< orphan*/  BB_RESET ; 
#define  BE_QUEUE 136 
 int BIT0 ; 
 int BIT4 ; 
#define  BK_QUEUE 135 
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  COMP_POWER ; 
 int /*<<< orphan*/  IEEE80211_LINKED ; 
 int /*<<< orphan*/  LED_CTL_LINK ; 
 int /*<<< orphan*/  LED_CTL_NO_LINK ; 
 int /*<<< orphan*/  LED_CTL_POWER_OFF ; 
 int /*<<< orphan*/  MAX_DOZE_WAITING_TIMES_9x ; 
 int /*<<< orphan*/  MAX_TX_QUEUE ; 
#define  MGNT_QUEUE 134 
 int /*<<< orphan*/  MacBlkCtrl ; 
 int /*<<< orphan*/  RF_1T2R ; 
 int /*<<< orphan*/  RF_2T4R ; 
#define  RF_8256 133 
 int /*<<< orphan*/  RF_CHANGE_BY_IPS ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,...) ; 
#define  VI_QUEUE 132 
#define  VO_QUEUE 131 
#define  eRfOff 130 
#define  eRfOn 129 
#define  eRfSleep 128 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  rFPGA0_AnalogParameter1 ; 
 int /*<<< orphan*/  rFPGA0_AnalogParameter2 ; 
 int /*<<< orphan*/  rFPGA0_AnalogParameter4 ; 
 int /*<<< orphan*/  rFPGA0_XA_RFInterfaceOE ; 
 int /*<<< orphan*/  rFPGA0_XB_RFInterfaceOE ; 
 int /*<<< orphan*/  rFPGA0_XC_RFInterfaceOE ; 
 int /*<<< orphan*/  rOFDM0_TRxPathEnable ; 
 int /*<<< orphan*/  rOFDM1_TRxPathEnable ; 
 int read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool
SetRFPowerState8190(
	struct net_device* dev,
	RT_RF_POWER_STATE	eRFPowerState
	)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	PRT_POWER_SAVE_CONTROL	pPSC = (PRT_POWER_SAVE_CONTROL)(&(priv->ieee80211->PowerSaveControl));
	bool bResult = true;
	//u8 eRFPath;
	u8	i = 0, QueueID = 0;
	ptx_ring	head=NULL,tail=NULL;

	if(priv->SetRFPowerStateInProgress == true)
		return false;
	RT_TRACE(COMP_POWER, "===========> SetRFPowerState8190()!\n");
	priv->SetRFPowerStateInProgress = true;

	switch(priv->rf_chip)
	{
		case RF_8256:
		switch( eRFPowerState )
		{
			case eRfOn:
				RT_TRACE(COMP_POWER, "SetRFPowerState8190() eRfOn !\n");
						//RXTX enable control: On
					//for(eRFPath = 0; eRFPath <pHalData->NumTotalRFPath; eRFPath++)
					//	PHY_SetRFReg(Adapter, (RF90_RADIO_PATH_E)eRFPath, 0x4, 0xC00, 0x2);
				#ifdef RTL8190P
				if(priv->rf_type == RF_2T4R)
				{
					//enable RF-Chip A/B
					rtl8192_setBBreg(dev, rFPGA0_XA_RFInterfaceOE, BIT4, 0x1); // 0x860[4]
					//enable RF-Chip C/D
					rtl8192_setBBreg(dev, rFPGA0_XC_RFInterfaceOE, BIT4, 0x1); // 0x868[4]
					//analog to digital on
					rtl8192_setBBreg(dev, rFPGA0_AnalogParameter4, 0xf00, 0xf);// 0x88c[11:8]
					//digital to analog on
					rtl8192_setBBreg(dev, rFPGA0_AnalogParameter1, 0x1e0, 0xf); // 0x880[8:5]
					//rx antenna on
					rtl8192_setBBreg(dev, rOFDM0_TRxPathEnable, 0xf, 0xf);// 0xc04[3:0]
					//rx antenna on
					rtl8192_setBBreg(dev, rOFDM1_TRxPathEnable, 0xf, 0xf);// 0xd04[3:0]
					//analog to digital part2 on
					rtl8192_setBBreg(dev, rFPGA0_AnalogParameter1, 0x1e00, 0xf); // 0x880[12:9]
				}
				else if(priv->rf_type == RF_1T2R)	//RF-C, RF-D
				{
					//enable RF-Chip C/D
					rtl8192_setBBreg(dev, rFPGA0_XC_RFInterfaceOE, BIT4, 0x1); // 0x868[4]
					//analog to digital on
					rtl8192_setBBreg(dev, rFPGA0_AnalogParameter4, 0xc00, 0x3);// 0x88c[11:10]
					//digital to analog on
					rtl8192_setBBreg(dev, rFPGA0_AnalogParameter1, 0x180, 0x3); // 0x880[8:7]
					//rx antenna on
					rtl8192_setBBreg(dev, rOFDM0_TRxPathEnable, 0xc, 0x3);// 0xc04[3:2]
					//rx antenna on
					rtl8192_setBBreg(dev, rOFDM1_TRxPathEnable, 0xc, 0x3);// 0xd04[3:2]
					//analog to digital part2 on
					rtl8192_setBBreg(dev, rFPGA0_AnalogParameter1, 0x1800, 0x3); // 0x880[12:11]
				}
				#else
				write_nic_byte(dev, ANAPAR, 0x37);//160MHz
				write_nic_byte(dev, MacBlkCtrl, 0x17); // 0x403
				mdelay(1);
				//enable clock 80/88 MHz

				priv->bHwRfOffAction = 0;
				//}

				// Baseband reset 2008.09.30 add
				write_nic_byte(dev, BB_RESET, (read_nic_byte(dev, BB_RESET)|BIT0));

				//2 AFE
				// 2008.09.30 add
				rtl8192_setBBreg(dev, rFPGA0_AnalogParameter2, 0x20000000, 0x1); // 0x884
				//analog to digital part2 on
					rtl8192_setBBreg(dev, rFPGA0_AnalogParameter1, 0x60, 0x3);		// 0x880[6:5]
				//digital to analog on
				rtl8192_setBBreg(dev, rFPGA0_AnalogParameter1, 0x98, 0x13); // 0x880[4:3]
				//analog to digital on
				rtl8192_setBBreg(dev, rFPGA0_AnalogParameter4, 0xf03, 0xf03);// 0x88c[9:8]
				//rx antenna on
				//PHY_SetBBReg(Adapter, rOFDM0_TRxPathEnable, 0x3, 0x3);// 0xc04[1:0]
				//rx antenna on 2008.09.30 mark
				//PHY_SetBBReg(Adapter, rOFDM1_TRxPathEnable, 0x3, 0x3);// 0xd04[1:0]

				//2 RF
				//enable RF-Chip A/B
					rtl8192_setBBreg(dev, rFPGA0_XA_RFInterfaceOE, BIT4, 0x1);		// 0x860[4]
				rtl8192_setBBreg(dev, rFPGA0_XB_RFInterfaceOE, BIT4, 0x1);		// 0x864[4]
				#endif
						break;

				//
				// In current solution, RFSleep=RFOff in order to save power under 802.11 power save.
				// By Bruce, 2008-01-16.
				//
			case eRfSleep:
			case eRfOff:
				RT_TRACE(COMP_POWER, "SetRFPowerState8190() eRfOff/Sleep !\n");
				if (pPSC->bLeisurePs)
				{
					for(QueueID = 0, i = 0; QueueID < MAX_TX_QUEUE; )
					{
						switch(QueueID) {
							case MGNT_QUEUE:
								tail=priv->txmapringtail;
								head=priv->txmapringhead;
								break;

							case BK_QUEUE:
								tail=priv->txbkpringtail;
								head=priv->txbkpringhead;
								break;

							case BE_QUEUE:
								tail=priv->txbepringtail;
								head=priv->txbepringhead;
								break;

							case VI_QUEUE:
								tail=priv->txvipringtail;
								head=priv->txvipringhead;
								break;

							case VO_QUEUE:
								tail=priv->txvopringtail;
								head=priv->txvopringhead;
								break;

							default:
								tail=head=NULL;
								break;
						}
						if(tail == head)
						{
							//DbgPrint("QueueID = %d", QueueID);
							QueueID++;
							continue;
						}
						else
						{
							RT_TRACE(COMP_POWER, "eRf Off/Sleep: %d times BusyQueue[%d] !=0 before doze!\n", (i+1), QueueID);
							udelay(10);
							i++;
						}

						if(i >= MAX_DOZE_WAITING_TIMES_9x)
						{
							RT_TRACE(COMP_POWER, "\n\n\n TimeOut!! SetRFPowerState8190(): eRfOff: %d times BusyQueue[%d] != 0 !!!\n\n\n", MAX_DOZE_WAITING_TIMES_9x, QueueID);
							break;
						}
					}
				}
				#ifdef RTL8190P
				if(priv->rf_type == RF_2T4R)
				{
					//disable RF-Chip A/B
					rtl8192_setBBreg(dev, rFPGA0_XA_RFInterfaceOE, BIT4, 0x0);		// 0x860[4]
				}
				//disable RF-Chip C/D
				rtl8192_setBBreg(dev, rFPGA0_XC_RFInterfaceOE, BIT4, 0x0); // 0x868[4]
				//analog to digital off, for power save
				rtl8192_setBBreg(dev, rFPGA0_AnalogParameter4, 0xf00, 0x0);// 0x88c[11:8]
				//digital to analog off, for power save
				rtl8192_setBBreg(dev, rFPGA0_AnalogParameter1, 0x1e0, 0x0); // 0x880[8:5]
				//rx antenna off
				rtl8192_setBBreg(dev, rOFDM0_TRxPathEnable, 0xf, 0x0);// 0xc04[3:0]
				//rx antenna off
				rtl8192_setBBreg(dev, rOFDM1_TRxPathEnable, 0xf, 0x0);// 0xd04[3:0]
				//analog to digital part2 off, for power save
				rtl8192_setBBreg(dev, rFPGA0_AnalogParameter1, 0x1e00, 0x0); // 0x880[12:9]
#else //8192E
					//2 RF
				//disable RF-Chip A/B
				rtl8192_setBBreg(dev, rFPGA0_XA_RFInterfaceOE, BIT4, 0x0);		// 0x860[4]
					rtl8192_setBBreg(dev, rFPGA0_XB_RFInterfaceOE, BIT4, 0x0);		// 0x864[4]
					//2 AFE
				//analog to digital off, for power save
					//PHY_SetBBReg(Adapter, rFPGA0_AnalogParameter4, 0xf00, 0x0);// 0x88c[11:8]
					rtl8192_setBBreg(dev, rFPGA0_AnalogParameter4, 0xf03, 0x0); //  2008.09.30 Modify
				//digital to analog off, for power save
					//PHY_SetBBReg(Adapter, rFPGA0_AnalogParameter1, 0x18, 0x0); // 0x880[4:3]
					rtl8192_setBBreg(dev, rFPGA0_AnalogParameter1, 0x98, 0x0); // 0x880 2008.09.30 Modify
					//rx antenna off  2008.09.30 mark
					//PHY_SetBBReg(Adapter, rOFDM0_TRxPathEnable, 0xf, 0x0);// 0xc04[3:0]
					//rx antenna off  2008.09.30 mark
					//PHY_SetBBReg(Adapter, rOFDM1_TRxPathEnable, 0xf, 0x0);// 0xd04[3:0]
				//analog to digital part2 off, for power save
					rtl8192_setBBreg(dev, rFPGA0_AnalogParameter1, 0x60, 0x0);		// 0x880[6:5]
					// 2008.09.30 add
					rtl8192_setBBreg(dev, rFPGA0_AnalogParameter2, 0x20000000, 0x0); // 0x884


					//disable clock 80/88 MHz 2008.09.30 mark
					//PHY_SetBBReg(Adapter, rFPGA0_AnalogParameter1, 0x4, 0x0); // 0x880[2]
					//2 BB
					// Baseband reset 2008.09.30 add
					write_nic_byte(dev, BB_RESET, (read_nic_byte(dev, BB_RESET)|BIT0)); // 0x101
					//MAC: off
					write_nic_byte(dev, MacBlkCtrl, 0x0); // 0x403
					//slow down cpu/lbus clock from 160MHz to Lower
					write_nic_byte(dev, ANAPAR, 0x07); // 0x 17 40MHz
				priv->bHwRfOffAction = 0;
				//}
				#endif
					break;

			default:
					bResult = false;
					RT_TRACE(COMP_ERR, "SetRFPowerState8190(): unknow state to set: 0x%X!!!\n", eRFPowerState);
					break;
		}

		break;

		default:
			RT_TRACE(COMP_ERR, "SetRFPowerState8190(): Unknown RF type\n");
			break;
	}

	if(bResult)
	{
		// Update current RF state variable.
		priv->ieee80211->eRFPowerState = eRFPowerState;

		switch(priv->rf_chip )
		{
			case RF_8256:
			switch(priv->ieee80211->eRFPowerState)
			{
				case eRfOff:
				//
				//If Rf off reason is from IPS, Led should blink with no link, by Maddest 071015
				//
					if(priv->ieee80211->RfOffReason==RF_CHANGE_BY_IPS )
					{
						#ifdef TO_DO
						Adapter->HalFunc.LedControlHandler(Adapter,LED_CTL_NO_LINK);
						#endif
					}
					else
					{
					// Turn off LED if RF is not ON.
						#ifdef TO_DO
						Adapter->HalFunc.LedControlHandler(Adapter, LED_CTL_POWER_OFF);
						#endif
					}
					break;

				case eRfOn:
				// Turn on RF we are still linked, which might happen when
				// we quickly turn off and on HW RF. 2006.05.12, by rcnjko.
					if( priv->ieee80211->state == IEEE80211_LINKED)
					{
						#ifdef TO_DO
						Adapter->HalFunc.LedControlHandler(Adapter, LED_CTL_LINK);
						#endif
					}
					else
					{
					// Turn off LED if RF is not ON.
						#ifdef TO_DO
						Adapter->HalFunc.LedControlHandler(Adapter, LED_CTL_NO_LINK);
						#endif
					}
					break;

				default:
			// do nothing.
					break;
			}// Switch RF state

			break;

			default:
				RT_TRACE(COMP_ERR, "SetRFPowerState8190(): Unknown RF type\n");
				break;
		}// Switch RFChipID
	}

	priv->SetRFPowerStateInProgress = false;
	RT_TRACE(COMP_POWER, "<=========== SetRFPowerState8190() bResult = %d!\n", bResult);
	return bResult;
}