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
struct r8192_priv {scalar_t__ card_8192_version; scalar_t__ rf_type; int* AntennaTxPwDiff; int CrystalCap; } ;
struct net_device {int dummy; } ;
typedef  scalar_t__ RT_STATUS ;
typedef  int /*<<< orphan*/  RF90_RADIO_PATH_E ;
typedef  scalar_t__ HW90_BLOCK_E ;

/* Variables and functions */
 int /*<<< orphan*/  BB_GLOBAL_RESET ; 
 scalar_t__ BB_GLOBAL_RESET_BIT ; 
 int /*<<< orphan*/  BaseBand_Config_AGC_TAB ; 
 int /*<<< orphan*/  BaseBand_Config_PHY_REG ; 
 int COMP_ERR ; 
 int COMP_PHY ; 
 int /*<<< orphan*/  CPU_GEN ; 
 int CPU_GEN_BB_RST ; 
 scalar_t__ HW90_BLOCK_PHY0 ; 
 scalar_t__ HW90_BLOCK_PHY1 ; 
 scalar_t__ RF_2T4R ; 
 scalar_t__ RT_STATUS_SUCCESS ; 
 int /*<<< orphan*/  RT_TRACE (int,char*,scalar_t__) ; 
 scalar_t__ VERSION_8190_BD ; 
 int bCCKEn ; 
 int bOFDMEn ; 
 int bXBTxAGC ; 
 int bXCTxAGC ; 
 int bXDTxAGC ; 
 int bXtalCap01 ; 
 int bXtalCap23 ; 
 int bXtalCap92x ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rFPGA0_AnalogParameter1 ; 
 int /*<<< orphan*/  rFPGA0_AnalogParameter2 ; 
 int /*<<< orphan*/  rFPGA0_RFMOD ; 
 int /*<<< orphan*/  rFPGA0_TxGainStage ; 
 scalar_t__ read_nic_byte (struct net_device*,int /*<<< orphan*/ ) ; 
 int read_nic_dword (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8192_phyConfigBB (struct net_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ rtl8192_phy_checkBBAndRF (struct net_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static RT_STATUS rtl8192_BB_Config_ParaFile(struct net_device* dev)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	RT_STATUS rtStatus = RT_STATUS_SUCCESS;
	u8 bRegValue = 0, eCheckItem = 0;
	u32 dwRegValue = 0;
	/**************************************
	//<1>Initialize BaseBand
	**************************************/

	/*--set BB Global Reset--*/
	bRegValue = read_nic_byte(dev, BB_GLOBAL_RESET);
	write_nic_byte(dev, BB_GLOBAL_RESET,(bRegValue|BB_GLOBAL_RESET_BIT));

	/*---set BB reset Active---*/
	dwRegValue = read_nic_dword(dev, CPU_GEN);
	write_nic_dword(dev, CPU_GEN, (dwRegValue&(~CPU_GEN_BB_RST)));

	/*----Ckeck FPGAPHY0 and PHY1 board is OK----*/
	// TODO: this function should be removed on ASIC , Emily 2007.2.2
	for(eCheckItem=(HW90_BLOCK_E)HW90_BLOCK_PHY0; eCheckItem<=HW90_BLOCK_PHY1; eCheckItem++)
	{
		rtStatus  = rtl8192_phy_checkBBAndRF(dev, (HW90_BLOCK_E)eCheckItem, (RF90_RADIO_PATH_E)0); //don't care RF path
		if(rtStatus != RT_STATUS_SUCCESS)
		{
			RT_TRACE((COMP_ERR | COMP_PHY), "PHY_RF8256_Config():Check PHY%d Fail!!\n", eCheckItem-1);
			return rtStatus;
		}
	}
	/*---- Set CCK and OFDM Block "OFF"----*/
	rtl8192_setBBreg(dev, rFPGA0_RFMOD, bCCKEn|bOFDMEn, 0x0);
	/*----BB Register Initilazation----*/
	//==m==>Set PHY REG From Header<==m==
	rtl8192_phyConfigBB(dev, BaseBand_Config_PHY_REG);

	/*----Set BB reset de-Active----*/
	dwRegValue = read_nic_dword(dev, CPU_GEN);
	write_nic_dword(dev, CPU_GEN, (dwRegValue|CPU_GEN_BB_RST));

 	/*----BB AGC table Initialization----*/
	//==m==>Set PHY REG From Header<==m==
	rtl8192_phyConfigBB(dev, BaseBand_Config_AGC_TAB);

	if (priv->card_8192_version  > VERSION_8190_BD)
	{
		if(priv->rf_type == RF_2T4R)
		{
		// Antenna gain offset from B/C/D to A
		dwRegValue = (  priv->AntennaTxPwDiff[2]<<8 |
						priv->AntennaTxPwDiff[1]<<4 |
						priv->AntennaTxPwDiff[0]);
		}
		else
			dwRegValue = 0x0;	//Antenna gain offset doesn't make sense in RF 1T2R.
		rtl8192_setBBreg(dev, rFPGA0_TxGainStage,
			(bXBTxAGC|bXCTxAGC|bXDTxAGC), dwRegValue);


		//XSTALLCap
#ifdef RTL8190P
	dwRegValue = priv->CrystalCap & 0x3;	// bit0~1 of crystal cap
	rtl8192_setBBreg(dev, rFPGA0_AnalogParameter1, bXtalCap01, dwRegValue);
	dwRegValue = ((priv->CrystalCap & 0xc)>>2);	// bit2~3 of crystal cap
	rtl8192_setBBreg(dev, rFPGA0_AnalogParameter2, bXtalCap23, dwRegValue);
#else
	#ifdef RTL8192E
		dwRegValue = priv->CrystalCap;
		rtl8192_setBBreg(dev, rFPGA0_AnalogParameter1, bXtalCap92x, dwRegValue);
	#endif
#endif

	}

	// Check if the CCK HighPower is turned ON.
	// This is used to calculate PWDB.
//	priv->bCckHighPower = (u8)(rtl8192_QueryBBReg(dev, rFPGA0_XA_HSSIParameter2, 0x200));
	return rtStatus;
}