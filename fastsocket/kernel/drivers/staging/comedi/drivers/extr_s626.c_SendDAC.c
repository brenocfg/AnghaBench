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
typedef  int /*<<< orphan*/  uint32_t ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * pDacWBuf; int /*<<< orphan*/  Dacpol; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBIwrite (struct comedi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EOS ; 
 int /*<<< orphan*/  ISR_AFOU ; 
 int /*<<< orphan*/  LP_DACPOL ; 
 int MC1_A2OUT ; 
 int /*<<< orphan*/  MC_ENABLE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  P_FB_BUFFER2 ; 
 int /*<<< orphan*/  P_ISR ; 
 int /*<<< orphan*/  P_MC1 ; 
 int /*<<< orphan*/  P_SSR ; 
 int RR7146 (int /*<<< orphan*/ ) ; 
 int RSD2 ; 
 int RSD3 ; 
 int /*<<< orphan*/  SETVECT (int /*<<< orphan*/ ,int) ; 
 int SIB_A2 ; 
 int SSR_AF2_OUT ; 
 int /*<<< orphan*/  WR7146 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int XFIFO_2 ; 
 int XSD2 ; 
 TYPE_1__* devpriv ; 

__attribute__((used)) static void SendDAC(struct comedi_device *dev, uint32_t val)
{

	/* START THE SERIAL CLOCK RUNNING ------------- */

	/* Assert DAC polarity control and enable gating of DAC serial clock
	 * and audio bit stream signals.  At this point in time we must be
	 * assured of being in time slot 0.  If we are not in slot 0, the
	 * serial clock and audio stream signals will be disabled; this is
	 * because the following DEBIwrite statement (which enables signals
	 * to be passed through the gate array) would execute before the
	 * trailing edge of WS1/WS3 (which turns off the signals), thus
	 * causing the signals to be inactive during the DAC write.
	 */
	DEBIwrite(dev, LP_DACPOL, devpriv->Dacpol);

	/* TRANSFER OUTPUT DWORD VALUE INTO A2'S OUTPUT FIFO ---------------- */

	/* Copy DAC setpoint value to DAC's output DMA buffer. */

	/* WR7146( (uint32_t)devpriv->pDacWBuf, val ); */
	*devpriv->pDacWBuf = val;

	/* enab the output DMA transfer.  This will cause the DMAC to copy
	 * the DAC's data value to A2's output FIFO.  The DMA transfer will
	 * then immediately terminate because the protection address is
	 * reached upon transfer of the first DWORD value.
	 */
	MC_ENABLE(P_MC1, MC1_A2OUT);

	/*  While the DMA transfer is executing ... */

	/* Reset Audio2 output FIFO's underflow flag (along with any other
	 * FIFO underflow/overflow flags).  When set, this flag will
	 * indicate that we have emerged from slot 0.
	 */
	WR7146(P_ISR, ISR_AFOU);

	/* Wait for the DMA transfer to finish so that there will be data
	 * available in the FIFO when time slot 1 tries to transfer a DWORD
	 * from the FIFO to the output buffer register.  We test for DMA
	 * Done by polling the DMAC enable flag; this flag is automatically
	 * cleared when the transfer has finished.
	 */
	while ((RR7146(P_MC1) & MC1_A2OUT) != 0) ;

	/* START THE OUTPUT STREAM TO THE TARGET DAC -------------------- */

	/* FIFO data is now available, so we enable execution of time slots
	 * 1 and higher by clearing the EOS flag in slot 0.  Note that SD3
	 * will be shifted in and stored in FB_BUFFER2 for end-of-slot-list
	 * detection.
	 */
	SETVECT(0, XSD2 | RSD3 | SIB_A2);

	/* Wait for slot 1 to execute to ensure that the Packet will be
	 * transmitted.  This is detected by polling the Audio2 output FIFO
	 * underflow flag, which will be set when slot 1 execution has
	 * finished transferring the DAC's data DWORD from the output FIFO
	 * to the output buffer register.
	 */
	while ((RR7146(P_SSR) & SSR_AF2_OUT) == 0) ;

	/* Set up to trap execution at slot 0 when the TSL sequencer cycles
	 * back to slot 0 after executing the EOS in slot 5.  Also,
	 * simultaneously shift out and in the 0x00 that is ALWAYS the value
	 * stored in the last byte to be shifted out of the FIFO's DWORD
	 * buffer register.
	 */
	SETVECT(0, XSD2 | XFIFO_2 | RSD2 | SIB_A2 | EOS);

	/* WAIT FOR THE TRANSACTION TO FINISH ----------------------- */

	/* Wait for the TSL to finish executing all time slots before
	 * exiting this function.  We must do this so that the next DAC
	 * write doesn't start, thereby enabling clock/chip select signals:
	 *
	 * 1. Before the TSL sequence cycles back to slot 0, which disables
	 *    the clock/cs signal gating and traps slot // list execution.
	 *    we have not yet finished slot 5 then the clock/cs signals are
	 *    still gated and we have not finished transmitting the stream.
	 *
	 * 2. While slots 2-5 are executing due to a late slot 0 trap.  In
	 *    this case, the slot sequence is currently repeating, but with
	 *    clock/cs signals disabled.  We must wait for slot 0 to trap
	 *    execution before setting up the next DAC setpoint DMA transfer
	 *    and enabling the clock/cs signals.  To detect the end of slot 5,
	 *    we test for the FB_BUFFER2 MSB contents to be equal to 0xFF.  If
	 *    the TSL has not yet finished executing slot 5 ...
	 */
	if ((RR7146(P_FB_BUFFER2) & 0xFF000000) != 0) {
		/* The trap was set on time and we are still executing somewhere
		 * in slots 2-5, so we now wait for slot 0 to execute and trap
		 * TSL execution.  This is detected when FB_BUFFER2 MSB changes
		 * from 0xFF to 0x00, which slot 0 causes to happen by shifting
		 * out/in on SD2 the 0x00 that is always referenced by slot 5.
		 */
		while ((RR7146(P_FB_BUFFER2) & 0xFF000000) != 0) ;
	}
	/* Either (1) we were too late setting the slot 0 trap; the TSL
	 * sequencer restarted slot 0 before we could set the EOS trap flag,
	 * or (2) we were not late and execution is now trapped at slot 0.
	 * In either case, we must now change slot 0 so that it will store
	 * value 0xFF (instead of 0x00) to FB_BUFFER2 next time it executes.
	 * In order to do this, we reprogram slot 0 so that it will shift in
	 * SD3, which is driven only by a pull-up resistor.
	 */
	SETVECT(0, RSD3 | SIB_A2 | EOS);

	/* Wait for slot 0 to execute, at which time the TSL is setup for
	 * the next DAC write.  This is detected when FB_BUFFER2 MSB changes
	 * from 0x00 to 0xFF.
	 */
	while ((RR7146(P_FB_BUFFER2) & 0xFF000000) == 0) ;
}