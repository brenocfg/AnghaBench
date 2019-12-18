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
struct e100_serial {int irq; int /*<<< orphan*/  uses_dma_in; int /*<<< orphan*/  enabled; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int NR_PORTS ; 
 unsigned long* R_IRQ_MASK2_RD ; 
 int /*<<< orphan*/  SIMCOUT (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  receive_chars_dma (struct e100_serial*) ; 
 struct e100_serial* rs_table ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static irqreturn_t
rec_interrupt(int irq, void *dev_id)
{
	struct e100_serial *info;
	unsigned long ireg;
	int i;
	int handled = 0;

#ifdef CONFIG_SVINTO_SIM
	/* No receive in the simulator.  Will probably be when the rest of
	 * the serial interface works, and this piece will just be removed.
	 */
	{
		const char *s = "What? rec_interrupt in simulator??\n";
		SIMCOUT(s,strlen(s));
	}
	return IRQ_HANDLED;
#endif

	/* find out the line that caused this irq and get it from rs_table */

	ireg = *R_IRQ_MASK2_RD;  /* get the active irq bits for the dma channels */

	for (i = 0; i < NR_PORTS; i++) {
		info = rs_table + i;
		if (!info->enabled || !info->uses_dma_in)
			continue;
		/* check for both dma_eop and dma_descr for the input dma channel */
		if (ireg & ((info->irq << 2) | (info->irq << 3))) {
			handled = 1;
			/* we have received something */
			receive_chars_dma(info);
		}

		/* FIXME: here we should really check for a change in the
		   status lines and if so call status_handle(info) */
	}
	return IRQ_RETVAL(handled);
}