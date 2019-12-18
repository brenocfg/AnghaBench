#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct r8192_priv {int rf_type; int MinSpaceCfg; int /*<<< orphan*/  bInHctTest; TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int mode; } ;

/* Variables and functions */
 scalar_t__ ACK_TIMEOUT ; 
 scalar_t__ AGGLEN_LMT_H ; 
 scalar_t__ AGGLEN_LMT_L ; 
 scalar_t__ AMPDU_MIN_SPACE ; 
 scalar_t__ ARFR0 ; 
 scalar_t__ BW_OPMODE ; 
 int BW_OPMODE_20MHZ ; 
 int BW_OPMODE_5G ; 
 scalar_t__ CFEND_TH ; 
 int /*<<< orphan*/  COMP_INIT ; 
 scalar_t__ DARFRC ; 
 scalar_t__ INIRTSMCS_SEL ; 
 int MAX_MSS_DENSITY_1T ; 
 int MAX_MSS_DENSITY_2T ; 
 scalar_t__ MLT ; 
 scalar_t__ NAV_PROT_LEN ; 
 scalar_t__ RARFRC ; 
 int RATE_ALL_CCK ; 
 int RATE_ALL_OFDM_1SS ; 
 int RATE_ALL_OFDM_2SS ; 
 int RATE_ALL_OFDM_AG ; 
#define  RF_1T1R 137 
#define  RF_1T2R 136 
#define  RF_2T2R 135 
#define  RF_2T2R_GREEN 134 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ SIFS_CCK ; 
 scalar_t__ SIFS_OFDM ; 
 scalar_t__ TXOP_STALL_CTRL ; 
#define  WIRELESS_MODE_A 133 
#define  WIRELESS_MODE_AUTO 132 
#define  WIRELESS_MODE_B 131 
#define  WIRELESS_MODE_G 130 
#define  WIRELESS_MODE_N_24G 129 
#define  WIRELESS_MODE_N_5G 128 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int read_nic_byte (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  write_nic_dword (struct net_device*,scalar_t__,int) ; 
 int /*<<< orphan*/  write_nic_word (struct net_device*,scalar_t__,int) ; 

void rtl8192SU_HwConfigureRTL8192SUsb(struct net_device *dev)
{

	struct r8192_priv *priv = ieee80211_priv(dev);
	u8			regBwOpMode = 0;
	u32			regRATR = 0, regRRSR = 0;
	u8			regTmp = 0;
	u32 			i = 0;

	//1 This part need to modified according to the rate set we filtered!!
	//
	// Set RRSR, RATR, and BW_OPMODE registers
	//
	switch(priv->ieee80211->mode)
	{
	case WIRELESS_MODE_B:
		regBwOpMode = BW_OPMODE_20MHZ;
		regRATR = RATE_ALL_CCK;
		regRRSR = RATE_ALL_CCK;
		break;
	case WIRELESS_MODE_A:
		regBwOpMode = BW_OPMODE_5G |BW_OPMODE_20MHZ;
		regRATR = RATE_ALL_OFDM_AG;
		regRRSR = RATE_ALL_OFDM_AG;
		break;
	case WIRELESS_MODE_G:
		regBwOpMode = BW_OPMODE_20MHZ;
		regRATR = RATE_ALL_CCK | RATE_ALL_OFDM_AG;
		regRRSR = RATE_ALL_CCK | RATE_ALL_OFDM_AG;
		break;
	case WIRELESS_MODE_AUTO:
		if (priv->bInHctTest)
		{
		    regBwOpMode = BW_OPMODE_20MHZ;
		    regRATR = RATE_ALL_CCK | RATE_ALL_OFDM_AG;
		    regRRSR = RATE_ALL_CCK | RATE_ALL_OFDM_AG;
		}
		else
		{
		    regBwOpMode = BW_OPMODE_20MHZ;
		    regRATR = RATE_ALL_CCK | RATE_ALL_OFDM_AG | RATE_ALL_OFDM_1SS | RATE_ALL_OFDM_2SS;
		    regRRSR = RATE_ALL_CCK | RATE_ALL_OFDM_AG;
		}
		break;
	case WIRELESS_MODE_N_24G:
		// It support CCK rate by default.
		// CCK rate will be filtered out only when associated AP does not support it.
		regBwOpMode = BW_OPMODE_20MHZ;
			regRATR = RATE_ALL_CCK | RATE_ALL_OFDM_AG | RATE_ALL_OFDM_1SS | RATE_ALL_OFDM_2SS;
			regRRSR = RATE_ALL_CCK | RATE_ALL_OFDM_AG;
		break;
	case WIRELESS_MODE_N_5G:
		regBwOpMode = BW_OPMODE_5G;
		regRATR = RATE_ALL_OFDM_AG | RATE_ALL_OFDM_1SS | RATE_ALL_OFDM_2SS;
		regRRSR = RATE_ALL_OFDM_AG;
		break;
	}

	//
	// <Roger_Notes> We disable CCK response rate until FIB CCK rate IC's back.
	// 2008.09.23.
	//
	regTmp = read_nic_byte(dev, INIRTSMCS_SEL);
	regRRSR = ((regRRSR & 0x000fffff)<<8) | regTmp;

	//
	// Update SIFS timing.
	//
	//priv->SifsTime = 0x0e0e0a0a;
	//Adapter->HalFunc.SetHwRegHandler( Adapter, HW_VAR_SIFS,  (pu1Byte)&pHalData->SifsTime);
	{	u8 val[4] = {0x0e, 0x0e, 0x0a, 0x0a};
		// SIFS for CCK Data ACK
		write_nic_byte(dev, SIFS_CCK, val[0]);
		// SIFS for CCK consecutive tx like CTS data!
		write_nic_byte(dev, SIFS_CCK+1, val[1]);

		// SIFS for OFDM Data ACK
		write_nic_byte(dev, SIFS_OFDM, val[2]);
		// SIFS for OFDM consecutive tx like CTS data!
		write_nic_byte(dev, SIFS_OFDM+1, val[3]);
	}

	write_nic_dword(dev, INIRTSMCS_SEL, regRRSR);
	write_nic_byte(dev, BW_OPMODE, regBwOpMode);

	//
	// Suggested by SD1 Alex, 2008-06-14.
	//
	//PlatformEFIOWrite1Byte(Adapter, TXOP_STALL_CTRL, 0x80);//NAV to protect all TXOP.

	//
	// Set Data Auto Rate Fallback Retry Count register.
	//
	write_nic_dword(dev, DARFRC, 0x02010000);
	write_nic_dword(dev, DARFRC+4, 0x06050403);
	write_nic_dword(dev, RARFRC, 0x02010000);
	write_nic_dword(dev, RARFRC+4, 0x06050403);

	// Set Data Auto Rate Fallback Reg. Added by Roger, 2008.09.22.
	for (i = 0; i < 8; i++)
		write_nic_dword(dev, ARFR0+i*4, 0x1f0ffff0);

	//
	// Aggregation length limit. Revised by Roger. 2008.09.22.
	//
	write_nic_byte(dev, AGGLEN_LMT_H, 0x0f);	// Set AMPDU length to 12Kbytes for ShortGI case.
	write_nic_dword(dev, AGGLEN_LMT_L, 0xddd77442); // Long GI
	write_nic_dword(dev, AGGLEN_LMT_L+4, 0xfffdd772);

	// Set NAV protection length
	write_nic_word(dev, NAV_PROT_LEN, 0x0080);

	// Set TXOP stall control for several queue/HI/BCN/MGT/
	write_nic_byte(dev, TXOP_STALL_CTRL, 0x00); // NAV Protect next packet.

	// Set MSDU lifetime.
	write_nic_byte(dev, MLT, 0x8f);

	// Set CCK/OFDM SIFS
	write_nic_word(dev, SIFS_CCK, 0x0a0a); // CCK SIFS shall always be 10us.
	write_nic_word(dev, SIFS_OFDM, 0x0e0e);

	write_nic_byte(dev, ACK_TIMEOUT, 0x40);

	// CF-END Threshold
	write_nic_byte(dev, CFEND_TH, 0xFF);

	//
	// For Min Spacing configuration.
	//
	switch(priv->rf_type)
	{
		case RF_1T2R:
		case RF_1T1R:
			RT_TRACE(COMP_INIT, "Initializeadapter: RF_Type%s\n", (priv->rf_type==RF_1T1R? "(1T1R)":"(1T2R)"));
			priv->MinSpaceCfg = (MAX_MSS_DENSITY_1T<<3);
			break;
		case RF_2T2R:
		case RF_2T2R_GREEN:
			RT_TRACE(COMP_INIT, "Initializeadapter:RF_Type(2T2R)\n");
			priv->MinSpaceCfg = (MAX_MSS_DENSITY_2T<<3);
			break;
	}
	write_nic_byte(dev, AMPDU_MIN_SPACE, priv->MinSpaceCfg);

	//LZM 090219
	//
	// For Min Spacing configuration.
	//
	//priv->MinSpaceCfg = 0x00;
	//rtl8192SU_SetHwRegAmpduMinSpace(dev, priv->MinSpaceCfg);
}