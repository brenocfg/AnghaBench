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
struct TYPE_3__ {unsigned int IER; } ;
struct TYPE_4__ {TYPE_1__ elsa; } ;
struct IsdnCardState {TYPE_2__ hw; } ;

/* Variables and functions */
 int BASE_BAUD ; 
 int /*<<< orphan*/  UART_DLL ; 
 int /*<<< orphan*/  UART_DLM ; 
 int /*<<< orphan*/  UART_FCR ; 
 unsigned int UART_FCR_ENABLE_FIFO ; 
 unsigned int UART_FCR_TRIGGER_1 ; 
 unsigned int UART_FCR_TRIGGER_8 ; 
 int /*<<< orphan*/  UART_IER ; 
 unsigned int UART_IER_MSI ; 
 int /*<<< orphan*/  UART_LCR ; 
 unsigned int UART_LCR_DLAB ; 
 int /*<<< orphan*/  UART_RX ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,int) ; 
 int /*<<< orphan*/  serial_inp (struct IsdnCardState*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_outp (struct IsdnCardState*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void change_speed(struct IsdnCardState *cs, int baud)
{
	int	quot = 0, baud_base;
	unsigned cval, fcr = 0;
	int	bits;


	/* byte size and parity */
	cval = 0x03; bits = 10;
	/* Determine divisor based on baud rate */
	baud_base = BASE_BAUD;
	quot = baud_base / baud;
	/* If the quotient is ever zero, default to 9600 bps */
	if (!quot)
		quot = baud_base / 9600;

	/* Set up FIFO's */
	if ((baud_base / quot) < 2400)
		fcr = UART_FCR_ENABLE_FIFO | UART_FCR_TRIGGER_1;
	else
		fcr = UART_FCR_ENABLE_FIFO | UART_FCR_TRIGGER_8;
	serial_outp(cs, UART_FCR, fcr);
	/* CTS flow control flag and modem status interrupts */
	cs->hw.elsa.IER &= ~UART_IER_MSI;
	cs->hw.elsa.IER |= UART_IER_MSI;
	serial_outp(cs, UART_IER, cs->hw.elsa.IER);

	debugl1(cs,"modem quot=0x%x", quot);
	serial_outp(cs, UART_LCR, cval | UART_LCR_DLAB);/* set DLAB */
	serial_outp(cs, UART_DLL, quot & 0xff);		/* LS of divisor */
	serial_outp(cs, UART_DLM, quot >> 8);		/* MS of divisor */
	serial_outp(cs, UART_LCR, cval);		/* reset DLAB */
	serial_inp(cs, UART_RX);
}