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

/* Variables and functions */
 unsigned int AVR_QUOT (int /*<<< orphan*/ ) ; 
 scalar_t__ UART_DLL ; 
 scalar_t__ UART_DLM ; 
 scalar_t__ UART_FCR ; 
 unsigned char UART_FCR_ENABLE_FIFO ; 
 scalar_t__ UART_IER ; 
 scalar_t__ UART_LCR ; 
 unsigned char UART_LCR_DLAB ; 
 unsigned char UART_LCR_EPAR ; 
 unsigned char UART_LCR_PARITY ; 
 unsigned char UART_LCR_STOP ; 
 unsigned char UART_LCR_WLEN8 ; 
 scalar_t__ UART_MCR ; 
 scalar_t__ avr_addr ; 
 int /*<<< orphan*/  avr_clock ; 
 int /*<<< orphan*/  out_8 (scalar_t__,unsigned char) ; 

void avr_uart_configure(void)
{
	unsigned char cval = UART_LCR_WLEN8;
	unsigned int quot = AVR_QUOT(avr_clock);

	if (!avr_addr || !avr_clock)
		return;

	out_8(avr_addr + UART_LCR, cval);			/* initialise UART */
	out_8(avr_addr + UART_MCR, 0);
	out_8(avr_addr + UART_IER, 0);

	cval |= UART_LCR_STOP | UART_LCR_PARITY | UART_LCR_EPAR;

	out_8(avr_addr + UART_LCR, cval);			/* Set character format */

	out_8(avr_addr + UART_LCR, cval | UART_LCR_DLAB);	/* set DLAB */
	out_8(avr_addr + UART_DLL, quot & 0xff);		/* LS of divisor */
	out_8(avr_addr + UART_DLM, quot >> 8);			/* MS of divisor */
	out_8(avr_addr + UART_LCR, cval);			/* reset DLAB */
	out_8(avr_addr + UART_FCR, UART_FCR_ENABLE_FIFO);	/* enable FIFO */
}