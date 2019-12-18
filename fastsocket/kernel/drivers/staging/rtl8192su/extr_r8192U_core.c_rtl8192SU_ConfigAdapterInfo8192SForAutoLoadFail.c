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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct r8192_priv {int bIgnoreDiffRateTxPowerOffset; int EEPROMThermalMeter; int** RfCckChnlAreaTxPwr; int** RfOfdmChnlAreaTxPwr1T; int** RfOfdmChnlAreaTxPwr2T; int** RfTxPwrLevelCck; int** RfTxPwrLevelOfdm1T; int** RfTxPwrLevelOfdm2T; int TSSI_13dBm; int* ThermalMeter; int /*<<< orphan*/  LedStrategy; int /*<<< orphan*/  EEPROMCrystalCap; int /*<<< orphan*/  CrystalCap; int /*<<< orphan*/  EEPROMTxPowerDiff; int /*<<< orphan*/  TxPowerDiff; int /*<<< orphan*/  LegacyHTTxPowerDiff; int /*<<< orphan*/  EEPROMTxPwrTkMode; void* EEPROMTSSI_B; void* EEPROMTSSI_A; int /*<<< orphan*/  EEPROMTxPwrBase; int /*<<< orphan*/  rf_type; int /*<<< orphan*/  EEPROMBoardType; int /*<<< orphan*/ * EEPROMUsbPhyParam; int /*<<< orphan*/  EEPROMUsbOption; scalar_t__ eeprom_ChannelPlan; scalar_t__ eeprom_SubCustomerID; scalar_t__ eeprom_CustomerID; scalar_t__ eeprom_pid; scalar_t__ eeprom_vid; scalar_t__ card_8192_version; } ;
struct net_device {int* dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  EEPROM_Default_BoardType ; 
 int /*<<< orphan*/  EEPROM_Default_CrystalCap ; 
 int /*<<< orphan*/  EEPROM_Default_PwDiff ; 
 void* EEPROM_Default_TSSI ; 
 int EEPROM_Default_ThermalMeter ; 
 int EEPROM_Default_TxPower ; 
 int /*<<< orphan*/  EEPROM_Default_TxPowerBase ; 
 int /*<<< orphan*/  EEPROM_Default_TxPwrTkMode ; 
 int /*<<< orphan*/  EEPROM_USB_Default_OPTIONAL_FUNC ; 
 int /*<<< orphan*/  EEPROM_USB_Default_PHY_PARAM ; 
 int /*<<< orphan*/  IDR0 ; 
 int /*<<< orphan*/  IDR4 ; 
 scalar_t__ PMC_FSM ; 
 int /*<<< orphan*/  RF_1T2R ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  SW_LED_MODE0 ; 
 scalar_t__ SYS_ISO_CTRL ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  init_rate_adaptive (struct net_device*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_nic_word (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
rtl8192SU_ConfigAdapterInfo8192SForAutoLoadFail(struct net_device* dev)
{
	struct r8192_priv 	*priv = ieee80211_priv(dev);
	//u16			i,usValue;
	//u8 sMacAddr[6] = {0x00, 0xE0, 0x4C, 0x81, 0x92, 0x00};
	u8		rf_path, index;	// For EEPROM/EFUSE After V0.6_1117
	int	i;

	RT_TRACE(COMP_INIT, "====> ConfigAdapterInfo8192SForAutoLoadFail\n");

	write_nic_byte(dev, SYS_ISO_CTRL+1, 0xE8); // Isolation signals from Loader
	//PlatformStallExecution(10000);
	mdelay(10);
	write_nic_byte(dev, PMC_FSM, 0x02); // Enable Loader Data Keep

	//RT_ASSERT(priv->AutoloadFailFlag==TRUE, ("ReadAdapterInfo8192SEEPROM(): AutoloadFailFlag !=TRUE\n"));

	// Initialize IC Version && Channel Plan
	priv->eeprom_vid = 0;
	priv->eeprom_pid = 0;
	priv->card_8192_version = 0;
	priv->eeprom_ChannelPlan = 0;
	priv->eeprom_CustomerID = 0;
	priv->eeprom_SubCustomerID = 0;
	priv->bIgnoreDiffRateTxPowerOffset = false;

	RT_TRACE(COMP_INIT, "EEPROM VID = 0x%4x\n", priv->eeprom_vid);
	RT_TRACE(COMP_INIT, "EEPROM PID = 0x%4x\n", priv->eeprom_pid);
	RT_TRACE(COMP_INIT, "EEPROM Customer ID: 0x%2x\n", priv->eeprom_CustomerID);
	RT_TRACE(COMP_INIT, "EEPROM SubCustomer ID: 0x%2x\n", priv->eeprom_SubCustomerID);
	RT_TRACE(COMP_INIT, "EEPROM ChannelPlan = 0x%4x\n", priv->eeprom_ChannelPlan);
	RT_TRACE(COMP_INIT, "IgnoreDiffRateTxPowerOffset = %d\n", priv->bIgnoreDiffRateTxPowerOffset);



	priv->EEPROMUsbOption = EEPROM_USB_Default_OPTIONAL_FUNC;
	RT_TRACE(COMP_INIT, "USB Option = %#x\n", priv->EEPROMUsbOption);

	for(i=0; i<5; i++)
		priv->EEPROMUsbPhyParam[i] = EEPROM_USB_Default_PHY_PARAM;

	//RT_PRINT_DATA(COMP_INIT|COMP_EFUSE, DBG_LOUD, ("EFUSE USB PHY Param: \n"), priv->EEPROMUsbPhyParam, 5);

	{
	//<Roger_Notes> In this case, we random assigh MAC address here. 2008.10.15.
		static u8 sMacAddr[6] = {0x00, 0xE0, 0x4C, 0x81, 0x92, 0x00};
		u8	i;

        	//sMacAddr[5] = (u8)GetRandomNumber(1, 254);

		for(i = 0; i < 6; i++)
			dev->dev_addr[i] = sMacAddr[i];
	}
	//NicIFSetMacAddress(Adapter, Adapter->PermanentAddress);
	write_nic_dword(dev, IDR0, ((u32*)dev->dev_addr)[0]);
	write_nic_word(dev, IDR4, ((u16*)(dev->dev_addr + 4))[0]);

	RT_TRACE(COMP_INIT, "ReadAdapterInfo8192SEFuse(), Permanent Address = %02x-%02x-%02x-%02x-%02x-%02x\n",
			dev->dev_addr[0], dev->dev_addr[1],
			dev->dev_addr[2], dev->dev_addr[3],
			dev->dev_addr[4], dev->dev_addr[5]);

	priv->EEPROMBoardType = EEPROM_Default_BoardType;
	priv->rf_type = RF_1T2R; //RF_2T2R
	priv->EEPROMTxPowerDiff = EEPROM_Default_PwDiff;
	priv->EEPROMThermalMeter = EEPROM_Default_ThermalMeter;
	priv->EEPROMCrystalCap = EEPROM_Default_CrystalCap;
	priv->EEPROMTxPwrBase = EEPROM_Default_TxPowerBase;
	priv->EEPROMTSSI_A = EEPROM_Default_TSSI;
	priv->EEPROMTSSI_B = EEPROM_Default_TSSI;
	priv->EEPROMTxPwrTkMode = EEPROM_Default_TxPwrTkMode;



	for (rf_path = 0; rf_path < 2; rf_path++)
	{
		for (i = 0; i < 3; i++)
		{
			// Read CCK RF A & B Tx power
			priv->RfCckChnlAreaTxPwr[rf_path][i] =
			priv->RfOfdmChnlAreaTxPwr1T[rf_path][i] =
			priv->RfOfdmChnlAreaTxPwr2T[rf_path][i] =
			(u8)(EEPROM_Default_TxPower & 0xff);
		}
	}

	for (i = 0; i < 3; i++)
	{
		//RT_TRACE((COMP_EFUSE), "CCK RF-%d CHan_Area-%d = 0x%x\n",  rf_path, i,
		//priv->RfCckChnlAreaTxPwr[rf_path][i]);
		//RT_TRACE((COMP_EFUSE), "OFDM-1T RF-%d CHan_Area-%d = 0x%x\n",  rf_path, i,
		//priv->RfOfdmChnlAreaTxPwr1T[rf_path][i]);
		//RT_TRACE((COMP_EFUSE), "OFDM-2T RF-%d CHan_Area-%d = 0x%x\n",  rf_path, i,
		//priv->RfOfdmChnlAreaTxPwr2T[rf_path][i]);
	}

	// Assign dedicated channel tx power
	for(i=0; i<14; i++)	// channel 1~3 use the same Tx Power Level.
		{
		if (i < 3)			// Cjanel 1-3
			index = 0;
		else if (i < 9)		// Channel 4-9
			index = 1;
		else				// Channel 10-14
			index = 2;

		// Record A & B CCK /OFDM - 1T/2T Channel area tx power
		priv->RfTxPwrLevelCck[rf_path][i]  =
		priv->RfCckChnlAreaTxPwr[rf_path][index];
		priv->RfTxPwrLevelOfdm1T[rf_path][i]  =
		priv->RfOfdmChnlAreaTxPwr1T[rf_path][index];
		priv->RfTxPwrLevelOfdm2T[rf_path][i]  =
		priv->RfOfdmChnlAreaTxPwr2T[rf_path][index];
		}

		for(i=0; i<14; i++)
		{
		//RT_TRACE((COMP_EFUSE), "Rf-%d TxPwr CH-%d CCK OFDM_1T OFDM_2T= 0x%x/0x%x/0x%x\n",
		//rf_path, i, priv->RfTxPwrLevelCck[0][i],
		//priv->RfTxPwrLevelOfdm1T[0][i] ,
		//priv->RfTxPwrLevelOfdm2T[0][i] );
		}

	//
	// Update remained HAL variables.
	//
	priv->TSSI_13dBm = priv->EEPROMThermalMeter *100;
	priv->LegacyHTTxPowerDiff = priv->EEPROMTxPowerDiff;//new
	priv->TxPowerDiff = priv->EEPROMTxPowerDiff;
	//priv->AntennaTxPwDiff[0] = (priv->EEPROMTxPowerDiff & 0xf);// Antenna B gain offset to antenna A, bit0~3
	//priv->AntennaTxPwDiff[1] = ((priv->EEPROMTxPowerDiff & 0xf0)>>4);// Antenna C gain offset to antenna A, bit4~7
	priv->CrystalCap = priv->EEPROMCrystalCap;	// CrystalCap, bit12~15
	priv->ThermalMeter[0] = priv->EEPROMThermalMeter;// ThermalMeter, bit0~3 for RFIC1, bit4~7 for RFIC2
	priv->LedStrategy = SW_LED_MODE0;

	init_rate_adaptive(dev);

	RT_TRACE(COMP_INIT, "<==== ConfigAdapterInfo8192SForAutoLoadFail\n");

}