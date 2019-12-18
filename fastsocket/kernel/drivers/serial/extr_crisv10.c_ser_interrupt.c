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
struct e100_serial {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LOG (int /*<<< orphan*/ ,char*,unsigned long) ; 
 int /*<<< orphan*/  DFLOW (int /*<<< orphan*/ ) ; 
 unsigned long IO_MASK (unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IO_STATE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int NR_PORTS ; 
 unsigned long* R_IRQ_MASK1_CLR ; 
 unsigned long* R_IRQ_MASK1_RD ; 
 int /*<<< orphan*/ * R_VECT_MASK_SET ; 
 int /*<<< orphan*/  SERIAL_DEBUG_LINE ; 
 unsigned long e100_ser_int_mask ; 
 int /*<<< orphan*/  handle_ser_rx_interrupt (struct e100_serial*) ; 
 int /*<<< orphan*/  handle_ser_tx_interrupt (struct e100_serial*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 struct e100_serial* rs_table ; 
 int /*<<< orphan*/  ser0_ready ; 
 int /*<<< orphan*/  ser1_ready ; 
 int /*<<< orphan*/  ser2_ready ; 
 int /*<<< orphan*/  ser3_ready ; 
 int /*<<< orphan*/  serial ; 
 int /*<<< orphan*/  set ; 

__attribute__((used)) static irqreturn_t
ser_interrupt(int irq, void *dev_id)
{
	static volatile int tx_started = 0;
	struct e100_serial *info;
	int i;
	unsigned long flags;
	unsigned long irq_mask1_rd;
	unsigned long data_mask = (1 << (8+2*0)); /* ser0 data_avail */
	int handled = 0;
	static volatile unsigned long reentered_ready_mask = 0;

	local_irq_save(flags);
	irq_mask1_rd = *R_IRQ_MASK1_RD;
	/* First handle all rx interrupts with ints disabled */
	info = rs_table;
	irq_mask1_rd &= e100_ser_int_mask;
	for (i = 0; i < NR_PORTS; i++) {
		/* Which line caused the data irq? */
		if (irq_mask1_rd & data_mask) {
			handled = 1;
			handle_ser_rx_interrupt(info);
		}
		info += 1;
		data_mask <<= 2;
	}
	/* Handle tx interrupts with interrupts enabled so we
	 * can take care of new data interrupts while transmitting
	 * We protect the tx part with the tx_started flag.
	 * We disable the tr_ready interrupts we are about to handle and
	 * unblock the serial interrupt so new serial interrupts may come.
	 *
	 * If we get a new interrupt:
	 *  - it migth be due to synchronous serial ports.
	 *  - serial irq will be blocked by general irq handler.
	 *  - async data will be handled above (sync will be ignored).
	 *  - tx_started flag will prevent us from trying to send again and
	 *    we will exit fast - no need to unblock serial irq.
	 *  - Next (sync) serial interrupt handler will be runned with
	 *    disabled interrupt due to restore_flags() at end of function,
	 *    so sync handler will not be preempted or reentered.
	 */
	if (!tx_started) {
		unsigned long ready_mask;
		unsigned long
		tx_started = 1;
		/* Only the tr_ready interrupts left */
		irq_mask1_rd &= (IO_MASK(R_IRQ_MASK1_RD, ser0_ready) |
				 IO_MASK(R_IRQ_MASK1_RD, ser1_ready) |
				 IO_MASK(R_IRQ_MASK1_RD, ser2_ready) |
				 IO_MASK(R_IRQ_MASK1_RD, ser3_ready));
		while (irq_mask1_rd) {
			/* Disable those we are about to handle */
			*R_IRQ_MASK1_CLR = irq_mask1_rd;
			/* Unblock the serial interrupt */
			*R_VECT_MASK_SET = IO_STATE(R_VECT_MASK_SET, serial, set);

			local_irq_enable();
			ready_mask = (1 << (8+1+2*0)); /* ser0 tr_ready */
			info = rs_table;
			for (i = 0; i < NR_PORTS; i++) {
				/* Which line caused the ready irq? */
				if (irq_mask1_rd & ready_mask) {
					handled = 1;
					handle_ser_tx_interrupt(info);
				}
				info += 1;
				ready_mask <<= 2;
			}
			/* handle_ser_tx_interrupt enables tr_ready interrupts */
			local_irq_disable();
			/* Handle reentered TX interrupt */
			irq_mask1_rd = reentered_ready_mask;
		}
		local_irq_disable();
		tx_started = 0;
	} else {
		unsigned long ready_mask;
		ready_mask = irq_mask1_rd & (IO_MASK(R_IRQ_MASK1_RD, ser0_ready) |
					     IO_MASK(R_IRQ_MASK1_RD, ser1_ready) |
					     IO_MASK(R_IRQ_MASK1_RD, ser2_ready) |
					     IO_MASK(R_IRQ_MASK1_RD, ser3_ready));
		if (ready_mask) {
			reentered_ready_mask |= ready_mask;
			/* Disable those we are about to handle */
			*R_IRQ_MASK1_CLR = ready_mask;
			DFLOW(DEBUG_LOG(SERIAL_DEBUG_LINE, "ser_int reentered with TX %X\n", ready_mask));
		}
	}

	local_irq_restore(flags);
	return IRQ_RETVAL(handled);
}