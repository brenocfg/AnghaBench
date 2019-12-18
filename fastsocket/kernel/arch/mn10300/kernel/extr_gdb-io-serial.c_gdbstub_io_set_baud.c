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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 unsigned int GDBPORT_SERIAL_DLL ; 
 unsigned int GDBPORT_SERIAL_DLM ; 
 int /*<<< orphan*/  GDBPORT_SERIAL_LCR ; 
 int /*<<< orphan*/  UART_LCR_DLAB ; 

void gdbstub_io_set_baud(unsigned baud)
{
	unsigned value;
	u8 lcr;

	value = 18432000 / 16 / baud;

	lcr = GDBPORT_SERIAL_LCR;
	GDBPORT_SERIAL_LCR |= UART_LCR_DLAB;
	GDBPORT_SERIAL_DLL = value & 0xff;
	GDBPORT_SERIAL_DLM = (value >> 8) & 0xff;
	GDBPORT_SERIAL_LCR = lcr;
}