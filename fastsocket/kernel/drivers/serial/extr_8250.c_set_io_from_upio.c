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
struct uart_port {int iotype; int /*<<< orphan*/  serial_out; void* serial_in; } ;
struct uart_8250_port {int cur_iotype; } ;

/* Variables and functions */
#define  UPIO_AU 134 
#define  UPIO_DWAPB 133 
#define  UPIO_HUB6 132 
#define  UPIO_MEM 131 
#define  UPIO_MEM32 130 
#define  UPIO_RM9000 129 
#define  UPIO_TSI 128 
 void* au_serial_in ; 
 int /*<<< orphan*/  au_serial_out ; 
 int /*<<< orphan*/  dwapb_serial_out ; 
 void* hub6_serial_in ; 
 int /*<<< orphan*/  hub6_serial_out ; 
 void* io_serial_in ; 
 int /*<<< orphan*/  io_serial_out ; 
 void* mem32_serial_in ; 
 int /*<<< orphan*/  mem32_serial_out ; 
 void* mem_serial_in ; 
 int /*<<< orphan*/  mem_serial_out ; 
 void* tsi_serial_in ; 
 int /*<<< orphan*/  tsi_serial_out ; 

__attribute__((used)) static void set_io_from_upio(struct uart_port *p)
{
	struct uart_8250_port *up = (struct uart_8250_port *)p;
	switch (p->iotype) {
	case UPIO_HUB6:
		p->serial_in = hub6_serial_in;
		p->serial_out = hub6_serial_out;
		break;

	case UPIO_MEM:
		p->serial_in = mem_serial_in;
		p->serial_out = mem_serial_out;
		break;

	case UPIO_RM9000:
	case UPIO_MEM32:
		p->serial_in = mem32_serial_in;
		p->serial_out = mem32_serial_out;
		break;

#ifdef CONFIG_SERIAL_8250_AU1X00
	case UPIO_AU:
		p->serial_in = au_serial_in;
		p->serial_out = au_serial_out;
		break;
#endif
	case UPIO_TSI:
		p->serial_in = tsi_serial_in;
		p->serial_out = tsi_serial_out;
		break;

	case UPIO_DWAPB:
		p->serial_in = mem_serial_in;
		p->serial_out = dwapb_serial_out;
		break;

	default:
		p->serial_in = io_serial_in;
		p->serial_out = io_serial_out;
		break;
	}
	/* Remember loaded iotype */
	up->cur_iotype = p->iotype;
}