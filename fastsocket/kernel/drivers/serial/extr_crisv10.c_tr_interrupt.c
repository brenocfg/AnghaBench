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
struct e100_serial {unsigned long irq; size_t line; int /*<<< orphan*/  last_tx_active; int /*<<< orphan*/  last_tx_active_usec; int /*<<< orphan*/  uses_dma_out; int /*<<< orphan*/  enabled; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  tx_dma_ints; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LOG (size_t,char*,int) ; 
 int /*<<< orphan*/  DINTR2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_JIFFIES_USEC () ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int NR_PORTS ; 
 int /*<<< orphan*/  PROCSTAT (int /*<<< orphan*/ ) ; 
 unsigned long* R_IRQ_MASK2_RD ; 
 int /*<<< orphan*/  SIMCOUT (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 struct e100_serial* rs_table ; 
 TYPE_1__* ser_stat ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  transmit_chars_dma (struct e100_serial*) ; 

__attribute__((used)) static irqreturn_t
tr_interrupt(int irq, void *dev_id)
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
		const char *s = "What? tr_interrupt in simulator??\n";
		SIMCOUT(s,strlen(s));
	}
	return IRQ_HANDLED;
#endif

	/* find out the line that caused this irq and get it from rs_table */

	ireg = *R_IRQ_MASK2_RD;  /* get the active irq bits for the dma channels */

	for (i = 0; i < NR_PORTS; i++) {
		info = rs_table + i;
		if (!info->enabled || !info->uses_dma_out)
			continue;
		/* check for dma_descr (don't need to check for dma_eop in output dma for serial */
		if (ireg & info->irq) {
			handled = 1;
			/* we can send a new dma bunch. make it so. */
			DINTR2(DEBUG_LOG(info->line, "tr_interrupt %i\n", i));
			/* Read jiffies_usec first,
			 * we want this time to be as late as possible
			 */
 			PROCSTAT(ser_stat[info->line].tx_dma_ints++);
			info->last_tx_active_usec = GET_JIFFIES_USEC();
			info->last_tx_active = jiffies;
			transmit_chars_dma(info);
		}

		/* FIXME: here we should really check for a change in the
		   status lines and if so call status_handle(info) */
	}
	return IRQ_RETVAL(handled);
}