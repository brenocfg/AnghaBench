#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  irq; } ;
struct uart_sunsab_port {int cached_mode; int interrupt_mask0; int interrupt_mask1; TYPE_5__ port; int /*<<< orphan*/  irqflags; TYPE_4__* regs; } ;
struct uart_port {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  imr1; int /*<<< orphan*/  imr0; int /*<<< orphan*/  rfc; int /*<<< orphan*/  mode; int /*<<< orphan*/  ccr4; int /*<<< orphan*/  ccr3; int /*<<< orphan*/  ccr2; int /*<<< orphan*/  ccr1; int /*<<< orphan*/  ccr0; int /*<<< orphan*/  cmdr; } ;
struct TYPE_7__ {int /*<<< orphan*/  ccr0; } ;
struct TYPE_6__ {int /*<<< orphan*/  isr1; int /*<<< orphan*/  isr0; } ;
struct TYPE_9__ {TYPE_3__ w; TYPE_2__ rw; TYPE_1__ r; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  SAB82532_ALLS ; 
 unsigned char SAB82532_CCR0_MCE ; 
 unsigned char SAB82532_CCR0_PU ; 
 unsigned char SAB82532_CCR0_SC_NRZ ; 
 unsigned char SAB82532_CCR0_SM_ASYNC ; 
 int SAB82532_CCR1_BCR ; 
 int SAB82532_CCR1_ODS ; 
 unsigned char SAB82532_CCR2_BDF ; 
 unsigned char SAB82532_CCR2_SSEL ; 
 unsigned char SAB82532_CCR2_TOE ; 
 unsigned char SAB82532_CCR4_EBRG ; 
 unsigned char SAB82532_CCR4_MCK4 ; 
 unsigned char SAB82532_CMDR_RRES ; 
 unsigned char SAB82532_CMDR_XRES ; 
 int SAB82532_IMR0_FERR ; 
 int SAB82532_IMR0_PERR ; 
 int SAB82532_IMR0_PLLA ; 
 int SAB82532_IMR1_ALLS ; 
 int SAB82532_IMR1_BRKT ; 
 int SAB82532_IMR1_CSC ; 
 int SAB82532_IMR1_TIN ; 
 int SAB82532_IMR1_XOFF ; 
 int SAB82532_IMR1_XON ; 
 int SAB82532_IMR1_XPR ; 
 int SAB82532_MODE_FCTS ; 
 int SAB82532_MODE_RAC ; 
 int SAB82532_MODE_RTS ; 
 unsigned char SAB82532_RFC_DPS ; 
 unsigned char SAB82532_RFC_RFTH_32 ; 
 int /*<<< orphan*/  SAB82532_XPR ; 
 unsigned char readb (int /*<<< orphan*/ *) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct uart_sunsab_port*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sunsab_cec_wait (struct uart_sunsab_port*) ; 
 int /*<<< orphan*/  sunsab_interrupt ; 
 int /*<<< orphan*/  sunsab_tec_wait (struct uart_sunsab_port*) ; 
 int /*<<< orphan*/  writeb (unsigned char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sunsab_startup(struct uart_port *port)
{
	struct uart_sunsab_port *up = (struct uart_sunsab_port *) port;
	unsigned long flags;
	unsigned char tmp;
	int err = request_irq(up->port.irq, sunsab_interrupt,
			      IRQF_SHARED, "sab", up);
	if (err)
		return err;

	spin_lock_irqsave(&up->port.lock, flags);

	/*
	 * Wait for any commands or immediate characters
	 */
	sunsab_cec_wait(up);
	sunsab_tec_wait(up);

	/*
	 * Clear the FIFO buffers.
	 */
	writeb(SAB82532_CMDR_RRES, &up->regs->w.cmdr);
	sunsab_cec_wait(up);
	writeb(SAB82532_CMDR_XRES, &up->regs->w.cmdr);

	/*
	 * Clear the interrupt registers.
	 */
	(void) readb(&up->regs->r.isr0);
	(void) readb(&up->regs->r.isr1);

	/*
	 * Now, initialize the UART 
	 */
	writeb(0, &up->regs->w.ccr0);				/* power-down */
	writeb(SAB82532_CCR0_MCE | SAB82532_CCR0_SC_NRZ |
	       SAB82532_CCR0_SM_ASYNC, &up->regs->w.ccr0);
	writeb(SAB82532_CCR1_ODS | SAB82532_CCR1_BCR | 7, &up->regs->w.ccr1);
	writeb(SAB82532_CCR2_BDF | SAB82532_CCR2_SSEL |
	       SAB82532_CCR2_TOE, &up->regs->w.ccr2);
	writeb(0, &up->regs->w.ccr3);
	writeb(SAB82532_CCR4_MCK4 | SAB82532_CCR4_EBRG, &up->regs->w.ccr4);
	up->cached_mode = (SAB82532_MODE_RTS | SAB82532_MODE_FCTS |
			   SAB82532_MODE_RAC);
	writeb(up->cached_mode, &up->regs->w.mode);
	writeb(SAB82532_RFC_DPS|SAB82532_RFC_RFTH_32, &up->regs->w.rfc);
	
	tmp = readb(&up->regs->rw.ccr0);
	tmp |= SAB82532_CCR0_PU;	/* power-up */
	writeb(tmp, &up->regs->rw.ccr0);

	/*
	 * Finally, enable interrupts
	 */
	up->interrupt_mask0 = (SAB82532_IMR0_PERR | SAB82532_IMR0_FERR |
			       SAB82532_IMR0_PLLA);
	writeb(up->interrupt_mask0, &up->regs->w.imr0);
	up->interrupt_mask1 = (SAB82532_IMR1_BRKT | SAB82532_IMR1_ALLS |
			       SAB82532_IMR1_XOFF | SAB82532_IMR1_TIN |
			       SAB82532_IMR1_CSC | SAB82532_IMR1_XON |
			       SAB82532_IMR1_XPR);
	writeb(up->interrupt_mask1, &up->regs->w.imr1);
	set_bit(SAB82532_ALLS, &up->irqflags);
	set_bit(SAB82532_XPR, &up->irqflags);

	spin_unlock_irqrestore(&up->port.lock, flags);

	return 0;
}