#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct uart_pmac_port {TYPE_1__ port; int /*<<< orphan*/ * node; struct uart_pmac_port* mate; } ;
struct tty_struct {int dummy; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int CHAEXT ; 
 int CHARxIP ; 
 int CHATxIP ; 
 int CHBEXT ; 
 int CHBRxIP ; 
 int CHBTxIP ; 
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R3 ; 
 int /*<<< orphan*/  RES_H_IUS ; 
 int /*<<< orphan*/  pmz_debug (char*,...) ; 
 struct uart_pmac_port* pmz_get_port_A (struct uart_pmac_port*) ; 
 struct tty_struct* pmz_receive_chars (struct uart_pmac_port*) ; 
 int /*<<< orphan*/  pmz_status_handle (struct uart_pmac_port*) ; 
 int /*<<< orphan*/  pmz_transmit_chars (struct uart_pmac_port*) ; 
 int read_zsreg (struct uart_pmac_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 int /*<<< orphan*/  write_zsreg (struct uart_pmac_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zssync (struct uart_pmac_port*) ; 

__attribute__((used)) static irqreturn_t pmz_interrupt(int irq, void *dev_id)
{
	struct uart_pmac_port *uap = dev_id;
	struct uart_pmac_port *uap_a;
	struct uart_pmac_port *uap_b;
	int rc = IRQ_NONE;
	struct tty_struct *tty;
	u8 r3;

	uap_a = pmz_get_port_A(uap);
	uap_b = uap_a->mate;
       
       	spin_lock(&uap_a->port.lock);
	r3 = read_zsreg(uap_a, R3);

#ifdef DEBUG_HARD
	pmz_debug("irq, r3: %x\n", r3);
#endif
       	/* Channel A */
	tty = NULL;
       	if (r3 & (CHAEXT | CHATxIP | CHARxIP)) {
		write_zsreg(uap_a, R0, RES_H_IUS);
		zssync(uap_a);		
       		if (r3 & CHAEXT)
       			pmz_status_handle(uap_a);
		if (r3 & CHARxIP)
			tty = pmz_receive_chars(uap_a);
       		if (r3 & CHATxIP)
       			pmz_transmit_chars(uap_a);
	        rc = IRQ_HANDLED;
       	}
       	spin_unlock(&uap_a->port.lock);
	if (tty != NULL)
		tty_flip_buffer_push(tty);

	if (uap_b->node == NULL)
		goto out;

       	spin_lock(&uap_b->port.lock);
	tty = NULL;
	if (r3 & (CHBEXT | CHBTxIP | CHBRxIP)) {
		write_zsreg(uap_b, R0, RES_H_IUS);
		zssync(uap_b);
       		if (r3 & CHBEXT)
       			pmz_status_handle(uap_b);
       	       	if (r3 & CHBRxIP)
       			tty = pmz_receive_chars(uap_b);
       		if (r3 & CHBTxIP)
       			pmz_transmit_chars(uap_b);
	       	rc = IRQ_HANDLED;
       	}
       	spin_unlock(&uap_b->port.lock);
	if (tty != NULL)
		tty_flip_buffer_push(tty);

 out:
#ifdef DEBUG_HARD
	pmz_debug("irq done.\n");
#endif
	return rc;
}