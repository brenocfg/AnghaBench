#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_8__ {long* rxSNRdB; int /*<<< orphan*/ * received_bwtype; int /*<<< orphan*/  numqry_phystatusHT; int /*<<< orphan*/  numqry_phystatusCCK; int /*<<< orphan*/  numqry_phystatus; } ;
struct r8192_priv {TYPE_1__ stats; scalar_t__* brfpath_rxenable; int /*<<< orphan*/  bCckHighPower; } ;
struct ieee80211_rx_stats {int bPacketMatchBSSID; int bPacketToSelf; int bIsCCK; int bPacketBeacon; int bToSelfBA; int* RxMIMOSignalQuality; int RxPWDBAll; char RecvSignalPower; int SignalQuality; int* RxMIMOSignalStrength; char RxPower; int SignalStrength; } ;
struct TYPE_9__ {int* cfosho; int* gain_trsw; int* rxsnr; int pwdb_all; int rxsc; int /*<<< orphan*/ * rxevm; } ;
typedef  TYPE_2__ rx_drvinfo_819x_usb ;
struct TYPE_10__ {scalar_t__ BW; int /*<<< orphan*/  RxMCS; scalar_t__ RxHT; } ;
typedef  TYPE_3__ rx_desc_819x_usb ;
struct TYPE_11__ {int cck_agc_rpt; int sq_rpt; } ;
typedef  TYPE_4__ phy_sts_cck_819xusb_t ;
typedef  int /*<<< orphan*/  phy_ofdm_rx_status_rxsc_sgien_exintfflag ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_RF ; 
 int /*<<< orphan*/  DESC92S_RATEMCS15 ; 
 int /*<<< orphan*/  DESC92S_RATEMCS8 ; 
 int RF90_PATH_A ; 
 int RF90_PATH_MAX ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,char*,int,char,...) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  memset (struct ieee80211_rx_stats*,int /*<<< orphan*/ ,int) ; 
 int rtl819x_evm_dbtopercentage (int /*<<< orphan*/ ) ; 
 int rtl819x_query_rxpwrpercentage (char) ; 
 scalar_t__ rtl819x_signal_scale_mapping (long) ; 
 int rx_hal_is_cck_rate (TYPE_3__*) ; 

__attribute__((used)) static void rtl8192SU_query_rxphystatus(
	struct r8192_priv * priv,
	struct ieee80211_rx_stats * pstats,
	rx_desc_819x_usb	*pDesc,
	rx_drvinfo_819x_usb  * pdrvinfo,
	struct ieee80211_rx_stats * precord_stats,
	bool bpacket_match_bssid,
	bool bpacket_toself,
	bool bPacketBeacon,
	bool bToSelfBA
	)
{
	//PRT_RFD_STATUS		pRtRfdStatus = &(pRfd->Status);
	//PHY_STS_CCK_8192S_T	*pCck_buf;
	phy_sts_cck_819xusb_t	*	pcck_buf;
	phy_ofdm_rx_status_rxsc_sgien_exintfflag* prxsc;
	//u8				*prxpkt;
	//u8				i, max_spatial_stream, tmp_rxsnr, tmp_rxevm, rxsc_sgien_exflg;
	u8				i, max_spatial_stream, rxsc_sgien_exflg;
	char				rx_pwr[4], rx_pwr_all=0;
	//long				rx_avg_pwr = 0;
	//char				rx_snrX, rx_evmX;
	u8				evm, pwdb_all;
	u32				RSSI, total_rssi=0;//, total_evm=0;
//	long				signal_strength_index = 0;
	u8				is_cck_rate=0;
	u8				rf_rx_num = 0;



	priv->stats.numqry_phystatus++;

	is_cck_rate = rx_hal_is_cck_rate(pDesc);

	// Record it for next packet processing
	memset(precord_stats, 0, sizeof(struct ieee80211_rx_stats));
	pstats->bPacketMatchBSSID = precord_stats->bPacketMatchBSSID = bpacket_match_bssid;
	pstats->bPacketToSelf = precord_stats->bPacketToSelf = bpacket_toself;
	pstats->bIsCCK = precord_stats->bIsCCK = is_cck_rate;//RX_HAL_IS_CCK_RATE(pDrvInfo);
	pstats->bPacketBeacon = precord_stats->bPacketBeacon = bPacketBeacon;
	pstats->bToSelfBA = precord_stats->bToSelfBA = bToSelfBA;


	pstats->RxMIMOSignalQuality[0] = -1;
	pstats->RxMIMOSignalQuality[1] = -1;
	precord_stats->RxMIMOSignalQuality[0] = -1;
	precord_stats->RxMIMOSignalQuality[1] = -1;

	if(is_cck_rate)
	{
		u8 report;//, tmp_pwdb;
		//char cck_adc_pwdb[4];

		// CCK Driver info Structure is not the same as OFDM packet.
		pcck_buf = (phy_sts_cck_819xusb_t *)pdrvinfo;

		//
		// (1)Hardware does not provide RSSI for CCK
		//

		//
		// (2)PWDB, Average PWDB cacluated by hardware (for rate adaptive)
		//

		priv->stats.numqry_phystatusCCK++;

		if(!priv->bCckHighPower)
		{
			report = pcck_buf->cck_agc_rpt & 0xc0;
			report = report>>6;
			switch(report)
			{
				//Fixed by Jacken from Bryant 2008-03-20
				//Original value is -38 , -26 , -14 , -2
				//Fixed value is -35 , -23 , -11 , 6
				case 0x3:
					rx_pwr_all = -35 - (pcck_buf->cck_agc_rpt & 0x3e);
					break;
				case 0x2:
					rx_pwr_all = -23 - (pcck_buf->cck_agc_rpt & 0x3e);
					break;
				case 0x1:
					rx_pwr_all = -11 - (pcck_buf->cck_agc_rpt & 0x3e);
					break;
				case 0x0:
					rx_pwr_all = 8 - (pcck_buf->cck_agc_rpt & 0x3e);//6->8
					break;
			}
		}
		else
		{
			report = pdrvinfo->cfosho[0] & 0x60;
			report = report>>5;
			switch(report)
			{
				case 0x3:
					rx_pwr_all = -35 - ((pcck_buf->cck_agc_rpt & 0x1f)<<1) ;
					break;
				case 0x2:
					rx_pwr_all = -23 - ((pcck_buf->cck_agc_rpt & 0x1f)<<1);
					break;
				case 0x1:
					rx_pwr_all = -11 - ((pcck_buf->cck_agc_rpt & 0x1f)<<1) ;
					break;
				case 0x0:
					rx_pwr_all = -8 - ((pcck_buf->cck_agc_rpt & 0x1f)<<1) ;//6->-8
					break;
			}
		}

		pwdb_all = rtl819x_query_rxpwrpercentage(rx_pwr_all);//check it
		pstats->RxPWDBAll = precord_stats->RxPWDBAll = pwdb_all;
		//pstats->RecvSignalPower = pwdb_all;
		pstats->RecvSignalPower = rx_pwr_all;

		//
		// (3) Get Signal Quality (EVM)
		//
	//if(bpacket_match_bssid)
	{
			u8	sq;

			if(pstats->RxPWDBAll > 40)
			{
				sq = 100;
			}else
			{
				sq = pcck_buf->sq_rpt;

				if(pcck_buf->sq_rpt > 64)
					sq = 0;
				else if (pcck_buf->sq_rpt < 20)
					sq = 100;
				else
					sq = ((64-sq) * 100) / 44;
			}
			pstats->SignalQuality = precord_stats->SignalQuality = sq;
			pstats->RxMIMOSignalQuality[0] = precord_stats->RxMIMOSignalQuality[0] = sq;
			pstats->RxMIMOSignalQuality[1] = precord_stats->RxMIMOSignalQuality[1] = -1;
		}
	}
	else
	{
		priv->stats.numqry_phystatusHT++;

		// 2008/09/19 MH For 92S debug, RX RF path always enable!!
		priv->brfpath_rxenable[0] = priv->brfpath_rxenable[1] = TRUE;

		//
		// (1)Get RSSI for HT rate
		//
		//for(i=RF90_PATH_A; i<priv->NumTotalRFPath; i++)
		for(i=RF90_PATH_A; i<RF90_PATH_MAX; i++)
		{
			// 2008/01/30 MH we will judge RF RX path now.
			if (priv->brfpath_rxenable[i])
				rf_rx_num++;
			//else
			//	continue;

		//if (!rtl8192_phy_CheckIsLegalRFPath(priv->ieee80211->dev, i))
		//		continue;

			//Fixed by Jacken from Bryant 2008-03-20
			//Original value is 106
			//rx_pwr[i] = ((pofdm_buf->trsw_gain_X[i]&0x3F)*2) - 106;
			rx_pwr[i] = ((pdrvinfo->gain_trsw[i]&0x3F)*2) - 110;

			/* Translate DBM to percentage. */
			RSSI = rtl819x_query_rxpwrpercentage(rx_pwr[i]);	//check ok
			total_rssi += RSSI;
			RT_TRACE(COMP_RF, "RF-%d RXPWR=%x RSSI=%d\n", i, rx_pwr[i], RSSI);

			//Get Rx snr value in DB
			//tmp_rxsnr =	pofdm_buf->rxsnr_X[i];
			//rx_snrX = (char)(tmp_rxsnr);
			//rx_snrX /= 2;
			//priv->stats.rxSNRdB[i] = (long)rx_snrX;
			priv->stats.rxSNRdB[i] = (long)(pdrvinfo->rxsnr[i]/2);

			/* Translate DBM to percentage. */
			//RSSI = rtl819x_query_rxpwrpercentage(rx_pwr[i]);
			//total_rssi += RSSI;

			/* Record Signal Strength for next packet */
			//if(bpacket_match_bssid)
			{
				pstats->RxMIMOSignalStrength[i] =(u8) RSSI;
				precord_stats->RxMIMOSignalStrength[i] =(u8) RSSI;
			}
		}


		//
		// (2)PWDB, Average PWDB cacluated by hardware (for rate adaptive)
		//
		//Fixed by Jacken from Bryant 2008-03-20
		//Original value is 106
		//rx_pwr_all = (((pofdm_buf->pwdb_all ) >> 1 )& 0x7f) -106;
		rx_pwr_all = (((pdrvinfo->pwdb_all ) >> 1 )& 0x7f) -106;
		pwdb_all = rtl819x_query_rxpwrpercentage(rx_pwr_all);

		pstats->RxPWDBAll = precord_stats->RxPWDBAll = pwdb_all;
		pstats->RxPower = precord_stats->RxPower =  rx_pwr_all;
		pstats->RecvSignalPower = rx_pwr_all;

		//
		// (3)EVM of HT rate
		//
		//if(pdrvinfo->RxHT && pdrvinfo->RxRate>=DESC90_RATEMCS8 &&
		 //	pdrvinfo->RxRate<=DESC90_RATEMCS15)
		 if(pDesc->RxHT && pDesc->RxMCS>=DESC92S_RATEMCS8 &&
		 	pDesc->RxMCS<=DESC92S_RATEMCS15)
			max_spatial_stream = 2; //both spatial stream make sense
		else
			max_spatial_stream = 1; //only spatial stream 1 makes sense

		for(i=0; i<max_spatial_stream; i++)
		{
			//tmp_rxevm =	pofdm_buf->rxevm_X[i];
			//rx_evmX = (char)(tmp_rxevm);

			// Do not use shift operation like "rx_evmX >>= 1" because the compilor of free build environment
			// fill most significant bit to "zero" when doing shifting operation which may change a negative
			// value to positive one, then the dbm value (which is supposed to be negative)  is not correct anymore.
			//rx_evmX /= 2;	//dbm

			//evm = rtl819x_evm_dbtopercentage(rx_evmX);
			evm = rtl819x_evm_dbtopercentage( (pdrvinfo->rxevm[i] /*/ 2*/));	//dbm
			RT_TRACE(COMP_RF, "RXRATE=%x RXEVM=%x EVM=%s%d\n", pDesc->RxMCS, pdrvinfo->rxevm[i], "%", evm);

			//if(bpacket_match_bssid)
			{
				if(i==0) // Fill value in RFD, Get the first spatial stream only
					pstats->SignalQuality = precord_stats->SignalQuality = (u8)(evm & 0xff);
				pstats->RxMIMOSignalQuality[i] = precord_stats->RxMIMOSignalQuality[i] = (u8)(evm & 0xff);
			}
		}


		/* record rx statistics for debug */
		//rxsc_sgien_exflg = pofdm_buf->rxsc_sgien_exflg;
		prxsc =	(phy_ofdm_rx_status_rxsc_sgien_exintfflag *)&rxsc_sgien_exflg;
		//if(pdrvinfo->BW)	//40M channel
		if(pDesc->BW)	//40M channel
			priv->stats.received_bwtype[1+pdrvinfo->rxsc]++;
		else				//20M channel
			priv->stats.received_bwtype[0]++;
	}

	//UI BSS List signal strength(in percentage), make it good looking, from 0~100.
	//It is assigned to the BSS List in GetValueFromBeaconOrProbeRsp().
	if(is_cck_rate)
	{
		pstats->SignalStrength = precord_stats->SignalStrength = (u8)(rtl819x_signal_scale_mapping((long)pwdb_all));//PWDB_ALL;//check ok

	}
	else
	{
		//pRfd->Status.SignalStrength = pRecordRfd->Status.SignalStrength = (u8)(SignalScaleMapping(total_rssi/=RF90_PATH_MAX));//(u8)(total_rssi/=RF90_PATH_MAX);
		// We can judge RX path number now.
		if (rf_rx_num != 0)
			pstats->SignalStrength = precord_stats->SignalStrength = (u8)(rtl819x_signal_scale_mapping((long)(total_rssi/=rf_rx_num)));
	}
}