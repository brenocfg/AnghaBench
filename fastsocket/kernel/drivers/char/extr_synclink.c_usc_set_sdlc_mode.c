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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int flags; scalar_t__ mode; int preamble; int addr_filter; int encoding; int crc_type; int clock_speed; int preamble_length; } ;
struct mgsl_struct {int cmr_value; scalar_t__ bus_type; int tcsr_value; int mbre_bit; TYPE_1__ params; int /*<<< orphan*/  io_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDCR ; 
 int BIT10 ; 
 int BIT11 ; 
 int BIT12 ; 
 int BIT13 ; 
 int BIT14 ; 
 int BIT15 ; 
 int BIT3 ; 
 int BIT4 ; 
 int BIT8 ; 
 int BIT9 ; 
 int /*<<< orphan*/  CCR ; 
 int /*<<< orphan*/  CCSR ; 
 int /*<<< orphan*/  CDIR ; 
 int /*<<< orphan*/  CMCR ; 
 int /*<<< orphan*/  CMR ; 
 int /*<<< orphan*/  DCR ; 
 int /*<<< orphan*/  DICR ; 
 int /*<<< orphan*/  DmaCmd_ResetAllChannels ; 
 int /*<<< orphan*/  HCR ; 
 int HDLC_CRC_16_CCITT ; 
 int HDLC_CRC_32_CCITT ; 
 int HDLC_CRC_MASK ; 
#define  HDLC_ENCODING_BIPHASE_LEVEL 142 
#define  HDLC_ENCODING_BIPHASE_MARK 141 
#define  HDLC_ENCODING_BIPHASE_SPACE 140 
#define  HDLC_ENCODING_DIFF_BIPHASE_LEVEL 139 
#define  HDLC_ENCODING_NRZ 138 
#define  HDLC_ENCODING_NRZB 137 
#define  HDLC_ENCODING_NRZI_MARK 136 
#define  HDLC_ENCODING_NRZI_SPACE 135 
 int HDLC_FLAG_AUTO_CTS ; 
 int HDLC_FLAG_DPLL_DIV16 ; 
 int HDLC_FLAG_DPLL_DIV8 ; 
 int HDLC_FLAG_HDLC_LOOPMODE ; 
 int HDLC_FLAG_RXC_BRG ; 
 int HDLC_FLAG_RXC_DPLL ; 
 int HDLC_FLAG_RXC_TXCPIN ; 
 int HDLC_FLAG_SHARE_ZERO ; 
 int HDLC_FLAG_TXC_BRG ; 
 int HDLC_FLAG_TXC_DPLL ; 
 int HDLC_FLAG_TXC_RXCPIN ; 
 int HDLC_FLAG_UNDERRUN_ABORT15 ; 
 int HDLC_FLAG_UNDERRUN_CRC ; 
 int HDLC_FLAG_UNDERRUN_FLAG ; 
#define  HDLC_PREAMBLE_LENGTH_16BITS 134 
#define  HDLC_PREAMBLE_LENGTH_32BITS 133 
#define  HDLC_PREAMBLE_LENGTH_64BITS 132 
#define  HDLC_PREAMBLE_PATTERN_01 131 
#define  HDLC_PREAMBLE_PATTERN_10 130 
#define  HDLC_PREAMBLE_PATTERN_FLAGS 129 
 int HDLC_PREAMBLE_PATTERN_NONE ; 
#define  HDLC_PREAMBLE_PATTERN_ONES 128 
 int /*<<< orphan*/  IOCR ; 
 int IUSC_PRE_SL1660 ; 
 scalar_t__ MGSL_BUS_TYPE_ISA ; 
 scalar_t__ MGSL_BUS_TYPE_PCI ; 
 scalar_t__ MGSL_MODE_HDLC ; 
 scalar_t__ MGSL_MODE_RAW ; 
 scalar_t__ MISC ; 
 int /*<<< orphan*/  PCR ; 
 int /*<<< orphan*/  RCLR ; 
 int RCLRVALUE ; 
 int /*<<< orphan*/  RCmd_SelectRicrdma_level ; 
 int /*<<< orphan*/  RDMR ; 
 scalar_t__ RECEIVE_DATA ; 
 scalar_t__ RECEIVE_STATUS ; 
 int /*<<< orphan*/  RICR ; 
 int /*<<< orphan*/  RMR ; 
 int /*<<< orphan*/  RSR ; 
 int /*<<< orphan*/  RXSTATUS_ALL ; 
 int /*<<< orphan*/  SICR ; 
 int SICR_CTS_INACTIVE ; 
 int /*<<< orphan*/  TC1R ; 
 int /*<<< orphan*/  TCSR ; 
 int TCSR_UNDERWAIT ; 
 int /*<<< orphan*/  TCmd_SelectTicrdma_level ; 
 int /*<<< orphan*/  TDMR ; 
 int /*<<< orphan*/  TICR ; 
 int /*<<< orphan*/  TMCR ; 
 int /*<<< orphan*/  TMDR ; 
 int /*<<< orphan*/  TMR ; 
 scalar_t__ TRANSMIT_DATA ; 
 scalar_t__ TRANSMIT_STATUS ; 
 int /*<<< orphan*/  TXSTATUS_ALL ; 
 int /*<<< orphan*/  outw (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_ClearIrqPendingBits (struct mgsl_struct*,scalar_t__) ; 
 int /*<<< orphan*/  usc_DmaCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_EnableInterrupts (struct mgsl_struct*,scalar_t__) ; 
 int /*<<< orphan*/  usc_EnableMasterIrqBit (struct mgsl_struct*) ; 
 int /*<<< orphan*/  usc_InDmaReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int usc_InReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_OutDmaReg (struct mgsl_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usc_OutReg (struct mgsl_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usc_RCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_TCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_UnlatchRxstatusBits (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_UnlatchTxstatusBits (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_set_txidle (struct mgsl_struct*) ; 
 int /*<<< orphan*/  usc_stop_receiver (struct mgsl_struct*) ; 
 int /*<<< orphan*/  usc_stop_transmitter (struct mgsl_struct*) ; 

__attribute__((used)) static void usc_set_sdlc_mode( struct mgsl_struct *info )
{
	u16 RegValue;
	bool PreSL1660;
	
	/*
	 * determine if the IUSC on the adapter is pre-SL1660. If
	 * not, take advantage of the UnderWait feature of more
	 * modern chips. If an underrun occurs and this bit is set,
	 * the transmitter will idle the programmed idle pattern
	 * until the driver has time to service the underrun. Otherwise,
	 * the dma controller may get the cycles previously requested
	 * and begin transmitting queued tx data.
	 */
	usc_OutReg(info,TMCR,0x1f);
	RegValue=usc_InReg(info,TMDR);
	PreSL1660 = (RegValue == IUSC_PRE_SL1660);

 	if ( info->params.flags & HDLC_FLAG_HDLC_LOOPMODE )
 	{
 	   /*
 	   ** Channel Mode Register (CMR)
 	   **
 	   ** <15..14>    10    Tx Sub Modes, Send Flag on Underrun
 	   ** <13>        0     0 = Transmit Disabled (initially)
 	   ** <12>        0     1 = Consecutive Idles share common 0
 	   ** <11..8>     1110  Transmitter Mode = HDLC/SDLC Loop
 	   ** <7..4>      0000  Rx Sub Modes, addr/ctrl field handling
 	   ** <3..0>      0110  Receiver Mode = HDLC/SDLC
 	   **
 	   ** 1000 1110 0000 0110 = 0x8e06
 	   */
 	   RegValue = 0x8e06;
 
 	   /*--------------------------------------------------
 	    * ignore user options for UnderRun Actions and
 	    * preambles
 	    *--------------------------------------------------*/
 	}
 	else
 	{	
		/* Channel mode Register (CMR)
		 *
		 * <15..14>  00    Tx Sub modes, Underrun Action
		 * <13>      0     1 = Send Preamble before opening flag
		 * <12>      0     1 = Consecutive Idles share common 0
		 * <11..8>   0110  Transmitter mode = HDLC/SDLC
		 * <7..4>    0000  Rx Sub modes, addr/ctrl field handling
		 * <3..0>    0110  Receiver mode = HDLC/SDLC
		 *
		 * 0000 0110 0000 0110 = 0x0606
		 */
		if (info->params.mode == MGSL_MODE_RAW) {
			RegValue = 0x0001;		/* Set Receive mode = external sync */

			usc_OutReg( info, IOCR,		/* Set IOCR DCD is RxSync Detect Input */
				(unsigned short)((usc_InReg(info, IOCR) & ~(BIT13|BIT12)) | BIT12));

			/*
			 * TxSubMode:
			 * 	CMR <15>		0	Don't send CRC on Tx Underrun
			 * 	CMR <14>		x	undefined
			 * 	CMR <13>		0	Send preamble before openning sync
			 * 	CMR <12>		0	Send 8-bit syncs, 1=send Syncs per TxLength
			 *
			 * TxMode:
			 * 	CMR <11-8)	0100	MonoSync
			 *
			 * 	0x00 0100 xxxx xxxx  04xx
			 */
			RegValue |= 0x0400;
		}
		else {

		RegValue = 0x0606;

		if ( info->params.flags & HDLC_FLAG_UNDERRUN_ABORT15 )
			RegValue |= BIT14;
		else if ( info->params.flags & HDLC_FLAG_UNDERRUN_FLAG )
			RegValue |= BIT15;
		else if ( info->params.flags & HDLC_FLAG_UNDERRUN_CRC )
			RegValue |= BIT15 + BIT14;
		}

		if ( info->params.preamble != HDLC_PREAMBLE_PATTERN_NONE )
			RegValue |= BIT13;
	}

	if ( info->params.mode == MGSL_MODE_HDLC &&
		(info->params.flags & HDLC_FLAG_SHARE_ZERO) )
		RegValue |= BIT12;

	if ( info->params.addr_filter != 0xff )
	{
		/* set up receive address filtering */
		usc_OutReg( info, RSR, info->params.addr_filter );
		RegValue |= BIT4;
	}

	usc_OutReg( info, CMR, RegValue );
	info->cmr_value = RegValue;

	/* Receiver mode Register (RMR)
	 *
	 * <15..13>  000    encoding
	 * <12..11>  00     FCS = 16bit CRC CCITT (x15 + x12 + x5 + 1)
	 * <10>      1      1 = Set CRC to all 1s (use for SDLC/HDLC)
	 * <9>       0      1 = Include Receive chars in CRC
	 * <8>       1      1 = Use Abort/PE bit as abort indicator
	 * <7..6>    00     Even parity
	 * <5>       0      parity disabled
	 * <4..2>    000    Receive Char Length = 8 bits
	 * <1..0>    00     Disable Receiver
	 *
	 * 0000 0101 0000 0000 = 0x0500
	 */

	RegValue = 0x0500;

	switch ( info->params.encoding ) {
	case HDLC_ENCODING_NRZB:               RegValue |= BIT13; break;
	case HDLC_ENCODING_NRZI_MARK:          RegValue |= BIT14; break;
	case HDLC_ENCODING_NRZI_SPACE:	       RegValue |= BIT14 + BIT13; break;
	case HDLC_ENCODING_BIPHASE_MARK:       RegValue |= BIT15; break;
	case HDLC_ENCODING_BIPHASE_SPACE:      RegValue |= BIT15 + BIT13; break;
	case HDLC_ENCODING_BIPHASE_LEVEL:      RegValue |= BIT15 + BIT14; break;
	case HDLC_ENCODING_DIFF_BIPHASE_LEVEL: RegValue |= BIT15 + BIT14 + BIT13; break;
	}

	if ( (info->params.crc_type & HDLC_CRC_MASK) == HDLC_CRC_16_CCITT )
		RegValue |= BIT9;
	else if ( (info->params.crc_type & HDLC_CRC_MASK) == HDLC_CRC_32_CCITT )
		RegValue |= ( BIT12 | BIT10 | BIT9 );

	usc_OutReg( info, RMR, RegValue );

	/* Set the Receive count Limit Register (RCLR) to 0xffff. */
	/* When an opening flag of an SDLC frame is recognized the */
	/* Receive Character count (RCC) is loaded with the value in */
	/* RCLR. The RCC is decremented for each received byte.  The */
	/* value of RCC is stored after the closing flag of the frame */
	/* allowing the frame size to be computed. */

	usc_OutReg( info, RCLR, RCLRVALUE );

	usc_RCmd( info, RCmd_SelectRicrdma_level );

	/* Receive Interrupt Control Register (RICR)
	 *
	 * <15..8>	?	RxFIFO DMA Request Level
	 * <7>		0	Exited Hunt IA (Interrupt Arm)
	 * <6>		0	Idle Received IA
	 * <5>		0	Break/Abort IA
	 * <4>		0	Rx Bound IA
	 * <3>		1	Queued status reflects oldest 2 bytes in FIFO
	 * <2>		0	Abort/PE IA
	 * <1>		1	Rx Overrun IA
	 * <0>		0	Select TC0 value for readback
	 *
	 *	0000 0000 0000 1000 = 0x000a
	 */

	/* Carry over the Exit Hunt and Idle Received bits */
	/* in case they have been armed by usc_ArmEvents.   */

	RegValue = usc_InReg( info, RICR ) & 0xc0;

	if ( info->bus_type == MGSL_BUS_TYPE_PCI )
		usc_OutReg( info, RICR, (u16)(0x030a | RegValue) );
	else
		usc_OutReg( info, RICR, (u16)(0x140a | RegValue) );

	/* Unlatch all Rx status bits and clear Rx status IRQ Pending */

	usc_UnlatchRxstatusBits( info, RXSTATUS_ALL );
	usc_ClearIrqPendingBits( info, RECEIVE_STATUS );

	/* Transmit mode Register (TMR)
	 *	
	 * <15..13>	000	encoding
	 * <12..11>	00	FCS = 16bit CRC CCITT (x15 + x12 + x5 + 1)
	 * <10>		1	1 = Start CRC as all 1s (use for SDLC/HDLC)
	 * <9>		0	1 = Tx CRC Enabled
	 * <8>		0	1 = Append CRC to end of transmit frame
	 * <7..6>	00	Transmit parity Even
	 * <5>		0	Transmit parity Disabled
	 * <4..2>	000	Tx Char Length = 8 bits
	 * <1..0>	00	Disable Transmitter
	 *
	 * 	0000 0100 0000 0000 = 0x0400
	 */

	RegValue = 0x0400;

	switch ( info->params.encoding ) {
	case HDLC_ENCODING_NRZB:               RegValue |= BIT13; break;
	case HDLC_ENCODING_NRZI_MARK:          RegValue |= BIT14; break;
	case HDLC_ENCODING_NRZI_SPACE:         RegValue |= BIT14 + BIT13; break;
	case HDLC_ENCODING_BIPHASE_MARK:       RegValue |= BIT15; break;
	case HDLC_ENCODING_BIPHASE_SPACE:      RegValue |= BIT15 + BIT13; break;
	case HDLC_ENCODING_BIPHASE_LEVEL:      RegValue |= BIT15 + BIT14; break;
	case HDLC_ENCODING_DIFF_BIPHASE_LEVEL: RegValue |= BIT15 + BIT14 + BIT13; break;
	}

	if ( (info->params.crc_type & HDLC_CRC_MASK) == HDLC_CRC_16_CCITT )
		RegValue |= BIT9 + BIT8;
	else if ( (info->params.crc_type & HDLC_CRC_MASK) == HDLC_CRC_32_CCITT )
		RegValue |= ( BIT12 | BIT10 | BIT9 | BIT8);

	usc_OutReg( info, TMR, RegValue );

	usc_set_txidle( info );


	usc_TCmd( info, TCmd_SelectTicrdma_level );

	/* Transmit Interrupt Control Register (TICR)
	 *
	 * <15..8>	?	Transmit FIFO DMA Level
	 * <7>		0	Present IA (Interrupt Arm)
	 * <6>		0	Idle Sent IA
	 * <5>		1	Abort Sent IA
	 * <4>		1	EOF/EOM Sent IA
	 * <3>		0	CRC Sent IA
	 * <2>		1	1 = Wait for SW Trigger to Start Frame
	 * <1>		1	Tx Underrun IA
	 * <0>		0	TC0 constant on read back
	 *
	 *	0000 0000 0011 0110 = 0x0036
	 */

	if ( info->bus_type == MGSL_BUS_TYPE_PCI )
		usc_OutReg( info, TICR, 0x0736 );
	else								
		usc_OutReg( info, TICR, 0x1436 );

	usc_UnlatchTxstatusBits( info, TXSTATUS_ALL );
	usc_ClearIrqPendingBits( info, TRANSMIT_STATUS );

	/*
	** Transmit Command/Status Register (TCSR)
	**
	** <15..12>	0000	TCmd
	** <11> 	0/1	UnderWait
	** <10..08>	000	TxIdle
	** <7>		x	PreSent
	** <6>         	x	IdleSent
	** <5>         	x	AbortSent
	** <4>         	x	EOF/EOM Sent
	** <3>         	x	CRC Sent
	** <2>         	x	All Sent
	** <1>         	x	TxUnder
	** <0>         	x	TxEmpty
	** 
	** 0000 0000 0000 0000 = 0x0000
	*/
	info->tcsr_value = 0;

	if ( !PreSL1660 )
		info->tcsr_value |= TCSR_UNDERWAIT;
		
	usc_OutReg( info, TCSR, info->tcsr_value );

	/* Clock mode Control Register (CMCR)
	 *
	 * <15..14>	00	counter 1 Source = Disabled
	 * <13..12> 	00	counter 0 Source = Disabled
	 * <11..10> 	11	BRG1 Input is TxC Pin
	 * <9..8>	11	BRG0 Input is TxC Pin
	 * <7..6>	01	DPLL Input is BRG1 Output
	 * <5..3>	XXX	TxCLK comes from Port 0
	 * <2..0>   	XXX	RxCLK comes from Port 1
	 *
	 *	0000 1111 0111 0111 = 0x0f77
	 */

	RegValue = 0x0f40;

	if ( info->params.flags & HDLC_FLAG_RXC_DPLL )
		RegValue |= 0x0003;	/* RxCLK from DPLL */
	else if ( info->params.flags & HDLC_FLAG_RXC_BRG )
		RegValue |= 0x0004;	/* RxCLK from BRG0 */
 	else if ( info->params.flags & HDLC_FLAG_RXC_TXCPIN)
 		RegValue |= 0x0006;	/* RxCLK from TXC Input */
	else
		RegValue |= 0x0007;	/* RxCLK from Port1 */

	if ( info->params.flags & HDLC_FLAG_TXC_DPLL )
		RegValue |= 0x0018;	/* TxCLK from DPLL */
	else if ( info->params.flags & HDLC_FLAG_TXC_BRG )
		RegValue |= 0x0020;	/* TxCLK from BRG0 */
 	else if ( info->params.flags & HDLC_FLAG_TXC_RXCPIN)
 		RegValue |= 0x0038;	/* RxCLK from TXC Input */
	else
		RegValue |= 0x0030;	/* TxCLK from Port0 */

	usc_OutReg( info, CMCR, RegValue );


	/* Hardware Configuration Register (HCR)
	 *
	 * <15..14>	00	CTR0 Divisor:00=32,01=16,10=8,11=4
	 * <13>		0	CTR1DSel:0=CTR0Div determines CTR0Div
	 * <12>		0	CVOK:0=report code violation in biphase
	 * <11..10>	00	DPLL Divisor:00=32,01=16,10=8,11=4
	 * <9..8>	XX	DPLL mode:00=disable,01=NRZ,10=Biphase,11=Biphase Level
	 * <7..6>	00	reserved
	 * <5>		0	BRG1 mode:0=continuous,1=single cycle
	 * <4>		X	BRG1 Enable
	 * <3..2>	00	reserved
	 * <1>		0	BRG0 mode:0=continuous,1=single cycle
	 * <0>		0	BRG0 Enable
	 */

	RegValue = 0x0000;

	if ( info->params.flags & (HDLC_FLAG_RXC_DPLL + HDLC_FLAG_TXC_DPLL) ) {
		u32 XtalSpeed;
		u32 DpllDivisor;
		u16 Tc;

		/*  DPLL is enabled. Use BRG1 to provide continuous reference clock  */
		/*  for DPLL. DPLL mode in HCR is dependent on the encoding used. */

		if ( info->bus_type == MGSL_BUS_TYPE_PCI )
			XtalSpeed = 11059200;
		else
			XtalSpeed = 14745600;

		if ( info->params.flags & HDLC_FLAG_DPLL_DIV16 ) {
			DpllDivisor = 16;
			RegValue |= BIT10;
		}
		else if ( info->params.flags & HDLC_FLAG_DPLL_DIV8 ) {
			DpllDivisor = 8;
			RegValue |= BIT11;
		}
		else
			DpllDivisor = 32;

		/*  Tc = (Xtal/Speed) - 1 */
		/*  If twice the remainder of (Xtal/Speed) is greater than Speed */
		/*  then rounding up gives a more precise time constant. Instead */
		/*  of rounding up and then subtracting 1 we just don't subtract */
		/*  the one in this case. */

 		/*--------------------------------------------------
 		 * ejz: for DPLL mode, application should use the
 		 * same clock speed as the partner system, even 
 		 * though clocking is derived from the input RxData.
 		 * In case the user uses a 0 for the clock speed,
 		 * default to 0xffffffff and don't try to divide by
 		 * zero
 		 *--------------------------------------------------*/
 		if ( info->params.clock_speed )
 		{
			Tc = (u16)((XtalSpeed/DpllDivisor)/info->params.clock_speed);
			if ( !((((XtalSpeed/DpllDivisor) % info->params.clock_speed) * 2)
			       / info->params.clock_speed) )
				Tc--;
 		}
 		else
 			Tc = -1;
 				  

		/* Write 16-bit Time Constant for BRG1 */
		usc_OutReg( info, TC1R, Tc );

		RegValue |= BIT4;		/* enable BRG1 */

		switch ( info->params.encoding ) {
		case HDLC_ENCODING_NRZ:
		case HDLC_ENCODING_NRZB:
		case HDLC_ENCODING_NRZI_MARK:
		case HDLC_ENCODING_NRZI_SPACE: RegValue |= BIT8; break;
		case HDLC_ENCODING_BIPHASE_MARK:
		case HDLC_ENCODING_BIPHASE_SPACE: RegValue |= BIT9; break;
		case HDLC_ENCODING_BIPHASE_LEVEL:
		case HDLC_ENCODING_DIFF_BIPHASE_LEVEL: RegValue |= BIT9 + BIT8; break;
		}
	}

	usc_OutReg( info, HCR, RegValue );


	/* Channel Control/status Register (CCSR)
	 *
	 * <15>		X	RCC FIFO Overflow status (RO)
	 * <14>		X	RCC FIFO Not Empty status (RO)
	 * <13>		0	1 = Clear RCC FIFO (WO)
	 * <12>		X	DPLL Sync (RW)
	 * <11>		X	DPLL 2 Missed Clocks status (RO)
	 * <10>		X	DPLL 1 Missed Clock status (RO)
	 * <9..8>	00	DPLL Resync on rising and falling edges (RW)
	 * <7>		X	SDLC Loop On status (RO)
	 * <6>		X	SDLC Loop Send status (RO)
	 * <5>		1	Bypass counters for TxClk and RxClk (RW)
	 * <4..2>   	000	Last Char of SDLC frame has 8 bits (RW)
	 * <1..0>   	00	reserved
	 *
	 *	0000 0000 0010 0000 = 0x0020
	 */

	usc_OutReg( info, CCSR, 0x1020 );


	if ( info->params.flags & HDLC_FLAG_AUTO_CTS ) {
		usc_OutReg( info, SICR,
			    (u16)(usc_InReg(info,SICR) | SICR_CTS_INACTIVE) );
	}
	

	/* enable Master Interrupt Enable bit (MIE) */
	usc_EnableMasterIrqBit( info );

	usc_ClearIrqPendingBits( info, RECEIVE_STATUS + RECEIVE_DATA +
				TRANSMIT_STATUS + TRANSMIT_DATA + MISC);

	/* arm RCC underflow interrupt */
	usc_OutReg(info, SICR, (u16)(usc_InReg(info,SICR) | BIT3));
	usc_EnableInterrupts(info, MISC);

	info->mbre_bit = 0;
	outw( 0, info->io_base ); 			/* clear Master Bus Enable (DCAR) */
	usc_DmaCmd( info, DmaCmd_ResetAllChannels );	/* disable both DMA channels */
	info->mbre_bit = BIT8;
	outw( BIT8, info->io_base );			/* set Master Bus Enable (DCAR) */

	if (info->bus_type == MGSL_BUS_TYPE_ISA) {
		/* Enable DMAEN (Port 7, Bit 14) */
		/* This connects the DMA request signal to the ISA bus */
		usc_OutReg(info, PCR, (u16)((usc_InReg(info, PCR) | BIT15) & ~BIT14));
	}

	/* DMA Control Register (DCR)
	 *
	 * <15..14>	10	Priority mode = Alternating Tx/Rx
	 *		01	Rx has priority
	 *		00	Tx has priority
	 *
	 * <13>		1	Enable Priority Preempt per DCR<15..14>
	 *			(WARNING DCR<11..10> must be 00 when this is 1)
	 *		0	Choose activate channel per DCR<11..10>
	 *
	 * <12>		0	Little Endian for Array/List
	 * <11..10>	00	Both Channels can use each bus grant
	 * <9..6>	0000	reserved
	 * <5>		0	7 CLK - Minimum Bus Re-request Interval
	 * <4>		0	1 = drive D/C and S/D pins
	 * <3>		1	1 = Add one wait state to all DMA cycles.
	 * <2>		0	1 = Strobe /UAS on every transfer.
	 * <1..0>	11	Addr incrementing only affects LS24 bits
	 *
	 *	0110 0000 0000 1011 = 0x600b
	 */

	if ( info->bus_type == MGSL_BUS_TYPE_PCI ) {
		/* PCI adapter does not need DMA wait state */
		usc_OutDmaReg( info, DCR, 0xa00b );
	}
	else
		usc_OutDmaReg( info, DCR, 0x800b );


	/* Receive DMA mode Register (RDMR)
	 *
	 * <15..14>	11	DMA mode = Linked List Buffer mode
	 * <13>		1	RSBinA/L = store Rx status Block in Arrary/List entry
	 * <12>		1	Clear count of List Entry after fetching
	 * <11..10>	00	Address mode = Increment
	 * <9>		1	Terminate Buffer on RxBound
	 * <8>		0	Bus Width = 16bits
	 * <7..0>	?	status Bits (write as 0s)
	 *
	 * 1111 0010 0000 0000 = 0xf200
	 */

	usc_OutDmaReg( info, RDMR, 0xf200 );


	/* Transmit DMA mode Register (TDMR)
	 *
	 * <15..14>	11	DMA mode = Linked List Buffer mode
	 * <13>		1	TCBinA/L = fetch Tx Control Block from List entry
	 * <12>		1	Clear count of List Entry after fetching
	 * <11..10>	00	Address mode = Increment
	 * <9>		1	Terminate Buffer on end of frame
	 * <8>		0	Bus Width = 16bits
	 * <7..0>	?	status Bits (Read Only so write as 0)
	 *
	 *	1111 0010 0000 0000 = 0xf200
	 */

	usc_OutDmaReg( info, TDMR, 0xf200 );


	/* DMA Interrupt Control Register (DICR)
	 *
	 * <15>		1	DMA Interrupt Enable
	 * <14>		0	1 = Disable IEO from USC
	 * <13>		0	1 = Don't provide vector during IntAck
	 * <12>		1	1 = Include status in Vector
	 * <10..2>	0	reserved, Must be 0s
	 * <1>		0	1 = Rx DMA Interrupt Enabled
	 * <0>		0	1 = Tx DMA Interrupt Enabled
	 *
	 *	1001 0000 0000 0000 = 0x9000
	 */

	usc_OutDmaReg( info, DICR, 0x9000 );

	usc_InDmaReg( info, RDMR );		/* clear pending receive DMA IRQ bits */
	usc_InDmaReg( info, TDMR );		/* clear pending transmit DMA IRQ bits */
	usc_OutDmaReg( info, CDIR, 0x0303 );	/* clear IUS and Pending for Tx and Rx */

	/* Channel Control Register (CCR)
	 *
	 * <15..14>	10	Use 32-bit Tx Control Blocks (TCBs)
	 * <13>		0	Trigger Tx on SW Command Disabled
	 * <12>		0	Flag Preamble Disabled
	 * <11..10>	00	Preamble Length
	 * <9..8>	00	Preamble Pattern
	 * <7..6>	10	Use 32-bit Rx status Blocks (RSBs)
	 * <5>		0	Trigger Rx on SW Command Disabled
	 * <4..0>	0	reserved
	 *
	 *	1000 0000 1000 0000 = 0x8080
	 */

	RegValue = 0x8080;

	switch ( info->params.preamble_length ) {
	case HDLC_PREAMBLE_LENGTH_16BITS: RegValue |= BIT10; break;
	case HDLC_PREAMBLE_LENGTH_32BITS: RegValue |= BIT11; break;
	case HDLC_PREAMBLE_LENGTH_64BITS: RegValue |= BIT11 + BIT10; break;
	}

	switch ( info->params.preamble ) {
	case HDLC_PREAMBLE_PATTERN_FLAGS: RegValue |= BIT8 + BIT12; break;
	case HDLC_PREAMBLE_PATTERN_ONES:  RegValue |= BIT8; break;
	case HDLC_PREAMBLE_PATTERN_10:    RegValue |= BIT9; break;
	case HDLC_PREAMBLE_PATTERN_01:    RegValue |= BIT9 + BIT8; break;
	}

	usc_OutReg( info, CCR, RegValue );


	/*
	 * Burst/Dwell Control Register
	 *
	 * <15..8>	0x20	Maximum number of transfers per bus grant
	 * <7..0>	0x00	Maximum number of clock cycles per bus grant
	 */

	if ( info->bus_type == MGSL_BUS_TYPE_PCI ) {
		/* don't limit bus occupancy on PCI adapter */
		usc_OutDmaReg( info, BDCR, 0x0000 );
	}
	else
		usc_OutDmaReg( info, BDCR, 0x2000 );

	usc_stop_transmitter(info);
	usc_stop_receiver(info);
	
}