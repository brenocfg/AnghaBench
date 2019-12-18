#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u32 ;
struct r8192_priv {scalar_t__ bTXPowerDataReadFromEEPORM; size_t** RfTxPwrLevelCck; scalar_t__ rf_type; size_t** RfTxPwrLevelOfdm1T; size_t** RfTxPwrLevelOfdm2T; int EEPROMVersion; scalar_t__ CurrentChannelBW; size_t** TxPwrHt20Diff; int TxPwrbandEdgeFlag; size_t** TxPwrbandEdgeHt40; size_t** TxPwrbandEdgeHt20; size_t* AntennaTxPwDiff; size_t LegacyHTTxPowerDiff; size_t CurrentCckTxPwrIdx; size_t CurrentOfdm24GTxPwrIdx; int rf_chip; int /*<<< orphan*/  CcxCellPwr; TYPE_2__* ieee80211; scalar_t__ bWithCcxCellPwr; } ;
struct net_device {int dummy; } ;
typedef  int s8 ;
struct TYPE_3__ {size_t channel; } ;
struct TYPE_4__ {scalar_t__ iw_mode; TYPE_1__ current_network; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_TXAGC ; 
 scalar_t__ EEPROM_Default_TxPower ; 
 scalar_t__ FALSE ; 
 scalar_t__ HT_CHANNEL_WIDTH_20 ; 
 scalar_t__ HT_CHANNEL_WIDTH_20_40 ; 
 scalar_t__ IW_MODE_INFRA ; 
 int /*<<< orphan*/  PHY_RF6052SetCckTxPower (struct net_device*,size_t) ; 
 int /*<<< orphan*/  PHY_RF6052SetOFDMTxPower (struct net_device*,size_t) ; 
 scalar_t__ RF_1T1R ; 
 scalar_t__ RF_1T2R ; 
 scalar_t__ RF_2T2R ; 
#define  RF_6052 131 
#define  RF_8225 130 
#define  RF_8256 129 
#define  RF_8258 128 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WIRELESS_MODE_B ; 
 int /*<<< orphan*/  WIRELESS_MODE_G ; 
 int /*<<< orphan*/  WIRELESS_MODE_N_24G ; 
 int bXBTxAGC ; 
 int bXCTxAGC ; 
 int bXDTxAGC ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 size_t phy_DbmToTxPwrIdx (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rFPGA0_TxGainStage ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int /*<<< orphan*/ ,int,int) ; 

void PHY_SetTxPowerLevel8192S(struct net_device* dev, u8	channel)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	//HAL_DATA_TYPE		*pHalData = GET_HAL_DATA(dev);
	u8	powerlevel = (u8)EEPROM_Default_TxPower, powerlevelOFDM24G = 0x10;
	s8 	ant_pwr_diff = 0;
	u32	u4RegValue;
	u8	index = (channel -1);
	// 2009/01/22 MH Add for new EEPROM format from SD3
	u8	pwrdiff[2] = {0};
	u8	ht20pwr[2] = {0}, ht40pwr[2] = {0};
	u8	rfpath = 0, rfpathnum = 2;

	if(priv->bTXPowerDataReadFromEEPORM == FALSE)
		return;

	//
	// Read predefined TX power index in EEPROM
	//
//	if(priv->epromtype == EPROM_93c46)
	{
		//
		// Mainly we use RF-A Tx Power to write the Tx Power registers, but the RF-B Tx
		// Power must be calculated by the antenna diff.
		// So we have to rewrite Antenna gain offset register here.
		// Please refer to BB register 0x80c
		// 1. For CCK.
		// 2. For OFDM 1T or 2T
		//

		// 1. CCK
		powerlevel = priv->RfTxPwrLevelCck[0][index];

		if (priv->rf_type == RF_1T2R || priv->rf_type == RF_1T1R)
		{
		// Read HT 40 OFDM TX power
		powerlevelOFDM24G = priv->RfTxPwrLevelOfdm1T[0][index];
		// RF B HT OFDM pwr-RFA HT OFDM pwr
		// Only one RF we need not to decide B <-> A pwr diff

		// Legacy<->HT pwr diff, we only care about path A.

		// We only assume 1T as RF path A
		rfpathnum = 1;
		ht20pwr[0] = ht40pwr[0] = priv->RfTxPwrLevelOfdm1T[0][index];
		}
		else if (priv->rf_type == RF_2T2R)
		{
		// Read HT 40 OFDM TX power
		powerlevelOFDM24G = priv->RfTxPwrLevelOfdm2T[0][index];
			// RF B HT OFDM pwr-RFA HT OFDM pwr
		ant_pwr_diff = 	priv->RfTxPwrLevelOfdm2T[1][index] -
						priv->RfTxPwrLevelOfdm2T[0][index];
			// RF B (HT OFDM pwr+legacy-ht-diff) -(RFA HT OFDM pwr+legacy-ht-diff)
		// We can not handle Path B&A HT/Legacy pwr diff for 92S now.

		//RTPRINT(FPHY, PHY_TXPWR, ("CH-%d HT40 A/B Pwr index = %x/%x(%d/%d)\n",
		//channel, priv->RfTxPwrLevelOfdm2T[0][index],
		//priv->RfTxPwrLevelOfdm2T[1][index],
		//priv->RfTxPwrLevelOfdm2T[0][index],
		//priv->RfTxPwrLevelOfdm2T[1][index]));

		ht20pwr[0] = ht40pwr[0] = priv->RfTxPwrLevelOfdm2T[0][index];
		ht20pwr[1] = ht40pwr[1] = priv->RfTxPwrLevelOfdm2T[1][index];
	}

	//
	// 2009/01/21 MH Support new EEPROM format from SD3 requirement
	// 2009/02/10 Cosa, Here is only for reg B/C/D to A gain diff.
	//
	if (priv->EEPROMVersion == 2)	// Defined by SD1 Jong
	{
		if (priv->CurrentChannelBW == HT_CHANNEL_WIDTH_20)
		{
			for (rfpath = 0; rfpath < rfpathnum; rfpath++)
			{
				// HT 20<->40 pwr diff
				pwrdiff[rfpath] = priv->TxPwrHt20Diff[rfpath][index];

				// Calculate Antenna pwr diff
				if (pwrdiff[rfpath] < 8)	// 0~+7
				{
					ht20pwr[rfpath] += pwrdiff[rfpath];
				}
				else				// index8-15=-8~-1
				{
					ht20pwr[rfpath] -= (15-pwrdiff[rfpath]);
				}
			}

			// RF B HT OFDM pwr-RFA HT OFDM pwr
			if (priv->rf_type == RF_2T2R)
				ant_pwr_diff = ht20pwr[1] - ht20pwr[0];

			//RTPRINT(FPHY, PHY_TXPWR,
			//("HT20 to HT40 pwrdiff[A/B]=%d/%d, ant_pwr_diff=%d(B-A=%d-%d)\n",
			//pwrdiff[0], pwrdiff[1], ant_pwr_diff, ht20pwr[1], ht20pwr[0]));
		}

		// Band Edge scheme is enabled for FCC mode
		if (priv->TxPwrbandEdgeFlag == 1/* && pHalData->ChannelPlan == 0*/)
		{
			for (rfpath = 0; rfpath < rfpathnum; rfpath++)
			{
				pwrdiff[rfpath] = 0;
				if (priv->CurrentChannelBW == HT_CHANNEL_WIDTH_20_40)
				{
					if (channel <= 3)
						pwrdiff[rfpath] = priv->TxPwrbandEdgeHt40[rfpath][0];
					else if (channel >= 9)
						pwrdiff[rfpath] = priv->TxPwrbandEdgeHt40[rfpath][1];
					else
						pwrdiff[rfpath] = 0;

					ht40pwr[rfpath] -= pwrdiff[rfpath];
				}
				else if (priv->CurrentChannelBW == HT_CHANNEL_WIDTH_20)
				{
					if (channel == 1)
						pwrdiff[rfpath] = priv->TxPwrbandEdgeHt20[rfpath][0];
					else if (channel >= 11)
						pwrdiff[rfpath] = priv->TxPwrbandEdgeHt20[rfpath][1];
					else
						pwrdiff[rfpath] = 0;

					ht20pwr[rfpath] -= pwrdiff[rfpath];
				}
			}

			if (priv->rf_type == RF_2T2R)
			{
				// HT 20/40 must decide if they need to minus  BD pwr offset
				if (priv->CurrentChannelBW == HT_CHANNEL_WIDTH_20_40)
					ant_pwr_diff = ht40pwr[1] - ht40pwr[0];
				else
					ant_pwr_diff = ht20pwr[1] - ht20pwr[0];
			}
			if (priv->CurrentChannelBW == HT_CHANNEL_WIDTH_20)
			{
				if (channel <= 1 || channel >= 11)
				{
					//RTPRINT(FPHY, PHY_TXPWR,
					//("HT20 Band-edge pwrdiff[A/B]=%d/%d, ant_pwr_diff=%d(B-A=%d-%d)\n",
					//pwrdiff[0], pwrdiff[1], ant_pwr_diff, ht20pwr[1], ht20pwr[0]));
				}
			}
			else
			{
				if (channel <= 3 || channel >= 9)
				{
					//RTPRINT(FPHY, PHY_TXPWR,
					//("HT40 Band-edge pwrdiff[A/B]=%d/%d, ant_pwr_diff=%d(B-A=%d-%d)\n",
					//pwrdiff[0], pwrdiff[1], ant_pwr_diff, ht40pwr[1], ht40pwr[0]));
				}
			}
		}
		}

	//Cosa added for protection, the reg rFPGA0_TxGainStage
	// range is from 7~-8, index = 0x0~0xf
	if(ant_pwr_diff > 7)
		ant_pwr_diff = 7;
	if(ant_pwr_diff < -8)
		ant_pwr_diff = -8;

		//RTPRINT(FPHY, PHY_TXPWR,
		//("CCK/HT Power index = %x/%x(%d/%d), ant_pwr_diff=%d\n",
		//powerlevel, powerlevelOFDM24G, powerlevel, powerlevelOFDM24G, ant_pwr_diff));

		ant_pwr_diff &= 0xf;

		// Antenna TX power difference
		priv->AntennaTxPwDiff[2] = 0;// RF-D, don't care
		priv->AntennaTxPwDiff[1] = 0;// RF-C, don't care
		priv->AntennaTxPwDiff[0] = (u8)(ant_pwr_diff);		// RF-B

		// Antenna gain offset from B/C/D to A
		u4RegValue = (	priv->AntennaTxPwDiff[2]<<8 |
						priv->AntennaTxPwDiff[1]<<4 |
						priv->AntennaTxPwDiff[0]	);

		// Notify Tx power difference for B/C/D to A!!!
		rtl8192_setBBreg(dev, rFPGA0_TxGainStage, (bXBTxAGC|bXCTxAGC|bXDTxAGC), u4RegValue);
	}

	//
	// CCX 2 S31, AP control of client transmit power:
	// 1. We shall not exceed Cell Power Limit as possible as we can.
	// 2. Tolerance is +/- 5dB.
	// 3. 802.11h Power Contraint takes higher precedence over CCX Cell Power Limit.
	//
	// TODO:
	// 1. 802.11h power contraint
	//
	// 071011, by rcnjko.
	//
#ifdef TODO //WB, 11h has not implemented now.
	if(	priv->ieee80211->iw_mode != IW_MODE_INFRA && priv->bWithCcxCellPwr &&
		channel == priv->ieee80211->current_network.channel)// & priv->ieee80211->mAssoc )
	{
		u8	CckCellPwrIdx = phy_DbmToTxPwrIdx(dev, WIRELESS_MODE_B, priv->CcxCellPwr);
		u8	LegacyOfdmCellPwrIdx = phy_DbmToTxPwrIdx(dev, WIRELESS_MODE_G, priv->CcxCellPwr);
		u8	OfdmCellPwrIdx = phy_DbmToTxPwrIdx(dev, WIRELESS_MODE_N_24G, priv->CcxCellPwr);

		RT_TRACE(COMP_TXAGC,
		("CCX Cell Limit: %d dbm => CCK Tx power index : %d, Legacy OFDM Tx power index : %d, OFDM Tx power index: %d\n",
		priv->CcxCellPwr, CckCellPwrIdx, LegacyOfdmCellPwrIdx, OfdmCellPwrIdx));
		RT_TRACE(COMP_TXAGC,
		("EEPROM channel(%d) => CCK Tx power index: %d, Legacy OFDM Tx power index : %d, OFDM Tx power index: %d\n",
		channel, powerlevel, powerlevelOFDM24G + priv->LegacyHTTxPowerDiff, powerlevelOFDM24G));

		// CCK
		if(powerlevel > CckCellPwrIdx)
			powerlevel = CckCellPwrIdx;
		// Legacy OFDM, HT OFDM
		if(powerlevelOFDM24G + priv->LegacyHTTxPowerDiff > LegacyOfdmCellPwrIdx)
		{
			if((OfdmCellPwrIdx - priv->LegacyHTTxPowerDiff) > 0)
			{
				powerlevelOFDM24G = OfdmCellPwrIdx - priv->LegacyHTTxPowerDiff;
			}
			else
			{
				powerlevelOFDM24G = 0;
			}
		}

		RT_TRACE(COMP_TXAGC,
		("Altered CCK Tx power index : %d, Legacy OFDM Tx power index: %d, OFDM Tx power index: %d\n",
		powerlevel, powerlevelOFDM24G + priv->LegacyHTTxPowerDiff, powerlevelOFDM24G));
	}
#endif

	priv->CurrentCckTxPwrIdx = powerlevel;
	priv->CurrentOfdm24GTxPwrIdx = powerlevelOFDM24G;

	switch(priv->rf_chip)
	{
		case RF_8225:
			//PHY_SetRF8225CckTxPower(dev, powerlevel);
			//PHY_SetRF8225OfdmTxPower(dev, powerlevelOFDM24G);
		break;

		case RF_8256:
			break;

		case RF_6052:
			PHY_RF6052SetCckTxPower(dev, powerlevel);
			PHY_RF6052SetOFDMTxPower(dev, powerlevelOFDM24G);
			break;

		case RF_8258:
			break;
		default:
			break;
	}

}