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
typedef  int u8 ;
struct zs_scc {int /*<<< orphan*/  zlock; struct zs_port* zport; } ;
struct zs_port {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int CHAEXT ; 
 int CHARxIP ; 
 int CHATxIP ; 
 int CHBEXT ; 
 int CHBRxIP ; 
 int CHBTxIP ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  R3 ; 
 size_t ZS_CHAN_A ; 
 size_t ZS_CHAN_B ; 
 int read_zsreg (struct zs_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zs_receive_chars (struct zs_port*) ; 
 int /*<<< orphan*/  zs_status_handle (struct zs_port*,struct zs_port*) ; 
 int /*<<< orphan*/  zs_transmit_chars (struct zs_port*) ; 

__attribute__((used)) static irqreturn_t zs_interrupt(int irq, void *dev_id)
{
	struct zs_scc *scc = dev_id;
	struct zs_port *zport_a = &scc->zport[ZS_CHAN_A];
	struct zs_port *zport_b = &scc->zport[ZS_CHAN_B];
	irqreturn_t status = IRQ_NONE;
	u8 zs_intreg;
	int count;

	/*
	 * NOTE: The read register 3, which holds the irq status,
	 *       does so for both channels on each chip.  Although
	 *       the status value itself must be read from the A
	 *       channel and is only valid when read from channel A.
	 *       Yes... broken hardware...
	 */
	for (count = 16; count; count--) {
		spin_lock(&scc->zlock);
		zs_intreg = read_zsreg(zport_a, R3);
		spin_unlock(&scc->zlock);
		if (!zs_intreg)
			break;

		/*
		 * We do not like losing characters, so we prioritise
		 * interrupt sources a little bit differently than
		 * the SCC would, was it allowed to.
		 */
		if (zs_intreg & CHBRxIP)
			zs_receive_chars(zport_b);
		if (zs_intreg & CHARxIP)
			zs_receive_chars(zport_a);
		if (zs_intreg & CHBEXT)
			zs_status_handle(zport_b, zport_a);
		if (zs_intreg & CHAEXT)
			zs_status_handle(zport_a, zport_a);
		if (zs_intreg & CHBTxIP)
			zs_transmit_chars(zport_b);
		if (zs_intreg & CHATxIP)
			zs_transmit_chars(zport_a);

		status = IRQ_HANDLED;
	}

	return status;
}