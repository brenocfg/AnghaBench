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
struct r8192_priv {int CurrentChannelBW; int rf_chip; int nCur40MhzPrimeSC; void* SetBWModeInProgress; int /*<<< orphan*/  up; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ BW_OPMODE ; 
 int BW_OPMODE_20MHZ ; 
 int /*<<< orphan*/  COMP_DBG ; 
 int /*<<< orphan*/  COMP_SCAN ; 
 void* FALSE ; 
#define  HT_CHANNEL_WIDTH_20 134 
#define  HT_CHANNEL_WIDTH_20_40 133 
 int /*<<< orphan*/  PHY_RF6052SetBandwidth (struct net_device*,int) ; 
 int /*<<< orphan*/  PHY_SetRF8225Bandwidth (struct net_device*,int) ; 
#define  RF_6052 132 
#define  RF_8225 131 
#define  RF_8256 130 
#define  RF_8258 129 
#define  RF_PSEUDO_11N 128 
 scalar_t__ RRSR ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,...) ; 
 int bCCKSideBand ; 
 int bRFMOD ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  rCCK0_System ; 
 int /*<<< orphan*/  rFPGA0_AnalogParameter2 ; 
 int /*<<< orphan*/  rFPGA0_RFMOD ; 
 int /*<<< orphan*/  rFPGA1_RFMOD ; 
 int /*<<< orphan*/  rOFDM1_LSTF ; 
 int read_nic_byte (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  rtl8192_setBBreg (struct net_device*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  write_nic_byte (struct net_device*,scalar_t__,int) ; 

void SetBWModeCallback8192SUsbWorkItem(struct net_device *dev)
{
	struct r8192_priv 		*priv = ieee80211_priv(dev);
	u8	 			regBwOpMode;

	// Added it for 20/40 mhz switch time evaluation by guangan 070531
	//u32				NowL, NowH;
	//u8Byte				BeginTime, EndTime;
	u8			regRRSR_RSC;

	RT_TRACE(COMP_SCAN, "==>SetBWModeCallback8192SUsbWorkItem()  Switch to %s bandwidth\n", \
					priv->CurrentChannelBW == HT_CHANNEL_WIDTH_20?"20MHz":"40MHz");

	if(priv->rf_chip == RF_PSEUDO_11N)
	{
		priv->SetBWModeInProgress= FALSE;
		return;
	}

	if(!priv->up)
		return;

	// Added it for 20/40 mhz switch time evaluation by guangan 070531
	//NowL = read_nic_dword(dev, TSFR);
	//NowH = read_nic_dword(dev, TSFR+4);
	//BeginTime = ((u8Byte)NowH << 32) + NowL;

	//3<1>Set MAC register
	regBwOpMode = read_nic_byte(dev, BW_OPMODE);
	regRRSR_RSC = read_nic_byte(dev, RRSR+2);

	switch(priv->CurrentChannelBW)
	{
		case HT_CHANNEL_WIDTH_20:
			regBwOpMode |= BW_OPMODE_20MHZ;
		       // 2007/02/07 Mark by Emily becasue we have not verify whether this register works
			write_nic_byte(dev, BW_OPMODE, regBwOpMode);
			break;

		case HT_CHANNEL_WIDTH_20_40:
			regBwOpMode &= ~BW_OPMODE_20MHZ;
        		// 2007/02/07 Mark by Emily becasue we have not verify whether this register works
			write_nic_byte(dev, BW_OPMODE, regBwOpMode);
			regRRSR_RSC = (regRRSR_RSC&0x90) |(priv->nCur40MhzPrimeSC<<5);
			write_nic_byte(dev, RRSR+2, regRRSR_RSC);

			break;

		default:
			RT_TRACE(COMP_DBG, "SetBWModeCallback8192SUsbWorkItem():\
						unknown Bandwidth: %#X\n",priv->CurrentChannelBW);
			break;
	}

	//3 <2>Set PHY related register
	switch(priv->CurrentChannelBW)
	{
		case HT_CHANNEL_WIDTH_20:
			rtl8192_setBBreg(dev, rFPGA0_RFMOD, bRFMOD, 0x0);
			rtl8192_setBBreg(dev, rFPGA1_RFMOD, bRFMOD, 0x0);

			rtl8192_setBBreg(dev, rFPGA0_AnalogParameter2, 0xff, 0x58);

			break;
		case HT_CHANNEL_WIDTH_20_40:
			rtl8192_setBBreg(dev, rFPGA0_RFMOD, bRFMOD, 0x1);
			rtl8192_setBBreg(dev, rFPGA1_RFMOD, bRFMOD, 0x1);

			// Set Control channel to upper or lower. These settings are required only for 40MHz
			rtl8192_setBBreg(dev, rCCK0_System, bCCKSideBand, (priv->nCur40MhzPrimeSC>>1));
			rtl8192_setBBreg(dev, rOFDM1_LSTF, 0xC00, priv->nCur40MhzPrimeSC);

			rtl8192_setBBreg(dev, rFPGA0_AnalogParameter2, 0xff, 0x18);

			break;


		default:
			RT_TRACE(COMP_DBG, "SetBWModeCallback8192SUsbWorkItem(): unknown Bandwidth: %#X\n"\
						,priv->CurrentChannelBW);
			break;

	}
	//Skip over setting of J-mode in BB register here. Default value is "None J mode". Emily 20070315

	//3<3>Set RF related register
	switch( priv->rf_chip )
	{
		case RF_8225:
			PHY_SetRF8225Bandwidth(dev, priv->CurrentChannelBW);
			break;

		case RF_8256:
			// Please implement this function in Hal8190PciPhy8256.c
			//PHY_SetRF8256Bandwidth(dev, priv->CurrentChannelBW);
			break;

		case RF_6052:
			PHY_RF6052SetBandwidth(dev, priv->CurrentChannelBW);
			break;

		case RF_8258:
			// Please implement this function in Hal8190PciPhy8258.c
			// PHY_SetRF8258Bandwidth();
			break;

		case RF_PSEUDO_11N:
			// Do Nothing
			break;

		default:
			//RT_ASSERT(FALSE, ("Unknown rf_chip: %d\n", priv->rf_chip));
			break;
	}

	priv->SetBWModeInProgress= FALSE;

	RT_TRACE(COMP_SCAN, "<==SetBWModeCallback8192SUsbWorkItem()" );
}