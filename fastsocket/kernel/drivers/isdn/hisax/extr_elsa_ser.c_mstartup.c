#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int MCR; int IER; int MFlag; scalar_t__ rcvp; scalar_t__ rcvcnt; scalar_t__ transp; scalar_t__ transcnt; } ;
struct TYPE_4__ {TYPE_1__ elsa; } ;
struct IsdnCardState {TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  BASE_BAUD ; 
 int ENODEV ; 
 int /*<<< orphan*/  UART_FCR ; 
 int UART_FCR_CLEAR_RCVR ; 
 int UART_FCR_CLEAR_XMIT ; 
 int /*<<< orphan*/  UART_IER ; 
 int UART_IER_MSI ; 
 int UART_IER_RDI ; 
 int UART_IER_RLSI ; 
 int /*<<< orphan*/  UART_IIR ; 
 int /*<<< orphan*/  UART_LCR ; 
 int UART_LCR_WLEN8 ; 
 int /*<<< orphan*/  UART_LSR ; 
 int /*<<< orphan*/  UART_MCR ; 
 int UART_MCR_DTR ; 
 int UART_MCR_OUT2 ; 
 int UART_MCR_RTS ; 
 int /*<<< orphan*/  UART_MSR ; 
 int /*<<< orphan*/  UART_RX ; 
 int /*<<< orphan*/  change_speed (struct IsdnCardState*,int /*<<< orphan*/ ) ; 
 int serial_inp (struct IsdnCardState*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_outp (struct IsdnCardState*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mstartup(struct IsdnCardState *cs)
{
	int	retval=0;

	/*
	 * Clear the FIFO buffers and disable them
	 * (they will be reenabled in change_speed())
	 */
	serial_outp(cs, UART_FCR, (UART_FCR_CLEAR_RCVR | UART_FCR_CLEAR_XMIT));

	/*
	 * At this point there's no way the LSR could still be 0xFF;
	 * if it is, then bail out, because there's likely no UART
	 * here.
	 */
	if (serial_inp(cs, UART_LSR) == 0xff) {
		retval = -ENODEV;
		goto errout;
	}
	
	/*
	 * Clear the interrupt registers.
	 */
	(void) serial_inp(cs, UART_RX);
	(void) serial_inp(cs, UART_IIR);
	(void) serial_inp(cs, UART_MSR);

	/*
	 * Now, initialize the UART 
	 */
	serial_outp(cs, UART_LCR, UART_LCR_WLEN8);	/* reset DLAB */

	cs->hw.elsa.MCR = 0;
	cs->hw.elsa.MCR = UART_MCR_DTR | UART_MCR_RTS | UART_MCR_OUT2;
	serial_outp(cs, UART_MCR, cs->hw.elsa.MCR);
	
	/*
	 * Finally, enable interrupts
	 */
	cs->hw.elsa.IER = UART_IER_MSI | UART_IER_RLSI | UART_IER_RDI;
	serial_outp(cs, UART_IER, cs->hw.elsa.IER);	/* enable interrupts */
	
	/*
	 * And clear the interrupt registers again for luck.
	 */
	(void)serial_inp(cs, UART_LSR);
	(void)serial_inp(cs, UART_RX);
	(void)serial_inp(cs, UART_IIR);
	(void)serial_inp(cs, UART_MSR);

	cs->hw.elsa.transcnt = cs->hw.elsa.transp = 0;
	cs->hw.elsa.rcvcnt = cs->hw.elsa.rcvp =0;

	/*
	 * and set the speed of the serial port
	 */
	change_speed(cs, BASE_BAUD);
	cs->hw.elsa.MFlag = 1;
errout:
	return retval;
}