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
struct TYPE_2__ {int /*<<< orphan*/  (* uart_set_baud_rate ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FCR ; 
 int /*<<< orphan*/  IER ; 
 int /*<<< orphan*/  IO_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IO_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LCR ; 
 int /*<<< orphan*/  MCR ; 
 int /*<<< orphan*/  RBR ; 
 int UART_LCR_8BITS ; 
 int UART_MCR_DTR ; 
 int UART_MCR_RTS ; 
 TYPE_1__* gPESF ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_baud_rate ; 
 int uart_initted ; 

__attribute__((used)) static void
legacy_uart_init( void )
{
    /* Disable hardware interrupts */

    IO_WRITE( MCR, 0 );
    IO_WRITE( IER, 0 );

    /* Disable FIFO's for 16550 devices */

    IO_WRITE( FCR, 0 );

    /* Set for 8-bit, no parity, DLAB bit cleared */

    IO_WRITE( LCR, UART_LCR_8BITS );

    /* Set baud rate */

    gPESF->uart_set_baud_rate ( 0, uart_baud_rate );

    /* Assert DTR# and RTS# lines (OUT2?) */

    IO_WRITE( MCR, UART_MCR_DTR | UART_MCR_RTS );

    /* Clear any garbage in the input buffer */

    IO_READ( RBR );

    uart_initted = 1;
}