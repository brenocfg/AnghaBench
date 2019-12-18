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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLK ; 
 int /*<<< orphan*/  DLL ; 
 int /*<<< orphan*/  DLM ; 
 int /*<<< orphan*/  FCR ; 
 int /*<<< orphan*/  LCR ; 
 int /*<<< orphan*/  MCR ; 
 int /*<<< orphan*/  MMIO_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMIO_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RST ; 
 int UART_CLK_125M_1 ; 
 int UART_CLK_125M_2 ; 
 int UART_LCR_8BITS ; 
 int UART_LCR_DLAB ; 
 int UART_MCR_RTS ; 

__attribute__((used)) static void lpss_uart_re_init( void )
{
	uint32_t register_read;
	
	MMIO_WRITE (RST, 0x7);				/* LPSS UART2 controller out ot reset */
	register_read = MMIO_READ (RST);

	MMIO_WRITE (LCR, UART_LCR_DLAB);	/* Set DLAB bit to enable reading/writing of DLL, DLH */
	register_read = MMIO_READ (LCR);

	MMIO_WRITE (DLL, 1);				/* Divisor Latch Low Register */
	register_read = MMIO_READ (DLL);

	MMIO_WRITE (DLM, 0);				/* Divisor Latch High Register */
	register_read = MMIO_READ (DLM);

	MMIO_WRITE (FCR, 1);				/* Enable FIFO */
	register_read = MMIO_READ (FCR);

	MMIO_WRITE (LCR, UART_LCR_8BITS);	/* Set 8 bits, clear DLAB */
	register_read = MMIO_READ (LCR);

	MMIO_WRITE (MCR, UART_MCR_RTS);		/* Request to send */
	register_read = MMIO_READ (MCR);

	MMIO_WRITE (CLK, UART_CLK_125M_1);	/* 1.25M Clock speed */
	register_read = MMIO_READ (CLK);

	MMIO_WRITE (CLK, UART_CLK_125M_2);	/* 1.25M Clock speed */
	register_read = MMIO_READ (CLK);	
}