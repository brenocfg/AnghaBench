#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct port_hooks {int intr_rx_timer; int intr_rx_high; int intr_tx_explicit; int intr_delta_dcd; int intr_delta_cts; int intr_tx_mt; } ;
struct ioc3_port {int ip_notify; int ip_sscr; TYPE_2__* ip_serial_regs; TYPE_1__* ip_card; struct port_hooks* ip_hooks; } ;
struct TYPE_4__ {int /*<<< orphan*/  sscr; } ;
struct TYPE_3__ {int ic_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int N_DATA_READY ; 
 int N_DCTS ; 
 int N_DDCD ; 
 int N_OUTPUT_LOWAT ; 
 int SSCR_DMA_EN ; 
 int SSCR_RX_RING_DCD ; 
 int /*<<< orphan*/  disable_intrs (struct ioc3_port*,int) ; 
 int /*<<< orphan*/  enable_intrs (struct ioc3_port*,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int set_notification(struct ioc3_port *port, int mask, int set_on)
{
	struct port_hooks *hooks = port->ip_hooks;
	uint32_t intrbits, sscrbits;

	BUG_ON(!mask);

	intrbits = sscrbits = 0;

	if (mask & N_DATA_READY)
		intrbits |= (hooks->intr_rx_timer | hooks->intr_rx_high);
	if (mask & N_OUTPUT_LOWAT)
		intrbits |= hooks->intr_tx_explicit;
	if (mask & N_DDCD) {
		intrbits |= hooks->intr_delta_dcd;
		sscrbits |= SSCR_RX_RING_DCD;
	}
	if (mask & N_DCTS)
		intrbits |= hooks->intr_delta_cts;

	if (set_on) {
		enable_intrs(port, intrbits);
		port->ip_notify |= mask;
		port->ip_sscr |= sscrbits;
	} else {
		disable_intrs(port, intrbits);
		port->ip_notify &= ~mask;
		port->ip_sscr &= ~sscrbits;
	}

	/* We require DMA if either DATA_READY or DDCD notification is
	 * currently requested. If neither of these is requested and
	 * there is currently no tx in progress, DMA may be disabled.
	 */
	if (port->ip_notify & (N_DATA_READY | N_DDCD))
		port->ip_sscr |= SSCR_DMA_EN;
	else if (!(port->ip_card->ic_enable & hooks->intr_tx_mt))
		port->ip_sscr &= ~SSCR_DMA_EN;

	writel(port->ip_sscr, &port->ip_serial_regs->sscr);
	return 0;
}