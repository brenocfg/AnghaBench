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
struct uart_port {scalar_t__ membase; } ;

/* Variables and functions */
 int UART_IIR ; 
 int cvmx_read_csr (int /*<<< orphan*/ ) ; 

unsigned int octeon_serial_in(struct uart_port *up, int offset)
{
	int rv = cvmx_read_csr((uint64_t)(up->membase + (offset << 3)));
	if (offset == UART_IIR && (rv & 0xf) == 7) {
		/* Busy interrupt, read the USR (39) and try again. */
		cvmx_read_csr((uint64_t)(up->membase + (39 << 3)));
		rv = cvmx_read_csr((uint64_t)(up->membase + (offset << 3)));
	}
	return rv;
}