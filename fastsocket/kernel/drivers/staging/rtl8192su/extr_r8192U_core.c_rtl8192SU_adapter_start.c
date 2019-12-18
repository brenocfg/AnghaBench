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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct r8192_priv {scalar_t__ card_8192_version; scalar_t__ rf_type; scalar_t__ ResetProgress; int RegRfOff; int NumTotalRFPath; scalar_t__ RfOffReason; int /*<<< orphan*/  chan; int /*<<< orphan*/  eRFPowerState; TYPE_1__* ieee80211; int /*<<< orphan*/  bInHctTest; int /*<<< orphan*/  Rf_Mode; } ;
struct net_device {scalar_t__ dev_addr; } ;
struct TYPE_10__ {scalar_t__ HighestOperaRate; } ;
struct TYPE_12__ {TYPE_2__ MgntInfo; } ;
struct TYPE_11__ {int /*<<< orphan*/  RtUsbCheckForHangWorkItem; } ;
struct TYPE_9__ {int /*<<< orphan*/  mode; } ;
typedef  int /*<<< orphan*/  RF90_RADIO_PATH_E ;

/* Variables and functions */
 scalar_t__ AFE_XTAL_CTRL ; 
 scalar_t__ AcmHwCtrl ; 
 TYPE_4__* Adapter ; 
 int COMP_INIT ; 
 int COMP_RF ; 
 int /*<<< orphan*/  CamResetAllEntry (struct net_device*) ; 
 int /*<<< orphan*/  ChkFwCmdIoDone (struct net_device*) ; 
 int FW_BB_RESET_ENABLE ; 
 int FW_IQK_ENABLE ; 
 int FW_RA_ACTIVE ; 
 int FW_RA_REFRESH ; 
 int FW_RA_RESET ; 
 int FirmwareDownload92S (struct net_device*) ; 
 int GPIOMUX_EN ; 
 int /*<<< orphan*/  HalUsbInMpdu (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  IDR0 ; 
 int /*<<< orphan*/  IDR4 ; 
 scalar_t__ MAC_PINMUX_CFG ; 
 scalar_t__ MAX_RX_QUEUE ; 
 int /*<<< orphan*/  MgntActSet_RF_State (struct net_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int PHY_BBConfig8192S (struct net_device*) ; 
 int /*<<< orphan*/  PHY_GetHWRegOriginalValue (struct net_device*) ; 
 int PHY_MACConfig8192S (struct net_device*) ; 
 int PHY_RFConfig8192S (struct net_device*) ; 
 int /*<<< orphan*/  PHY_SetTxPowerLevel8192S (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ PipeIndex ; 
 int /*<<< orphan*/  PlatformAcquireSpinLock (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PlatformReleaseSpinLock (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PlatformStartWorkItem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PlatformUsbEnableInPipes (TYPE_4__*) ; 
 scalar_t__ RESET_TYPE_NORESET ; 
 scalar_t__ RF_1T1R ; 
 scalar_t__ RF_CHANGE_BY_PS ; 
 scalar_t__ RF_CHANGE_BY_SW ; 
 scalar_t__ RF_CTRL ; 
 int RF_EN ; 
 int /*<<< orphan*/  RF_OP_By_SW_3wire ; 
 int RF_RSTB ; 
 int RF_SDMRSTB ; 
 int /*<<< orphan*/  RT_RX_SPINLOCK ; 
 int /*<<< orphan*/  RT_TRACE (int,char*,...) ; 
 int SCR_NoSKMC ; 
 int SCR_RxDecEnable ; 
 int SCR_TxEncEnable ; 
 scalar_t__ SECR ; 
 scalar_t__ SPS1_CTRL ; 
 scalar_t__ VERSION_8192S_ACUT ; 
 int /*<<< orphan*/ * WDCAPARA_ADD ; 
 int /*<<< orphan*/  WFM5 ; 
 int /*<<< orphan*/  WIRELESS_MODE_G ; 
 int /*<<< orphan*/  bCCKEn ; 
 int /*<<< orphan*/  bOFDMEn ; 
 int /*<<< orphan*/  eRfOff ; 
 int /*<<< orphan*/  eRfOn ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 TYPE_3__* pHalData ; 
 int /*<<< orphan*/  rFPGA0_AnalogParameter2 ; 
 int /*<<< orphan*/  rFPGA0_RFMOD ; 
 int read_nic_byte (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  rtl8192SU_HwConfigureRTL8192SUsb (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192SU_MacConfigAfterFwDownload (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192SU_MacConfigBeforeFwDownloadASIC (struct net_device*) ; 
 int /*<<< orphan*/  rtl8192_SetWirelessMode (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int /*<<< orphan*/ ,int,int,...) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_nic_word (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool rtl8192SU_adapter_start(struct net_device *dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	//u32 					dwRegRead = 0;
	//bool 					init_status = true;
	//u32					ulRegRead;
	bool             				rtStatus = true;
	//u8					PipeIndex;
	//u8					eRFPath, tmpU1b;
	u8 fw_download_times = 1;


	RT_TRACE(COMP_INIT, "--->InitializeAdapter8192SUsb()\n");

	//pHalData->bGPIOChangeRF = FALSE;


	//
	// <Roger_Notes> 2008.06.15.
	//
	// Initialization Steps on RTL8192SU:
	// a. MAC initialization prior to sending down firmware code.
	// b. Download firmware code step by step(i.e., IMEM, EMEM, DMEM).
	// c. MAC configuration after firmware has been download successfully.
	// d. Initialize BB related configurations.
	// e. Initialize RF related configurations.
	// f.  Start to BulkIn transfer.
	//

	//
	//a. MAC initialization prior to send down firmware code.
	//
start:
	rtl8192SU_MacConfigBeforeFwDownloadASIC(dev);

	//
	//b. Download firmware code step by step(i.e., IMEM, EMEM, DMEM).
	//
	rtStatus = FirmwareDownload92S(dev);
	if(rtStatus != true)
	{
		if(fw_download_times == 1){
			RT_TRACE(COMP_INIT, "InitializeAdapter8192SUsb(): Download Firmware failed once, Download again!!\n");
			fw_download_times = fw_download_times + 1;
			goto start;
		}else{
			RT_TRACE(COMP_INIT, "InitializeAdapter8192SUsb(): Download Firmware failed twice, end!!\n");
		goto end;
	}
	}
	//
	//c. MAC configuration after firmware has been download successfully.
	//
	rtl8192SU_MacConfigAfterFwDownload(dev);

	//priv->bLbusEnable = TRUE;
	//if(priv->RegRfOff == TRUE)
	//	priv->eRFPowerState = eRfOff;

	// Save target channel
	// <Roger_Notes> Current Channel will be updated again later.
	//priv->CurrentChannel = Channel;
	rtStatus = PHY_MACConfig8192S(dev);//===>ok
	if(rtStatus != true)
	{
		RT_TRACE(COMP_INIT, "InitializeAdapter8192SUsb(): Fail to configure MAC!!\n");
		goto end;
	}
	if (1){
		int i;
		for (i=0; i<4; i++)
			write_nic_dword(dev,WDCAPARA_ADD[i], 0x5e4322);
		write_nic_byte(dev,AcmHwCtrl, 0x01);
	}


	//
	//d. Initialize BB related configurations.
	//

	rtStatus = PHY_BBConfig8192S(dev);//===>ok
	if(rtStatus != true)
	{
		RT_TRACE(COMP_INIT, "InitializeAdapter8192SUsb(): Fail to configure BB!!\n");
		goto end;
	}

	rtl8192_setBBreg(dev, rFPGA0_AnalogParameter2, 0xff, 0x58);//===>ok

	//
	// e. Initialize RF related configurations.
	//
	// 2007/11/02 MH Before initalizing RF. We can not use FW to do RF-R/W.
	priv->Rf_Mode = RF_OP_By_SW_3wire;

	// For RF test only from Scott's suggestion
	//write_nic_byte(dev, 0x27, 0xDB);
	//write_nic_byte(dev, 0x1B, 0x07);


	write_nic_byte(dev, AFE_XTAL_CTRL+1, 0xDB);

	// <Roger_Notes> The following IOs are configured for each RF modules.
	// Enable RF module and reset RF and SDM module. 2008.11.17.
	if(priv->card_8192_version == VERSION_8192S_ACUT)
		write_nic_byte(dev, SPS1_CTRL+3, (u8)(RF_EN|RF_RSTB|RF_SDMRSTB)); // Fix A-Cut bug.
	else
		write_nic_byte(dev, RF_CTRL, (u8)(RF_EN|RF_RSTB|RF_SDMRSTB));

	rtStatus = PHY_RFConfig8192S(dev);//===>ok
	if(rtStatus != true)
	{
		RT_TRACE(COMP_INIT, "InitializeAdapter8192SUsb(): Fail to configure RF!!\n");
		goto end;
	}


	// Set CCK and OFDM Block "ON"
	rtl8192_setBBreg(dev, rFPGA0_RFMOD, bCCKEn, 0x1);
	rtl8192_setBBreg(dev, rFPGA0_RFMOD, bOFDMEn, 0x1);

	//
	// Turn off Radio B while RF type is 1T1R by SD3 Wilsion's request.
	// Revised by Roger, 2008.12.18.
	//
	if(priv->rf_type == RF_1T1R)
	{
		// This is needed for PHY_REG after 20081219
		rtl8192_setBBreg(dev, rFPGA0_RFMOD, 0xff000000, 0x03);
		// This is needed for PHY_REG before 20081219
		//PHY_SetBBReg(Adapter, rOFDM0_TRxPathEnable, bMaskByte0, 0x11);
	}


	//LZM 090219
	// Set CCK and OFDM Block "ON"
	//rtl8192_setBBreg(dev, rFPGA0_RFMOD, bCCKEn, 0x1);
	//rtl8192_setBBreg(dev, rFPGA0_RFMOD, bOFDMEn, 0x1);


	//3//Get hardware version, do it in read eeprom?
	//GetHardwareVersion819xUsb(Adapter);

	//3//
	//3 //Set Hardware
	//3//
	rtl8192SU_HwConfigureRTL8192SUsb(dev);//==>ok

	//
	// <Roger_Notes> We set MAC address here if autoload was failed before,
	// otherwise IDR0 will NOT contain any value.
	//
	write_nic_dword(dev, IDR0, ((u32*)dev->dev_addr)[0]);
	write_nic_word(dev, IDR4, ((u16*)(dev->dev_addr + 4))[0]);
	if(!priv->bInHctTest)
	{
		if(priv->ResetProgress == RESET_TYPE_NORESET)
		{
			//RT_TRACE(COMP_MLME, DBG_LOUD, ("Initializeadapter8192SUsb():RegWirelessMode(%#x) \n", Adapter->RegWirelessMode));
			//Adapter->HalFunc.SetWirelessModeHandler(Adapter, Adapter->RegWirelessMode);
			rtl8192_SetWirelessMode(dev, priv->ieee80211->mode);//===>ok
	        }
	}
	else
	{
		priv->ieee80211->mode = WIRELESS_MODE_G;
	 	rtl8192_SetWirelessMode(dev, WIRELESS_MODE_G);
	}

	//Security related.
	//-----------------------------------------------------------------------------
	// Set up security related. 070106, by rcnjko:
	// 1. Clear all H/W keys.
	// 2. Enable H/W encryption/decryption.
	//-----------------------------------------------------------------------------
	//CamResetAllEntry(Adapter);
	//Adapter->HalFunc.EnableHWSecCfgHandler(Adapter);

	//SecClearAllKeys(Adapter);
	CamResetAllEntry(dev);
	//SecInit(Adapter);
	{
		u8 SECR_value = 0x0;
		SECR_value |= SCR_TxEncEnable;
		SECR_value |= SCR_RxDecEnable;
		SECR_value |= SCR_NoSKMC;
		write_nic_byte(dev, SECR, SECR_value);
	}

#ifdef TO_DO_LIST

	//PHY_UpdateInitialGain(dev);

	if(priv->RegRfOff == true)
	{ // User disable RF via registry.
		u8 eRFPath = 0;

		RT_TRACE((COMP_INIT|COMP_RF), "InitializeAdapter8192SUsb(): Turn off RF for RegRfOff ----------\n");
		MgntActSet_RF_State(dev, eRfOff, RF_CHANGE_BY_SW);
		// Those action will be discard in MgntActSet_RF_State because off the same state
		for(eRFPath = 0; eRFPath <priv->NumTotalRFPath; eRFPath++)
			rtl8192_setBBreg(dev, (RF90_RADIO_PATH_E)eRFPath, 0x4, 0xC00, 0x0);
	}
	else if(priv->RfOffReason > RF_CHANGE_BY_PS)
	{ // H/W or S/W RF OFF before sleep.
		RT_TRACE((COMP_INIT|COMP_RF), "InitializeAdapter8192SUsb(): Turn off RF for RfOffReason(%d) ----------\n", priv->RfOffReason);
		MgntActSet_RF_State(dev, eRfOff, priv->RfOffReason);
	}
	else
	{
		priv->eRFPowerState = eRfOn;
		priv->RfOffReason = 0;
		RT_TRACE((COMP_INIT|COMP_RF), "InitializeAdapter8192SUsb(): RF is on ----------\n");
	}

#endif


//
// f. Start to BulkIn transfer.
//
#ifdef TO_DO_LIST

#ifndef UNDER_VISTA
	{
		u8	i;
		PlatformAcquireSpinLock(Adapter, RT_RX_SPINLOCK);

		for(PipeIndex=0; PipeIndex < MAX_RX_QUEUE; PipeIndex++)
		{
			if (PipeIndex == 0)
			{
				for(i=0; i<32; i++)
				HalUsbInMpdu(Adapter, PipeIndex);
			}
			else
			{
				//HalUsbInMpdu(Adapter, PipeIndex);
				//HalUsbInMpdu(Adapter, PipeIndex);
				//HalUsbInMpdu(Adapter, PipeIndex);
			}
		}
		PlatformReleaseSpinLock(Adapter, RT_RX_SPINLOCK);
	}
#else
		// Joseph add to 819X code base for Vista USB platform.
		// This part may need to be add to Hal819xU code base. too.
	        PlatformUsbEnableInPipes(Adapter);
#endif

	RT_TRACE(COMP_INIT, "HighestOperaRate = %x\n", Adapter->MgntInfo.HighestOperaRate);

	PlatformStartWorkItem( &(pHalData->RtUsbCheckForHangWorkItem) );

	//
	// <Roger_EXP> The following  configurations are for ASIC verification temporally.
	// 2008.07.10.
	//

#endif

	//
	// Read EEPROM TX power index and PHY_REG_PG.txt to capture correct
	// TX power index for different rate set.
	//
	//if(priv->card_8192_version >= VERSION_8192S_ACUT)
	{
		// Get original hw reg values
		PHY_GetHWRegOriginalValue(dev);

		// Write correct tx power index//FIXLZM
		PHY_SetTxPowerLevel8192S(dev, priv->chan);
	}

	{
	u8  tmpU1b = 0;
	// EEPROM R/W workaround
	tmpU1b = read_nic_byte(dev, MAC_PINMUX_CFG);
	write_nic_byte(dev, MAC_PINMUX_CFG, tmpU1b&(~GPIOMUX_EN));
	}

//
//<Roger_Notes> 2008.08.19.
// We return status here for temporal FPGA verification, 2008.08.19.

#ifdef RTL8192SU_FW_IQK
	write_nic_dword(dev, WFM5, FW_IQK_ENABLE);
	ChkFwCmdIoDone(dev);
#endif

	//
	// <Roger_Notes> We enable high power mechanism after NIC initialized.
	// 2008.11.27.
	//
	write_nic_dword(dev, WFM5, FW_RA_RESET);
	ChkFwCmdIoDone(dev);
	write_nic_dword(dev, WFM5, FW_RA_ACTIVE);
	ChkFwCmdIoDone(dev);
	write_nic_dword(dev, WFM5, FW_RA_REFRESH);
	ChkFwCmdIoDone(dev);
	write_nic_dword(dev, WFM5, FW_BB_RESET_ENABLE);

// <Roger_Notes> We return status here for temporal FPGA verification. 2008.05.12.
//

end:
return rtStatus;
}