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
typedef  int /*<<< orphan*/  zdev_t ;

/* Variables and functions */
 int ZM_MAC_REG_ACK_EXTENSION ; 
 int ZM_MAC_REG_BACKOFF_PROTECT ; 
 int ZM_MAC_REG_BASIC_RATE ; 
 int ZM_MAC_REG_BCN_HT1 ; 
 int ZM_MAC_REG_EIFS_AND_SIFS ; 
 int ZM_MAC_REG_MANDATORY_RATE ; 
 int ZM_MAC_REG_RETRY_MAX ; 
 int ZM_MAC_REG_RTS_CTS_RATE ; 
 int ZM_MAC_REG_RX_PE_DELAY ; 
 int ZM_MAC_REG_RX_THRESHOLD ; 
 int ZM_MAC_REG_SLOT_TIME ; 
 int ZM_MAC_REG_SNIFFER ; 
 int ZM_MAC_REG_TXOP_NOT_ENOUGH_INDICATION ; 
 int /*<<< orphan*/  zfDelayWriteInternalReg (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  zfFlushDelayWrite (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfUpdateDefaultQosParameter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void zfInitMac(zdev_t* dev)
{
    /* ACK extension register */
    // jhlee temp : change value 0x2c -> 0x40
    // honda resolve short preamble problem : 0x40 -> 0x75
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_ACK_EXTENSION, 0x40); // 0x28 -> 0x2c 6522:yflee

    /* TxQ0/1/2/3 Retry MAX=2 => transmit 3 times and degrade rate for retry */
    /* PB42 AP crash issue:                                                  */
    /* Workaround the crash issue by CTS/RTS, set retry max to zero for      */
    /*   workaround tx underrun which enable CTS/RTS */
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_RETRY_MAX, 0); // 0x11111 => 0

    /* use hardware MIC check */
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_SNIFFER, 0x2000000);

    /* Set Rx threshold to 1600 */
#if ZM_LARGEPAYLOAD_TEST == 1
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_RX_THRESHOLD, 0xc4000);
#else
    #ifndef ZM_DISABLE_AMSDU8K_SUPPORT
    /* The maximum A-MSDU length is 3839/7935 */
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_RX_THRESHOLD, 0xc1f80);
    #else
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_RX_THRESHOLD, 0xc0f80);
    #endif
#endif

    //zfDelayWriteInternalReg(dev, ZM_MAC_REG_DYNAMIC_SIFS_ACK, 0x10A);
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_RX_PE_DELAY, 0x70);
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_EIFS_AND_SIFS, 0xa144000);
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_SLOT_TIME, 9<<10);

    /* CF-END mode */
    zfDelayWriteInternalReg(dev, 0x1c3b2c, 0x19000000);

    //NAV protects ACK only (in TXOP)
    zfDelayWriteInternalReg(dev, 0x1c3b38, 0x201);


    /* Set Beacon PHY CTRL's TPC to 0x7, TA1=1 */
    /* OTUS set AM to 0x1 */
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_BCN_HT1, 0x8000170);

    /* TODO : wep backoff protection 0x63c */
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_BACKOFF_PROTECT, 0x105);

    /* AGG test code*/
    /* Aggregation MAX number and timeout */
    zfDelayWriteInternalReg(dev, 0x1c3b9c, 0x10000a);
    /* Filter any control frames, BAR is bit 24 */
    zfDelayWriteInternalReg(dev, 0x1c368c, 0x0500ffff);
    /* Enable deaggregator */
    zfDelayWriteInternalReg(dev, 0x1c3c40, 0x1);

    /* Basic rate */
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_BASIC_RATE, 0x150f);
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_MANDATORY_RATE, 0x150f);
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_RTS_CTS_RATE, 0x10b01bb);

    /* MIMO resposne control */
    zfDelayWriteInternalReg(dev, 0x1c3694, 0x4003C1E);/* bit 26~28  otus-AM */

    /* Enable LED0 and LED1 */
    zfDelayWriteInternalReg(dev, 0x1d0100, 0x3);
    zfDelayWriteInternalReg(dev, 0x1d0104, 0x3);

    /* switch MAC to OTUS interface */
    zfDelayWriteInternalReg(dev, 0x1c3600, 0x3);

    /* RXMAC A-MPDU length threshold */
    zfDelayWriteInternalReg(dev, 0x1c3c50, 0xffff);

	/* Phy register read timeout */
	zfDelayWriteInternalReg(dev, 0x1c3680, 0xf00008);

	/* Disable Rx TimeOut : workaround for BB.
	 *  OTUS would interrupt the rx frame that sent by OWL TxUnderRun
	 *  because OTUS rx timeout behavior, then OTUS would not ack the BA for
	 *  this AMPDU from OWL.
	 *  Fix by Perry Hwang.  2007/05/10.
	 *  0x1c362c : Rx timeout value : bit 27~16
	 */
	zfDelayWriteInternalReg(dev, 0x1c362c, 0x0);

    //Set USB Rx stream mode MAX packet number to 2
    //    Max packet number = *0x1e1110 + 1
    zfDelayWriteInternalReg(dev, 0x1e1110, 0x4);
    //Set USB Rx stream mode timeout to 10us
    zfDelayWriteInternalReg(dev, 0x1e1114, 0x80);

    //Set CPU clock frequency to 88/80MHz
    zfDelayWriteInternalReg(dev, 0x1D4008, 0x73);

    //Set WLAN DMA interrupt mode : generate int per packet
    zfDelayWriteInternalReg(dev, 0x1c3d7c, 0x110011);

    /* 7807 */
    /* enable func : Reset FIFO1 and FIFO2 when queue-gnt is low */
    /* 0x1c3bb0 Bit2 */
    /* Disable SwReset in firmware for TxHang, enable reset FIFO func. */
    zfDelayWriteInternalReg(dev, 0x1c3bb0, 0x4);

    /* Disables the CF_END frame */
    zfDelayWriteInternalReg(dev, ZM_MAC_REG_TXOP_NOT_ENOUGH_INDICATION, 0x141E0F48);

	/* Disable the SW Decrypt*/
	zfDelayWriteInternalReg(dev, 0x1c3678, 0x70);
    zfFlushDelayWrite(dev);
    //---------------------

    /* Set TxQs CWMIN, CWMAX, AIFS and TXO to WME STA default. */
    zfUpdateDefaultQosParameter(dev, 0);

    //zfSelAdcClk(dev, 0);

    return;
}