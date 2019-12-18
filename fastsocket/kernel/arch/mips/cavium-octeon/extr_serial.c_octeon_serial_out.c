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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u8 ;
struct uart_port {scalar_t__ membase; } ;

/* Variables and functions */
 int UART_LCR ; 
 int /*<<< orphan*/  cvmx_write_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void octeon_serial_out(struct uart_port *up, int offset, int value)
{
	/*
	 * If bits 6 or 7 of the OCTEON UART's LCR are set, it quits
	 * working.
	 */
	if (offset == UART_LCR)
		value &= 0x9f;
	cvmx_write_csr((uint64_t)(up->membase + (offset << 3)), (u8)value);
}