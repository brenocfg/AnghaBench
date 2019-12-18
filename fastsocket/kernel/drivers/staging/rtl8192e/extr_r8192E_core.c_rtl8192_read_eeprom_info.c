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
typedef  scalar_t__ u16 ;
struct r8192_priv {int AutoloadFailFlag; int eeprom_vid; int eeprom_did; int eeprom_CustomerID; int eeprom_ChannelPlan; int card_8192_version; int bTXPowerDataReadFromEEPORM; scalar_t__ rf_type; int EEPROMLegacyHTTxPowerDiff; int EEPROMThermalMeter; int TSSI_13dBm; scalar_t__ epromtype; int EEPROMAntPwDiff; int EEPROMCrystalCap; int* EEPROMRfACCKChnl1TxPwLevel; int* EEPROMRfAOfdmChnlTxPwLevel; int* EEPROMRfCCCKChnl1TxPwLevel; int* EEPROMRfCOfdmChnlTxPwLevel; int LegacyHTTxPowerDiff; int* AntennaTxPwDiff; int CrystalCap; int* ThermalMeter; int* TxPowerLevelCCK_A; int* TxPowerLevelOFDM24G_A; int* TxPowerLevelCCK_C; int* TxPowerLevelOFDM24G_C; int RegChannelPlan; int ChannelPlan; int CustomerID; int ScanDelay; void* LedStrategy; int /*<<< orphan*/  rf_chip; int /*<<< orphan*/ * EEPROMTxPowerLevelOFDM24G; int /*<<< orphan*/ * TxPowerLevelOFDM24G; int /*<<< orphan*/ * EEPROMTxPowerLevelCCK; int /*<<< orphan*/ * TxPowerLevelCCK; } ;
struct net_device {int /*<<< orphan*/ * dev_addr; } ;
typedef  int VERSION_8190 ;

/* Variables and functions */
 int CHANNEL_PLAN_LEN ; 
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  COMP_TRACE ; 
 int EEPROM_C56_CrystalCap ; 
 int EEPROM_C56_RfA_CCK_Chnl1_TxPwIndex ; 
 int EEPROM_C56_RfC_CCK_Chnl1_TxPwIndex ; 
#define  EEPROM_CID_CAMEO 145 
#define  EEPROM_CID_DEFAULT 144 
#define  EEPROM_CID_DLINK 143 
#define  EEPROM_CID_NetCore 142 
#define  EEPROM_CID_Nettronix 141 
#define  EEPROM_CID_Pronet 140 
#define  EEPROM_CID_RUNTOP 139 
#define  EEPROM_CID_TOSHIBA 138 
#define  EEPROM_CID_WHQL 137 
 int EEPROM_Customer_ID ; 
 int EEPROM_DID ; 
 void* EEPROM_Default_AntTxPowerDiff ; 
 int EEPROM_Default_LegacyHTTxPowerDiff ; 
 int EEPROM_Default_ThermalMeter ; 
 scalar_t__ EEPROM_Default_TxPower ; 
 void* EEPROM_Default_TxPowerLevel ; 
 void* EEPROM_Default_TxPwDiff_CrystalCap ; 
 int EEPROM_ICVersion_ChannelPlan ; 
 scalar_t__ EEPROM_NODE_ADDRESS_BYTE_0 ; 
 int EEPROM_RFInd_PowerDiff ; 
 int EEPROM_ThermalMeter ; 
 int EEPROM_TxPwDiff_CrystalCap ; 
 scalar_t__ EEPROM_TxPwIndex_CCK ; 
 scalar_t__ EEPROM_TxPwIndex_OFDM_24G ; 
 int EEPROM_VID ; 
 scalar_t__ EPROM_93c46 ; 
 scalar_t__ EPROM_93c56 ; 
 void* HW_LED ; 
 scalar_t__ RF_1T2R ; 
 scalar_t__ RF_2T4R ; 
 int /*<<< orphan*/  RF_8256 ; 
 scalar_t__ RTL8190_EEPROM_ID ; 
 scalar_t__ RTL819X_DEFAULT_RF_TYPE ; 
#define  RT_CID_819x_CAMEO 136 
#define  RT_CID_819x_Netcore 135 
#define  RT_CID_819x_RUNTOP 134 
#define  RT_CID_DEFAULT 133 
 void* RT_CID_DLINK ; 
#define  RT_CID_Nettronix 132 
#define  RT_CID_PRONET 131 
#define  RT_CID_TOSHIBA 130 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,...) ; 
 void* SW_LED_MODE1 ; 
 void* SW_LED_MODE2 ; 
 void* SW_LED_MODE3 ; 
 void* SW_LED_MODE4 ; 
 void* SW_LED_MODE5 ; 
 void* SW_LED_MODE6 ; 
#define  VERSION_8190_BD 129 
#define  VERSION_8190_BE 128 
 int eprom_read (struct net_device*,int) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  init_rate_adaptive (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static void rtl8192_read_eeprom_info(struct net_device* dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);

	u8			tempval;
#ifdef RTL8192E
	u8			ICVer8192, ICVer8256;
#endif
	u16			i,usValue, IC_Version;
	u16			EEPROMId;
#ifdef RTL8190P
   	u8			offset;//, tmpAFR;
    	u8      		EepromTxPower[100];
#endif
	u8 bMac_Tmp_Addr[6] = {0x00, 0xe0, 0x4c, 0x00, 0x00, 0x01};
	RT_TRACE(COMP_INIT, "====> rtl8192_read_eeprom_info\n");


	// TODO: I don't know if we need to apply EF function to EEPROM read function

	//2 Read EEPROM ID to make sure autoload is success
	EEPROMId = eprom_read(dev, 0);
	if( EEPROMId != RTL8190_EEPROM_ID )
	{
		RT_TRACE(COMP_ERR, "EEPROM ID is invalid:%x, %x\n", EEPROMId, RTL8190_EEPROM_ID);
		priv->AutoloadFailFlag=true;
	}
	else
	{
		priv->AutoloadFailFlag=false;
	}

	//
	// Assign Chip Version ID
	//
	// Read IC Version && Channel Plan
	if(!priv->AutoloadFailFlag)
	{
		// VID, PID
		priv->eeprom_vid = eprom_read(dev, (EEPROM_VID >> 1));
		priv->eeprom_did = eprom_read(dev, (EEPROM_DID >> 1));

		usValue = eprom_read(dev, (u16)(EEPROM_Customer_ID>>1)) >> 8 ;
		priv->eeprom_CustomerID = (u8)( usValue & 0xff);
		usValue = eprom_read(dev, (EEPROM_ICVersion_ChannelPlan>>1));
		priv->eeprom_ChannelPlan = usValue&0xff;
		IC_Version = ((usValue&0xff00)>>8);

#ifdef RTL8190P
		priv->card_8192_version = (VERSION_8190)(IC_Version);
#else
	#ifdef RTL8192E
		ICVer8192 = (IC_Version&0xf);		//bit0~3; 1:A cut, 2:B cut, 3:C cut...
		ICVer8256 = ((IC_Version&0xf0)>>4);//bit4~6, bit7 reserved for other RF chip; 1:A cut, 2:B cut, 3:C cut...
		RT_TRACE(COMP_INIT, "\nICVer8192 = 0x%x\n", ICVer8192);
		RT_TRACE(COMP_INIT, "\nICVer8256 = 0x%x\n", ICVer8256);
		if(ICVer8192 == 0x2)	//B-cut
		{
			if(ICVer8256 == 0x5) //E-cut
				priv->card_8192_version= VERSION_8190_BE;
		}
	#endif
#endif
		switch(priv->card_8192_version)
		{
			case VERSION_8190_BD:
			case VERSION_8190_BE:
				break;
			default:
				priv->card_8192_version = VERSION_8190_BD;
				break;
		}
		RT_TRACE(COMP_INIT, "\nIC Version = 0x%x\n", priv->card_8192_version);
	}
	else
	{
		priv->card_8192_version = VERSION_8190_BD;
		priv->eeprom_vid = 0;
		priv->eeprom_did = 0;
		priv->eeprom_CustomerID = 0;
		priv->eeprom_ChannelPlan = 0;
		RT_TRACE(COMP_INIT, "\nIC Version = 0x%x\n", 0xff);
	}

	RT_TRACE(COMP_INIT, "EEPROM VID = 0x%4x\n", priv->eeprom_vid);
	RT_TRACE(COMP_INIT, "EEPROM DID = 0x%4x\n", priv->eeprom_did);
	RT_TRACE(COMP_INIT,"EEPROM Customer ID: 0x%2x\n", priv->eeprom_CustomerID);

	//2 Read Permanent MAC address
	if(!priv->AutoloadFailFlag)
	{
		for(i = 0; i < 6; i += 2)
		{
			usValue = eprom_read(dev, (u16) ((EEPROM_NODE_ADDRESS_BYTE_0+i)>>1));
			*(u16*)(&dev->dev_addr[i]) = usValue;
		}
	} else {
		// when auto load failed,  the last address byte set to be a random one.
		// added by david woo.2007/11/7
		memcpy(dev->dev_addr, bMac_Tmp_Addr, 6);
	}

	RT_TRACE(COMP_INIT, "Permanent Address = %02x-%02x-%02x-%02x-%02x-%02x\n",
			dev->dev_addr[0], dev->dev_addr[1],
			dev->dev_addr[2], dev->dev_addr[3],
			dev->dev_addr[4], dev->dev_addr[5]);

		//2 TX Power Check EEPROM Fail or not
	if(priv->card_8192_version > VERSION_8190_BD) {
		priv->bTXPowerDataReadFromEEPORM = true;
	} else {
		priv->bTXPowerDataReadFromEEPORM = false;
	}

	// 2007/11/15 MH 8190PCI Default=2T4R, 8192PCIE dafault=1T2R
	priv->rf_type = RTL819X_DEFAULT_RF_TYPE;

	if(priv->card_8192_version > VERSION_8190_BD)
	{
		// Read RF-indication and Tx Power gain index diff of legacy to HT OFDM rate.
		if(!priv->AutoloadFailFlag)
		{
			tempval = (eprom_read(dev, (EEPROM_RFInd_PowerDiff>>1))) & 0xff;
			priv->EEPROMLegacyHTTxPowerDiff = tempval & 0xf;	// bit[3:0]

			if (tempval&0x80)	//RF-indication, bit[7]
				priv->rf_type = RF_1T2R;
			else
				priv->rf_type = RF_2T4R;
		}
		else
		{
			priv->EEPROMLegacyHTTxPowerDiff = EEPROM_Default_LegacyHTTxPowerDiff;
		}
		RT_TRACE(COMP_INIT, "EEPROMLegacyHTTxPowerDiff = %d\n",
			priv->EEPROMLegacyHTTxPowerDiff);

		// Read ThermalMeter from EEPROM
		if(!priv->AutoloadFailFlag)
		{
			priv->EEPROMThermalMeter = (u8)(((eprom_read(dev, (EEPROM_ThermalMeter>>1))) & 0xff00)>>8);
		}
		else
		{
			priv->EEPROMThermalMeter = EEPROM_Default_ThermalMeter;
		}
		RT_TRACE(COMP_INIT, "ThermalMeter = %d\n", priv->EEPROMThermalMeter);
		//vivi, for tx power track
		priv->TSSI_13dBm = priv->EEPROMThermalMeter *100;

		if(priv->epromtype == EPROM_93c46)
		{
		// Read antenna tx power offset of B/C/D to A and CrystalCap from EEPROM
		if(!priv->AutoloadFailFlag)
		{
				usValue = eprom_read(dev, (EEPROM_TxPwDiff_CrystalCap>>1));
				priv->EEPROMAntPwDiff = (usValue&0x0fff);
				priv->EEPROMCrystalCap = (u8)((usValue&0xf000)>>12);
		}
		else
		{
				priv->EEPROMAntPwDiff = EEPROM_Default_AntTxPowerDiff;
				priv->EEPROMCrystalCap = EEPROM_Default_TxPwDiff_CrystalCap;
		}
			RT_TRACE(COMP_INIT, "EEPROMAntPwDiff = %d\n", priv->EEPROMAntPwDiff);
			RT_TRACE(COMP_INIT, "EEPROMCrystalCap = %d\n", priv->EEPROMCrystalCap);

		//
		// Get per-channel Tx Power Level
		//
		for(i=0; i<14; i+=2)
		{
			if(!priv->AutoloadFailFlag)
			{
				usValue = eprom_read(dev, (u16) ((EEPROM_TxPwIndex_CCK+i)>>1) );
			}
			else
			{
				usValue = EEPROM_Default_TxPower;
			}
			*((u16*)(&priv->EEPROMTxPowerLevelCCK[i])) = usValue;
			RT_TRACE(COMP_INIT,"CCK Tx Power Level, Index %d = 0x%02x\n", i, priv->EEPROMTxPowerLevelCCK[i]);
			RT_TRACE(COMP_INIT, "CCK Tx Power Level, Index %d = 0x%02x\n", i+1, priv->EEPROMTxPowerLevelCCK[i+1]);
		}
		for(i=0; i<14; i+=2)
		{
			if(!priv->AutoloadFailFlag)
			{
				usValue = eprom_read(dev, (u16) ((EEPROM_TxPwIndex_OFDM_24G+i)>>1) );
			}
			else
			{
				usValue = EEPROM_Default_TxPower;
			}
			*((u16*)(&priv->EEPROMTxPowerLevelOFDM24G[i])) = usValue;
			RT_TRACE(COMP_INIT, "OFDM 2.4G Tx Power Level, Index %d = 0x%02x\n", i, priv->EEPROMTxPowerLevelOFDM24G[i]);
			RT_TRACE(COMP_INIT, "OFDM 2.4G Tx Power Level, Index %d = 0x%02x\n", i+1, priv->EEPROMTxPowerLevelOFDM24G[i+1]);
		}
		}
		else if(priv->epromtype== EPROM_93c56)
		{
		#ifdef RTL8190P
			// Read CrystalCap from EEPROM
			if(!priv->AutoloadFailFlag)
			{
				priv->EEPROMAntPwDiff = EEPROM_Default_AntTxPowerDiff;
				priv->EEPROMCrystalCap = (u8)(((eprom_read(dev, (EEPROM_C56_CrystalCap>>1))) & 0xf000)>>12);
			}
			else
			{
				priv->EEPROMAntPwDiff = EEPROM_Default_AntTxPowerDiff;
				priv->EEPROMCrystalCap = EEPROM_Default_TxPwDiff_CrystalCap;
			}
			RT_TRACE(COMP_INIT,"EEPROMAntPwDiff = %d\n", priv->EEPROMAntPwDiff);
			RT_TRACE(COMP_INIT, "EEPROMCrystalCap = %d\n", priv->EEPROMCrystalCap);

			// Get Tx Power Level by Channel
			if(!priv->AutoloadFailFlag)
			{
				    // Read Tx power of Channel 1 ~ 14 from EEPROM.
			       for(i = 0; i < 12; i+=2)
				{
					if (i <6)
						offset = EEPROM_C56_RfA_CCK_Chnl1_TxPwIndex + i;
					else
						offset = EEPROM_C56_RfC_CCK_Chnl1_TxPwIndex + i - 6;
					usValue = eprom_read(dev, (offset>>1));
				       *((u16*)(&EepromTxPower[i])) = usValue;
				}

			       for(i = 0; i < 12; i++)
			       	{
			       		if (i <= 2)
						priv->EEPROMRfACCKChnl1TxPwLevel[i] = EepromTxPower[i];
					else if ((i >=3 )&&(i <= 5))
						priv->EEPROMRfAOfdmChnlTxPwLevel[i-3] = EepromTxPower[i];
					else if ((i >=6 )&&(i <= 8))
						priv->EEPROMRfCCCKChnl1TxPwLevel[i-6] = EepromTxPower[i];
					else
						priv->EEPROMRfCOfdmChnlTxPwLevel[i-9] = EepromTxPower[i];
				}
			}
			else
			{
				priv->EEPROMRfACCKChnl1TxPwLevel[0] = EEPROM_Default_TxPowerLevel;
				priv->EEPROMRfACCKChnl1TxPwLevel[1] = EEPROM_Default_TxPowerLevel;
				priv->EEPROMRfACCKChnl1TxPwLevel[2] = EEPROM_Default_TxPowerLevel;

				priv->EEPROMRfAOfdmChnlTxPwLevel[0] = EEPROM_Default_TxPowerLevel;
				priv->EEPROMRfAOfdmChnlTxPwLevel[1] = EEPROM_Default_TxPowerLevel;
				priv->EEPROMRfAOfdmChnlTxPwLevel[2] = EEPROM_Default_TxPowerLevel;

				priv->EEPROMRfCCCKChnl1TxPwLevel[0] = EEPROM_Default_TxPowerLevel;
				priv->EEPROMRfCCCKChnl1TxPwLevel[1] = EEPROM_Default_TxPowerLevel;
				priv->EEPROMRfCCCKChnl1TxPwLevel[2] = EEPROM_Default_TxPowerLevel;

				priv->EEPROMRfCOfdmChnlTxPwLevel[0] = EEPROM_Default_TxPowerLevel;
				priv->EEPROMRfCOfdmChnlTxPwLevel[1] = EEPROM_Default_TxPowerLevel;
				priv->EEPROMRfCOfdmChnlTxPwLevel[2] = EEPROM_Default_TxPowerLevel;
			}
			RT_TRACE(COMP_INIT, "priv->EEPROMRfACCKChnl1TxPwLevel[0] = 0x%x\n", priv->EEPROMRfACCKChnl1TxPwLevel[0]);
			RT_TRACE(COMP_INIT, "priv->EEPROMRfACCKChnl1TxPwLevel[1] = 0x%x\n", priv->EEPROMRfACCKChnl1TxPwLevel[1]);
			RT_TRACE(COMP_INIT, "priv->EEPROMRfACCKChnl1TxPwLevel[2] = 0x%x\n", priv->EEPROMRfACCKChnl1TxPwLevel[2]);
			RT_TRACE(COMP_INIT, "priv->EEPROMRfAOfdmChnlTxPwLevel[0] = 0x%x\n", priv->EEPROMRfAOfdmChnlTxPwLevel[0]);
			RT_TRACE(COMP_INIT, "priv->EEPROMRfAOfdmChnlTxPwLevel[1] = 0x%x\n", priv->EEPROMRfAOfdmChnlTxPwLevel[1]);
			RT_TRACE(COMP_INIT, "priv->EEPROMRfAOfdmChnlTxPwLevel[2] = 0x%x\n", priv->EEPROMRfAOfdmChnlTxPwLevel[2]);
			RT_TRACE(COMP_INIT, "priv->EEPROMRfCCCKChnl1TxPwLevel[0] = 0x%x\n", priv->EEPROMRfCCCKChnl1TxPwLevel[0]);
			RT_TRACE(COMP_INIT, "priv->EEPROMRfCCCKChnl1TxPwLevel[1] = 0x%x\n", priv->EEPROMRfCCCKChnl1TxPwLevel[1]);
			RT_TRACE(COMP_INIT, "priv->EEPROMRfCCCKChnl1TxPwLevel[2] = 0x%x\n", priv->EEPROMRfCCCKChnl1TxPwLevel[2]);
			RT_TRACE(COMP_INIT, "priv->EEPROMRfCOfdmChnlTxPwLevel[0] = 0x%x\n", priv->EEPROMRfCOfdmChnlTxPwLevel[0]);
			RT_TRACE(COMP_INIT, "priv->EEPROMRfCOfdmChnlTxPwLevel[1] = 0x%x\n", priv->EEPROMRfCOfdmChnlTxPwLevel[1]);
			RT_TRACE(COMP_INIT, "priv->EEPROMRfCOfdmChnlTxPwLevel[2] = 0x%x\n", priv->EEPROMRfCOfdmChnlTxPwLevel[2]);
#endif

		}
		//
		// Update HAL variables.
		//
		if(priv->epromtype == EPROM_93c46)
		{
			for(i=0; i<14; i++)
			{
				priv->TxPowerLevelCCK[i] = priv->EEPROMTxPowerLevelCCK[i];
				priv->TxPowerLevelOFDM24G[i] = priv->EEPROMTxPowerLevelOFDM24G[i];
			}
			priv->LegacyHTTxPowerDiff = priv->EEPROMLegacyHTTxPowerDiff;
		// Antenna B gain offset to antenna A, bit0~3
			priv->AntennaTxPwDiff[0] = (priv->EEPROMAntPwDiff & 0xf);
		// Antenna C gain offset to antenna A, bit4~7
			priv->AntennaTxPwDiff[1] = ((priv->EEPROMAntPwDiff & 0xf0)>>4);
		// Antenna D gain offset to antenna A, bit8~11
			priv->AntennaTxPwDiff[2] = ((priv->EEPROMAntPwDiff & 0xf00)>>8);
		// CrystalCap, bit12~15
			priv->CrystalCap = priv->EEPROMCrystalCap;
		// ThermalMeter, bit0~3 for RFIC1, bit4~7 for RFIC2
			priv->ThermalMeter[0] = (priv->EEPROMThermalMeter & 0xf);
			priv->ThermalMeter[1] = ((priv->EEPROMThermalMeter & 0xf0)>>4);
		}
		else if(priv->epromtype == EPROM_93c56)
		{
			//char	cck_pwr_diff_a=0, cck_pwr_diff_c=0;

			//cck_pwr_diff_a = pHalData->EEPROMRfACCKChnl7TxPwLevel - pHalData->EEPROMRfAOfdmChnlTxPwLevel[1];
			//cck_pwr_diff_c = pHalData->EEPROMRfCCCKChnl7TxPwLevel - pHalData->EEPROMRfCOfdmChnlTxPwLevel[1];
			for(i=0; i<3; i++)	// channel 1~3 use the same Tx Power Level.
			{
				priv->TxPowerLevelCCK_A[i]  = priv->EEPROMRfACCKChnl1TxPwLevel[0];
				priv->TxPowerLevelOFDM24G_A[i] = priv->EEPROMRfAOfdmChnlTxPwLevel[0];
				priv->TxPowerLevelCCK_C[i] =  priv->EEPROMRfCCCKChnl1TxPwLevel[0];
				priv->TxPowerLevelOFDM24G_C[i] = priv->EEPROMRfCOfdmChnlTxPwLevel[0];
			}
			for(i=3; i<9; i++)	// channel 4~9 use the same Tx Power Level
			{
				priv->TxPowerLevelCCK_A[i]  = priv->EEPROMRfACCKChnl1TxPwLevel[1];
				priv->TxPowerLevelOFDM24G_A[i] = priv->EEPROMRfAOfdmChnlTxPwLevel[1];
				priv->TxPowerLevelCCK_C[i] =  priv->EEPROMRfCCCKChnl1TxPwLevel[1];
				priv->TxPowerLevelOFDM24G_C[i] = priv->EEPROMRfCOfdmChnlTxPwLevel[1];
			}
			for(i=9; i<14; i++)	// channel 10~14 use the same Tx Power Level
			{
				priv->TxPowerLevelCCK_A[i]  = priv->EEPROMRfACCKChnl1TxPwLevel[2];
				priv->TxPowerLevelOFDM24G_A[i] = priv->EEPROMRfAOfdmChnlTxPwLevel[2];
				priv->TxPowerLevelCCK_C[i] =  priv->EEPROMRfCCCKChnl1TxPwLevel[2];
				priv->TxPowerLevelOFDM24G_C[i] = priv->EEPROMRfCOfdmChnlTxPwLevel[2];
			}
			for(i=0; i<14; i++)
				RT_TRACE(COMP_INIT, "priv->TxPowerLevelCCK_A[%d] = 0x%x\n", i, priv->TxPowerLevelCCK_A[i]);
			for(i=0; i<14; i++)
				RT_TRACE(COMP_INIT,"priv->TxPowerLevelOFDM24G_A[%d] = 0x%x\n", i, priv->TxPowerLevelOFDM24G_A[i]);
			for(i=0; i<14; i++)
				RT_TRACE(COMP_INIT, "priv->TxPowerLevelCCK_C[%d] = 0x%x\n", i, priv->TxPowerLevelCCK_C[i]);
			for(i=0; i<14; i++)
				RT_TRACE(COMP_INIT, "priv->TxPowerLevelOFDM24G_C[%d] = 0x%x\n", i, priv->TxPowerLevelOFDM24G_C[i]);
			priv->LegacyHTTxPowerDiff = priv->EEPROMLegacyHTTxPowerDiff;
			priv->AntennaTxPwDiff[0] = 0;
			priv->AntennaTxPwDiff[1] = 0;
			priv->AntennaTxPwDiff[2] = 0;
			priv->CrystalCap = priv->EEPROMCrystalCap;
			// ThermalMeter, bit0~3 for RFIC1, bit4~7 for RFIC2
			priv->ThermalMeter[0] = (priv->EEPROMThermalMeter & 0xf);
			priv->ThermalMeter[1] = ((priv->EEPROMThermalMeter & 0xf0)>>4);
		}
	}

	if(priv->rf_type == RF_1T2R)
	{
		RT_TRACE(COMP_INIT, "\n1T2R config\n");
	}
	else if (priv->rf_type == RF_2T4R)
	{
		RT_TRACE(COMP_INIT, "\n2T4R config\n");
	}

	// 2008/01/16 MH We can only know RF type in the function. So we have to init
	// DIG RATR table again.
	init_rate_adaptive(dev);

	//1 Make a copy for following variables and we can change them if we want

	priv->rf_chip= RF_8256;

	if(priv->RegChannelPlan == 0xf)
	{
		priv->ChannelPlan = priv->eeprom_ChannelPlan;
	}
	else
	{
		priv->ChannelPlan = priv->RegChannelPlan;
	}

	//
	//  Used PID and DID to Set CustomerID
	//
	if( priv->eeprom_vid == 0x1186 &&  priv->eeprom_did == 0x3304 )
	{
		priv->CustomerID =  RT_CID_DLINK;
	}

	switch(priv->eeprom_CustomerID)
	{
		case EEPROM_CID_DEFAULT:
			priv->CustomerID = RT_CID_DEFAULT;
			break;
		case EEPROM_CID_CAMEO:
			priv->CustomerID = RT_CID_819x_CAMEO;
			break;
		case  EEPROM_CID_RUNTOP:
			priv->CustomerID = RT_CID_819x_RUNTOP;
			break;
		case EEPROM_CID_NetCore:
			priv->CustomerID = RT_CID_819x_Netcore;
			break;
		case EEPROM_CID_TOSHIBA:        // Merge by Jacken, 2008/01/31
			priv->CustomerID = RT_CID_TOSHIBA;
			if(priv->eeprom_ChannelPlan&0x80)
				priv->ChannelPlan = priv->eeprom_ChannelPlan&0x7f;
			else
				priv->ChannelPlan = 0x0;
			RT_TRACE(COMP_INIT, "Toshiba ChannelPlan = 0x%x\n",
				priv->ChannelPlan);
			break;
		case EEPROM_CID_Nettronix:
			priv->ScanDelay = 100;	//cosa add for scan
			priv->CustomerID = RT_CID_Nettronix;
			break;
		case EEPROM_CID_Pronet:
			priv->CustomerID = RT_CID_PRONET;
			break;
		case EEPROM_CID_DLINK:
			priv->CustomerID = RT_CID_DLINK;
			break;

		case EEPROM_CID_WHQL:
			//Adapter->bInHctTest = TRUE;//do not supported

			//priv->bSupportTurboMode = FALSE;
			//priv->bAutoTurboBy8186 = FALSE;

			//pMgntInfo->PowerSaveControl.bInactivePs = FALSE;
			//pMgntInfo->PowerSaveControl.bIPSModeBackup = FALSE;
			//pMgntInfo->PowerSaveControl.bLeisurePs = FALSE;

			break;
		default:
			// value from RegCustomerID
			break;
	}

	//Avoid the channel plan array overflow, by Bruce, 2007-08-27.
	if(priv->ChannelPlan > CHANNEL_PLAN_LEN - 1)
		priv->ChannelPlan = 0; //FCC

	switch(priv->CustomerID)
	{
		case RT_CID_DEFAULT:
		#ifdef RTL8190P
			priv->LedStrategy = HW_LED;
		#else
			#ifdef RTL8192E
			priv->LedStrategy = SW_LED_MODE1;
			#endif
		#endif
			break;

		case RT_CID_819x_CAMEO:
			priv->LedStrategy = SW_LED_MODE2;
			break;

		case RT_CID_819x_RUNTOP:
			priv->LedStrategy = SW_LED_MODE3;
			break;

		case RT_CID_819x_Netcore:
			priv->LedStrategy = SW_LED_MODE4;
			break;

		case RT_CID_Nettronix:
			priv->LedStrategy = SW_LED_MODE5;
			break;

		case RT_CID_PRONET:
			priv->LedStrategy = SW_LED_MODE6;
			break;

		case RT_CID_TOSHIBA:   //Modify by Jacken 2008/01/31
			// Do nothing.
			//break;

		default:
		#ifdef RTL8190P
			priv->LedStrategy = HW_LED;
		#else
			#ifdef RTL8192E
			priv->LedStrategy = SW_LED_MODE1;
			#endif
		#endif
			break;
	}
/*
	//2008.06.03, for WOL
	if( priv->eeprom_vid == 0x1186 &&  priv->eeprom_did == 0x3304)
		priv->ieee80211->bSupportRemoteWakeUp = TRUE;
	else
		priv->ieee80211->bSupportRemoteWakeUp = FALSE;
*/
	RT_TRACE(COMP_INIT, "RegChannelPlan(%d)\n", priv->RegChannelPlan);
	RT_TRACE(COMP_INIT, "ChannelPlan = %d \n", priv->ChannelPlan);
	RT_TRACE(COMP_INIT, "LedStrategy = %d \n", priv->LedStrategy);
	RT_TRACE(COMP_TRACE, "<==== ReadAdapterInfo\n");

	return ;
}