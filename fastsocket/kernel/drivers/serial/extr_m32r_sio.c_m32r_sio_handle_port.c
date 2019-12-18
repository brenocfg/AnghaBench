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
struct uart_sio_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_INTR (char*,unsigned int) ; 
 int /*<<< orphan*/  receive_chars (struct uart_sio_port*,unsigned int*) ; 
 int /*<<< orphan*/  transmit_chars (struct uart_sio_port*) ; 

__attribute__((used)) static inline void m32r_sio_handle_port(struct uart_sio_port *up,
	unsigned int status)
{
	DEBUG_INTR("status = %x...", status);

	if (status & 0x04)
		receive_chars(up, &status);
	if (status & 0x01)
		transmit_chars(up);
}