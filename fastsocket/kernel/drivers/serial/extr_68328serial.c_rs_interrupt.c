#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct m68k_serial {size_t line; } ;
struct TYPE_6__ {unsigned short w; } ;
struct TYPE_5__ {unsigned short w; } ;
struct TYPE_7__ {TYPE_2__ utx; TYPE_1__ urx; } ;
typedef  TYPE_3__ m68328_uart ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned short URX_DATA_READY ; 
 unsigned short UTX_TX_AVAIL ; 
 int /*<<< orphan*/  receive_chars (struct m68k_serial*,unsigned short) ; 
 int /*<<< orphan*/  transmit_chars (struct m68k_serial*) ; 
 TYPE_3__* uart_addr ; 

irqreturn_t rs_interrupt(int irq, void *dev_id)
{
	struct m68k_serial *info = dev_id;
	m68328_uart *uart;
	unsigned short rx;
	unsigned short tx;

	uart = &uart_addr[info->line];
	rx = uart->urx.w;

#ifdef USE_INTS
	tx = uart->utx.w;

	if (rx & URX_DATA_READY) receive_chars(info, rx);
	if (tx & UTX_TX_AVAIL)   transmit_chars(info);
#else
	receive_chars(info, rx);		
#endif
	return IRQ_HANDLED;
}