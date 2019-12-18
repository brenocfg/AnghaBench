#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  txbeaconerr; int /*<<< orphan*/  txbeaconokint; } ;
struct r8192_priv {TYPE_2__ stats; TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_6__ {int length; int interrupt_status; } ;
typedef  TYPE_3__ cmpk_intr_sta_t ;
struct TYPE_4__ {scalar_t__ iw_mode; int bibsscoordinator; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMESG (char*,...) ; 
 int ISR_BcnTimerIntr ; 
 int ISR_TxBcnErr ; 
 int ISR_TxBcnOk ; 
 scalar_t__ IW_MODE_ADHOC ; 
 int /*<<< orphan*/  cmdpkt_beacontimerinterrupt_819xusb (struct net_device*) ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

__attribute__((used)) static	void
cmpk_handle_interrupt_status(
	struct net_device *dev,
	u8*	pmsg)
{
	cmpk_intr_sta_t		rx_intr_status;	/* */
	struct r8192_priv *priv = ieee80211_priv(dev);

	DMESG("---> cmpk_Handle_Interrupt_Status()\n");

	/* 0. Display received message. */
	//cmpk_Display_Message(CMPK_RX_BEACON_STATE_SIZE, pMsg);

	/* 1. Extract TX feedback info from RFD to temp structure buffer. */
	/* It seems that FW use big endian(MIPS) and DRV use little endian in
	   windows OS. So we have to read the content byte by byte or transfer
	   endian type before copy the message copy. */
	//rx_bcn_state.Element_ID 	= pMsg[0];
	//rx_bcn_state.Length 		= pMsg[1];
	rx_intr_status.length = pmsg[1];
	if (rx_intr_status.length != (sizeof(cmpk_intr_sta_t) - 2))
	{
		DMESG("cmpk_Handle_Interrupt_Status: wrong length!\n");
		return;
	}


	// Statistics of beacon for ad-hoc mode.
	if(	priv->ieee80211->iw_mode == IW_MODE_ADHOC)
	{
		//2 maybe need endian transform?
		rx_intr_status.interrupt_status = *((u32 *)(pmsg + 4));
		//rx_intr_status.InterruptStatus = N2H4BYTE(*((UINT32 *)(pMsg + 4)));

		DMESG("interrupt status = 0x%x\n", rx_intr_status.interrupt_status);

		if (rx_intr_status.interrupt_status & ISR_TxBcnOk)
		{
			priv->ieee80211->bibsscoordinator = true;
			priv->stats.txbeaconokint++;
		}
		else if (rx_intr_status.interrupt_status & ISR_TxBcnErr)
		{
			priv->ieee80211->bibsscoordinator = false;
			priv->stats.txbeaconerr++;
		}

		if (rx_intr_status.interrupt_status & ISR_BcnTimerIntr)
		{
			cmdpkt_beacontimerinterrupt_819xusb(dev);
		}

	}

	 // Other informations in interrupt status we need?


	DMESG("<---- cmpk_handle_interrupt_status()\n");

}