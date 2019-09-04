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
 int /*<<< orphan*/  LSR ; 
 unsigned char MMIO_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RBR ; 
 unsigned char UART_LSR_DR ; 
 unsigned char UART_LSR_FE ; 
 unsigned char UART_LSR_OE ; 
 unsigned char UART_LSR_PE ; 

__attribute__((used)) static int
mmio_uart_rr0( void ) 
{
    unsigned char lsr;

    lsr = MMIO_READ( LSR );

    if ( lsr & (UART_LSR_FE | UART_LSR_PE | UART_LSR_OE) )
    {
        MMIO_READ( RBR ); /* discard */
        return 0;
    }
    
    return (lsr & UART_LSR_DR);
}