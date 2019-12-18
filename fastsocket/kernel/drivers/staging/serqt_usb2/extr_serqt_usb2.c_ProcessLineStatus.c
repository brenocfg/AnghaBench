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
struct quatech_port {unsigned char shadowLSR; } ;

/* Variables and functions */
 unsigned char SERIAL_LSR_BI ; 
 unsigned char SERIAL_LSR_FE ; 
 unsigned char SERIAL_LSR_OE ; 
 unsigned char SERIAL_LSR_PE ; 

__attribute__((used)) static void ProcessLineStatus(struct quatech_port *qt_port,
			      unsigned char line_status)
{

	qt_port->shadowLSR =
	    line_status & (SERIAL_LSR_OE | SERIAL_LSR_PE | SERIAL_LSR_FE |
			   SERIAL_LSR_BI);
	return;
}