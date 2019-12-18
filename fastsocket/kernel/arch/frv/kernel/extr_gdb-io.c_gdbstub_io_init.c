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
typedef  int __UART ;

/* Variables and functions */
 int /*<<< orphan*/  DTR ; 
 int /*<<< orphan*/  FLOWCTL_CLEAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLOWCTL_SET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTS ; 
 int UART_FCR_CLEAR_RCVR ; 
 int UART_FCR_CLEAR_XMIT ; 
 int UART_FCR_ENABLE_FIFO ; 
 int UART_FCR_TRIGGER_1 ; 
 int UART_IER_RDI ; 
 int UART_IER_RLSI ; 
 int UART_LCR_WLEN8 ; 
 int /*<<< orphan*/  __UART_IRR_NMI ; 
 int /*<<< orphan*/  __set_IRR (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 

void gdbstub_io_init(void)
{
	/* set up the serial port */
	__UART(LCR) = UART_LCR_WLEN8; /* 1N8 */
	__UART(FCR) =
		UART_FCR_ENABLE_FIFO |
		UART_FCR_CLEAR_RCVR |
		UART_FCR_CLEAR_XMIT |
		UART_FCR_TRIGGER_1;

	FLOWCTL_CLEAR(DTR);
	FLOWCTL_SET(RTS);

//	gdbstub_set_baud(115200);

	/* we want to get serial receive interrupts */
	__UART(IER) = UART_IER_RDI | UART_IER_RLSI;
	mb();

	__set_IRR(6, __UART_IRR_NMI);	/* map ERRs and UARTx to NMI */

}