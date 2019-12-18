#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  irq; } ;
struct uart_pmac_port {int* curregs; TYPE_3__* dev; TYPE_1__ port; int /*<<< orphan*/  flags; int /*<<< orphan*/ * node; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {TYPE_2__ ofdev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODEV ; 
 int ENXIO ; 
 int EXT_INT_ENAB ; 
 int INT_ALL_Rx ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  PMACZILOG_FLAG_IS_IRQ_ON ; 
 int /*<<< orphan*/  PMACZILOG_FLAG_IS_OPEN ; 
 size_t R1 ; 
 int TxINT_ENAB ; 
 scalar_t__ ZS_IS_ASLEEP (struct uart_pmac_port*) ; 
 int /*<<< orphan*/  ZS_IS_CONS (struct uart_pmac_port*) ; 
 int /*<<< orphan*/  ZS_IS_EXTCLK (struct uart_pmac_port*) ; 
 scalar_t__ ZS_IS_IRDA (struct uart_pmac_port*) ; 
 int __pmz_startup (struct uart_pmac_port*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmz_debug (char*,...) ; 
 TYPE_4__* pmz_get_port_A (struct uart_pmac_port*) ; 
 int /*<<< orphan*/  pmz_interrupt ; 
 int /*<<< orphan*/  pmz_irda_reset (struct uart_pmac_port*) ; 
 int /*<<< orphan*/  pmz_irq_mutex ; 
 int /*<<< orphan*/  pmz_set_scc_power (struct uart_pmac_port*,int /*<<< orphan*/ ) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct uart_pmac_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct uart_pmac_port* to_pmz (struct uart_port*) ; 
 int /*<<< orphan*/  write_zsreg (struct uart_pmac_port*,size_t,int) ; 

__attribute__((used)) static int pmz_startup(struct uart_port *port)
{
	struct uart_pmac_port *uap = to_pmz(port);
	unsigned long flags;
	int pwr_delay = 0;

	pmz_debug("pmz: startup()\n");

	if (ZS_IS_ASLEEP(uap))
		return -EAGAIN;
	if (uap->node == NULL)
		return -ENODEV;

	mutex_lock(&pmz_irq_mutex);

	uap->flags |= PMACZILOG_FLAG_IS_OPEN;

	/* A console is never powered down. Else, power up and
	 * initialize the chip
	 */
	if (!ZS_IS_CONS(uap)) {
		spin_lock_irqsave(&port->lock, flags);
		pwr_delay = __pmz_startup(uap);
		spin_unlock_irqrestore(&port->lock, flags);
	}	

	pmz_get_port_A(uap)->flags |= PMACZILOG_FLAG_IS_IRQ_ON;
	if (request_irq(uap->port.irq, pmz_interrupt, IRQF_SHARED, "PowerMac Zilog", uap)) {
		dev_err(&uap->dev->ofdev.dev,
			"Unable to register zs interrupt handler.\n");
		pmz_set_scc_power(uap, 0);
		mutex_unlock(&pmz_irq_mutex);
		return -ENXIO;
	}

	mutex_unlock(&pmz_irq_mutex);

	/* Right now, we deal with delay by blocking here, I'll be
	 * smarter later on
	 */
	if (pwr_delay != 0) {
		pmz_debug("pmz: delaying %d ms\n", pwr_delay);
		msleep(pwr_delay);
	}

	/* IrDA reset is done now */
	if (ZS_IS_IRDA(uap))
		pmz_irda_reset(uap);

	/* Enable interrupts emission from the chip */
	spin_lock_irqsave(&port->lock, flags);
	uap->curregs[R1] |= INT_ALL_Rx | TxINT_ENAB;
	if (!ZS_IS_EXTCLK(uap))
		uap->curregs[R1] |= EXT_INT_ENAB;
	write_zsreg(uap, R1, uap->curregs[R1]);
       	spin_unlock_irqrestore(&port->lock, flags);

	pmz_debug("pmz: startup() done.\n");

	return 0;
}