#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int /*<<< orphan*/  txfeedback; } ;
struct r8192_priv {TYPE_1__ stats; } ;
struct net_device {int dummy; } ;
struct TYPE_7__ {int TOK; int Fail_Reason; int TID; int Qos_Pkt; int Bandwidth; int Retry_Cnt; int Pkt_ID; int Seq_Num; int S_Rate; int F_Rate; int S_RTS_Rate; int F_RTS_Rate; int pkt_length; } ;
typedef  TYPE_2__ cmpk_txfb_t ;
struct TYPE_9__ {scalar_t__ RegWirelessMode; } ;
struct TYPE_8__ {int CurrentOperaRate; int HTCurrentOperaRate; } ;

/* Variables and functions */
 scalar_t__ WIRELESS_MODE_A ; 
 scalar_t__ WIRELESS_MODE_B ; 
 scalar_t__ WIRELESS_MODE_G ; 
 scalar_t__ WIRELESS_MODE_N_24G ; 
 scalar_t__ WIRELESS_MODE_N_5G ; 
 int /*<<< orphan*/  cmpk_count_txstatistic (struct net_device*,TYPE_2__*) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_4__* pAdapter ; 
 TYPE_3__* pMgntInfo ; 
 int* pMsg ; 

__attribute__((used)) static	void
cmpk_handle_tx_feedback(
	struct net_device *dev,
	u8	*	pmsg)
{
	struct r8192_priv *priv = ieee80211_priv(dev);
	cmpk_txfb_t		rx_tx_fb;	/* */

	priv->stats.txfeedback++;

	/* 0. Display received message. */
	//cmpk_Display_Message(CMPK_RX_TX_FB_SIZE, pMsg);

	/* 1. Extract TX feedback info from RFD to temp structure buffer. */
	/* It seems that FW use big endian(MIPS) and DRV use little endian in
	   windows OS. So we have to read the content byte by byte or transfer
	   endian type before copy the message copy. */
#if 0		// The TX FEEDBACK packet element address
	//rx_tx_fb.Element_ID 	= pMsg[0];
	//rx_tx_fb.Length 		= pMsg[1];
	rx_tx_fb.TOK 			= pMsg[2]>>7;
	rx_tx_fb.Fail_Reason 	= (pMsg[2] & 0x70) >> 4;
	rx_tx_fb.TID 			= (pMsg[2] & 0x0F);
	rx_tx_fb.Qos_Pkt 		= pMsg[3] >> 7;
	rx_tx_fb.Bandwidth 		= (pMsg[3] & 0x40) >> 6;
	rx_tx_fb.Retry_Cnt 		= pMsg[5];
	rx_tx_fb.Pkt_ID 		= (pMsg[6] << 8) | pMsg[7];
	rx_tx_fb.Seq_Num 		= (pMsg[8] << 8) | pMsg[9];
	rx_tx_fb.S_Rate 		= pMsg[10];
	rx_tx_fb.F_Rate 		= pMsg[11];
	rx_tx_fb.S_RTS_Rate 	= pMsg[12];
	rx_tx_fb.F_RTS_Rate 	= pMsg[13];
	rx_tx_fb.pkt_length	= (pMsg[14] << 8) | pMsg[15];
#endif
	/* 2007/07/05 MH Use pointer to transfer structure memory. */
	//memcpy((UINT8 *)&rx_tx_fb, pMsg, sizeof(CMPK_TXFB_T));
	memcpy((u8*)&rx_tx_fb, pmsg, sizeof(cmpk_txfb_t));
	/* 2. Use tx feedback info to count TX statistics. */
	cmpk_count_txstatistic(dev, &rx_tx_fb);
#if 0
	/* 2007/07/11 MH Assign current operate rate.  */
	if (pAdapter->RegWirelessMode == WIRELESS_MODE_A ||
		pAdapter->RegWirelessMode == WIRELESS_MODE_B ||
		pAdapter->RegWirelessMode == WIRELESS_MODE_G)
	{
		pMgntInfo->CurrentOperaRate = (rx_tx_fb.F_Rate & 0x7F);
	}
	else if (pAdapter->RegWirelessMode == WIRELESS_MODE_N_24G ||
		 	 pAdapter->RegWirelessMode == WIRELESS_MODE_N_5G)
	{
		pMgntInfo->HTCurrentOperaRate = (rx_tx_fb.F_Rate & 0x8F);
	}
#endif
	/* 2007/01/17 MH Comment previous method for TX statistic function. */
	/* Collect info TX feedback packet to fill TCB. */
	/* We can not know the packet length and transmit type: broadcast or uni
	   or multicast. */
	//CountTxStatistics( pAdapter, &tcb );

}