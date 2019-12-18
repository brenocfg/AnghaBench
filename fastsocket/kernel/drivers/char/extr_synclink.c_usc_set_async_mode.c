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
typedef  int u16 ;
struct TYPE_2__ {int stop_bits; int data_bits; scalar_t__ parity; scalar_t__ loopback; int /*<<< orphan*/  data_rate; } ;
struct mgsl_struct {scalar_t__ bus_type; int loopback_bits; scalar_t__ io_base; TYPE_1__ params; } ;

/* Variables and functions */
 scalar_t__ ASYNC_PARITY_NONE ; 
 scalar_t__ ASYNC_PARITY_ODD ; 
 int BIT12 ; 
 int BIT13 ; 
 int BIT14 ; 
 int BIT2 ; 
 int BIT3 ; 
 int BIT4 ; 
 int BIT5 ; 
 int BIT6 ; 
 scalar_t__ CCAR ; 
 int /*<<< orphan*/  CCSR ; 
 int /*<<< orphan*/  CMR ; 
 int /*<<< orphan*/  DmaCmd_ResetAllChannels ; 
 scalar_t__ MGSL_BUS_TYPE_ISA ; 
 int /*<<< orphan*/  PCR ; 
 int /*<<< orphan*/  RCmd_SelectRicrIntLevel ; 
 scalar_t__ RECEIVE_DATA ; 
 scalar_t__ RECEIVE_STATUS ; 
 int /*<<< orphan*/  RICR ; 
 int /*<<< orphan*/  RMR ; 
 int /*<<< orphan*/  RXSTATUS_ALL ; 
 int /*<<< orphan*/  TCmd_SelectTicrIntLevel ; 
 int /*<<< orphan*/  TICR ; 
 int /*<<< orphan*/  TMR ; 
 scalar_t__ TRANSMIT_DATA ; 
 scalar_t__ TRANSMIT_STATUS ; 
 int /*<<< orphan*/  TXSTATUS_ALL ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 
 int /*<<< orphan*/  usc_ClearIrqPendingBits (struct mgsl_struct*,scalar_t__) ; 
 int /*<<< orphan*/  usc_DisableInterrupts (struct mgsl_struct*,scalar_t__) ; 
 int /*<<< orphan*/  usc_DisableMasterIrqBit (struct mgsl_struct*) ; 
 int /*<<< orphan*/  usc_DmaCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_EnableMasterIrqBit (struct mgsl_struct*) ; 
 int usc_InReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_OutReg (struct mgsl_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usc_RCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_TCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_UnlatchRxstatusBits (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_UnlatchTxstatusBits (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_enable_async_clock (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_loopback_frame (struct mgsl_struct*) ; 
 int /*<<< orphan*/  usc_set_txidle (struct mgsl_struct*) ; 

__attribute__((used)) static void usc_set_async_mode( struct mgsl_struct *info )
{
	u16 RegValue;

	/* disable interrupts while programming USC */
	usc_DisableMasterIrqBit( info );

	outw( 0, info->io_base ); 			/* clear Master Bus Enable (DCAR) */
	usc_DmaCmd( info, DmaCmd_ResetAllChannels );	/* disable both DMA channels */

	usc_loopback_frame( info );

	/* Channel mode Register (CMR)
	 *
	 * <15..14>	00	Tx Sub modes, 00 = 1 Stop Bit
	 * <13..12>	00	              00 = 16X Clock
	 * <11..8>	0000	Transmitter mode = Asynchronous
	 * <7..6>	00	reserved?
	 * <5..4>	00	Rx Sub modes, 00 = 16X Clock
	 * <3..0>	0000	Receiver mode = Asynchronous
	 *
	 * 0000 0000 0000 0000 = 0x0
	 */

	RegValue = 0;
	if ( info->params.stop_bits != 1 )
		RegValue |= BIT14;
	usc_OutReg( info, CMR, RegValue );

	
	/* Receiver mode Register (RMR)
	 *
	 * <15..13>	000	encoding = None
	 * <12..08>	00000	reserved (Sync Only)
	 * <7..6>   	00	Even parity
	 * <5>		0	parity disabled
	 * <4..2>	000	Receive Char Length = 8 bits
	 * <1..0>	00	Disable Receiver
	 *
	 * 0000 0000 0000 0000 = 0x0
	 */

	RegValue = 0;

	if ( info->params.data_bits != 8 )
		RegValue |= BIT4+BIT3+BIT2;

	if ( info->params.parity != ASYNC_PARITY_NONE ) {
		RegValue |= BIT5;
		if ( info->params.parity != ASYNC_PARITY_ODD )
			RegValue |= BIT6;
	}

	usc_OutReg( info, RMR, RegValue );


	/* Set IRQ trigger level */

	usc_RCmd( info, RCmd_SelectRicrIntLevel );

	
	/* Receive Interrupt Control Register (RICR)
	 *
	 * <15..8>	?		RxFIFO IRQ Request Level
	 *
	 * Note: For async mode the receive FIFO level must be set
	 * to 0 to avoid the situation where the FIFO contains fewer bytes
	 * than the trigger level and no more data is expected.
	 *
	 * <7>		0		Exited Hunt IA (Interrupt Arm)
	 * <6>		0		Idle Received IA
	 * <5>		0		Break/Abort IA
	 * <4>		0		Rx Bound IA
	 * <3>		0		Queued status reflects oldest byte in FIFO
	 * <2>		0		Abort/PE IA
	 * <1>		0		Rx Overrun IA
	 * <0>		0		Select TC0 value for readback
	 *
	 * 0000 0000 0100 0000 = 0x0000 + (FIFOLEVEL in MSB)
	 */
	
	usc_OutReg( info, RICR, 0x0000 );

	usc_UnlatchRxstatusBits( info, RXSTATUS_ALL );
	usc_ClearIrqPendingBits( info, RECEIVE_STATUS );

	
	/* Transmit mode Register (TMR)
	 *
	 * <15..13>	000	encoding = None
	 * <12..08>	00000	reserved (Sync Only)
	 * <7..6>	00	Transmit parity Even
	 * <5>		0	Transmit parity Disabled
	 * <4..2>	000	Tx Char Length = 8 bits
	 * <1..0>	00	Disable Transmitter
	 *
	 * 0000 0000 0000 0000 = 0x0
	 */

	RegValue = 0;

	if ( info->params.data_bits != 8 )
		RegValue |= BIT4+BIT3+BIT2;

	if ( info->params.parity != ASYNC_PARITY_NONE ) {
		RegValue |= BIT5;
		if ( info->params.parity != ASYNC_PARITY_ODD )
			RegValue |= BIT6;
	}

	usc_OutReg( info, TMR, RegValue );

	usc_set_txidle( info );


	/* Set IRQ trigger level */

	usc_TCmd( info, TCmd_SelectTicrIntLevel );

	
	/* Transmit Interrupt Control Register (TICR)
	 *
	 * <15..8>	?	Transmit FIFO IRQ Level
	 * <7>		0	Present IA (Interrupt Arm)
	 * <6>		1	Idle Sent IA
	 * <5>		0	Abort Sent IA
	 * <4>		0	EOF/EOM Sent IA
	 * <3>		0	CRC Sent IA
	 * <2>		0	1 = Wait for SW Trigger to Start Frame
	 * <1>		0	Tx Underrun IA
	 * <0>		0	TC0 constant on read back
	 *
	 *	0000 0000 0100 0000 = 0x0040
	 */

	usc_OutReg( info, TICR, 0x1f40 );

	usc_UnlatchTxstatusBits( info, TXSTATUS_ALL );
	usc_ClearIrqPendingBits( info, TRANSMIT_STATUS );

	usc_enable_async_clock( info, info->params.data_rate );

	
	/* Channel Control/status Register (CCSR)
	 *
	 * <15>		X	RCC FIFO Overflow status (RO)
	 * <14>		X	RCC FIFO Not Empty status (RO)
	 * <13>		0	1 = Clear RCC FIFO (WO)
	 * <12>		X	DPLL in Sync status (RO)
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
	
	usc_OutReg( info, CCSR, 0x0020 );

	usc_DisableInterrupts( info, TRANSMIT_STATUS + TRANSMIT_DATA +
			      RECEIVE_DATA + RECEIVE_STATUS );

	usc_ClearIrqPendingBits( info, TRANSMIT_STATUS + TRANSMIT_DATA +
				RECEIVE_DATA + RECEIVE_STATUS );

	usc_EnableMasterIrqBit( info );

	if (info->bus_type == MGSL_BUS_TYPE_ISA) {
		/* Enable INTEN (Port 6, Bit12) */
		/* This connects the IRQ request signal to the ISA bus */
		usc_OutReg(info, PCR, (u16)((usc_InReg(info, PCR) | BIT13) & ~BIT12));
	}

	if (info->params.loopback) {
		info->loopback_bits = 0x300;
		outw(0x0300, info->io_base + CCAR);
	}

}