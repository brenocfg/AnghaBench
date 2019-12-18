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
struct TYPE_2__ {unsigned long mode; } ;
struct mgsl_struct {TYPE_1__ params; scalar_t__ io_base; } ;

/* Variables and functions */
 int BIT1 ; 
 int BIT3 ; 
 int BIT4 ; 
 int BIT8 ; 
 int /*<<< orphan*/  CCR ; 
 scalar_t__ DATAREG ; 
 int /*<<< orphan*/  ENABLE_UNCONDITIONAL ; 
 unsigned long MGSL_MODE_HDLC ; 
 int /*<<< orphan*/  RCSR ; 
 int /*<<< orphan*/  RTCmd_PurgeRxFifo ; 
 int /*<<< orphan*/  RTCmd_PurgeTxFifo ; 
 int /*<<< orphan*/  TC0R ; 
 int /*<<< orphan*/  TCLR ; 
 int /*<<< orphan*/  TCmd_SendFrame ; 
 int /*<<< orphan*/  TXSTATUS_ALL ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  usc_DisableMasterIrqBit (struct mgsl_struct*) ; 
 int /*<<< orphan*/  usc_EnableMasterIrqBit (struct mgsl_struct*) ; 
 int /*<<< orphan*/  usc_EnableReceiver (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_EnableTransmitter (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int usc_InReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_OutReg (struct mgsl_struct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usc_RTCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_TCmd (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_UnlatchTxstatusBits (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_enable_loopback (struct mgsl_struct*,int) ; 
 int /*<<< orphan*/  usc_set_sdlc_mode (struct mgsl_struct*) ; 

__attribute__((used)) static void usc_loopback_frame( struct mgsl_struct *info )
{
	int i;
	unsigned long oldmode = info->params.mode;

	info->params.mode = MGSL_MODE_HDLC;
	
	usc_DisableMasterIrqBit( info );

	usc_set_sdlc_mode( info );
	usc_enable_loopback( info, 1 );

	/* Write 16-bit Time Constant for BRG0 */
	usc_OutReg( info, TC0R, 0 );
	
	/* Channel Control Register (CCR)
	 *
	 * <15..14>	00	Don't use 32-bit Tx Control Blocks (TCBs)
	 * <13>		0	Trigger Tx on SW Command Disabled
	 * <12>		0	Flag Preamble Disabled
	 * <11..10>	00	Preamble Length = 8-Bits
	 * <9..8>	01	Preamble Pattern = flags
	 * <7..6>	10	Don't use 32-bit Rx status Blocks (RSBs)
	 * <5>		0	Trigger Rx on SW Command Disabled
	 * <4..0>	0	reserved
	 *
	 *	0000 0001 0000 0000 = 0x0100
	 */

	usc_OutReg( info, CCR, 0x0100 );

	/* SETUP RECEIVER */
	usc_RTCmd( info, RTCmd_PurgeRxFifo );
	usc_EnableReceiver(info,ENABLE_UNCONDITIONAL);

	/* SETUP TRANSMITTER */
	/* Program the Transmit Character Length Register (TCLR) */
	/* and clear FIFO (TCC is loaded with TCLR on FIFO clear) */
	usc_OutReg( info, TCLR, 2 );
	usc_RTCmd( info, RTCmd_PurgeTxFifo );

	/* unlatch Tx status bits, and start transmit channel. */
	usc_UnlatchTxstatusBits(info,TXSTATUS_ALL);
	outw(0,info->io_base + DATAREG);

	/* ENABLE TRANSMITTER */
	usc_TCmd( info, TCmd_SendFrame );
	usc_EnableTransmitter(info,ENABLE_UNCONDITIONAL);
							
	/* WAIT FOR RECEIVE COMPLETE */
	for (i=0 ; i<1000 ; i++)
		if (usc_InReg( info, RCSR ) & (BIT8 + BIT4 + BIT3 + BIT1))
			break;

	/* clear Internal Data loopback mode */
	usc_enable_loopback(info, 0);

	usc_EnableMasterIrqBit(info);

	info->params.mode = oldmode;

}