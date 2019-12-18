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
struct zilog_channel {int /*<<< orphan*/  control; } ;

/* Variables and functions */
 unsigned char ALL_SNT ; 
 unsigned char BRENAB ; 
 int /*<<< orphan*/  ERR_RES ; 
 unsigned char EXT_INT_ENAB ; 
 size_t R0 ; 
 size_t R1 ; 
 size_t R10 ; 
 size_t R11 ; 
 size_t R12 ; 
 size_t R13 ; 
 size_t R14 ; 
 size_t R15 ; 
 size_t R3 ; 
 size_t R4 ; 
 size_t R5 ; 
 size_t R6 ; 
 size_t R7 ; 
 unsigned char RES_EXT_INT ; 
 unsigned char RxENAB ; 
 unsigned char RxINT_MASK ; 
 unsigned char TxENAB ; 
 unsigned char TxINT_ENAB ; 
 int /*<<< orphan*/  ZSDELAY () ; 
 int /*<<< orphan*/  ZS_WSYNC (struct zilog_channel*) ; 
 int /*<<< orphan*/  ip22zilog_clear_fifo (struct zilog_channel*) ; 
 unsigned char read_zsreg (struct zilog_channel*,size_t) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_zsreg (struct zilog_channel*,size_t,unsigned char) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __load_zsregs(struct zilog_channel *channel, unsigned char *regs)
{
	int i;

	/* Let pending transmits finish.  */
	for (i = 0; i < 1000; i++) {
		unsigned char stat = read_zsreg(channel, R1);
		if (stat & ALL_SNT)
			break;
		udelay(100);
	}

	writeb(ERR_RES, &channel->control);
	ZSDELAY();
	ZS_WSYNC(channel);

	ip22zilog_clear_fifo(channel);

	/* Disable all interrupts.  */
	write_zsreg(channel, R1,
		    regs[R1] & ~(RxINT_MASK | TxINT_ENAB | EXT_INT_ENAB));

	/* Set parity, sync config, stop bits, and clock divisor.  */
	write_zsreg(channel, R4, regs[R4]);

	/* Set misc. TX/RX control bits.  */
	write_zsreg(channel, R10, regs[R10]);

	/* Set TX/RX controls sans the enable bits.  */
	write_zsreg(channel, R3, regs[R3] & ~RxENAB);
	write_zsreg(channel, R5, regs[R5] & ~TxENAB);

	/* Synchronous mode config.  */
	write_zsreg(channel, R6, regs[R6]);
	write_zsreg(channel, R7, regs[R7]);

	/* Don't mess with the interrupt vector (R2, unused by us) and
	 * master interrupt control (R9).  We make sure this is setup
	 * properly at probe time then never touch it again.
	 */

	/* Disable baud generator.  */
	write_zsreg(channel, R14, regs[R14] & ~BRENAB);

	/* Clock mode control.  */
	write_zsreg(channel, R11, regs[R11]);

	/* Lower and upper byte of baud rate generator divisor.  */
	write_zsreg(channel, R12, regs[R12]);
	write_zsreg(channel, R13, regs[R13]);

	/* Now rewrite R14, with BRENAB (if set).  */
	write_zsreg(channel, R14, regs[R14]);

	/* External status interrupt control.  */
	write_zsreg(channel, R15, regs[R15]);

	/* Reset external status interrupts.  */
	write_zsreg(channel, R0, RES_EXT_INT);
	write_zsreg(channel, R0, RES_EXT_INT);

	/* Rewrite R3/R5, this time without enables masked.  */
	write_zsreg(channel, R3, regs[R3]);
	write_zsreg(channel, R5, regs[R5]);

	/* Rewrite R1, this time without IRQ enabled masked.  */
	write_zsreg(channel, R1, regs[R1]);
}