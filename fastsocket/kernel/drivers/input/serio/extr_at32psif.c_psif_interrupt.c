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
struct psif {int /*<<< orphan*/  io; TYPE_1__* pdev; } ;
typedef  int irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 int /*<<< orphan*/  OVRUN ; 
 int /*<<< orphan*/  PARITY ; 
 unsigned long PSIF_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RHR ; 
 int /*<<< orphan*/  RXRDY ; 
 unsigned int SERIO_PARITY ; 
 int /*<<< orphan*/  SR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 unsigned long psif_readl (struct psif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serio_interrupt (int /*<<< orphan*/ ,unsigned char,unsigned int) ; 

__attribute__((used)) static irqreturn_t psif_interrupt(int irq, void *_ptr)
{
	struct psif *psif = _ptr;
	int retval = IRQ_NONE;
	unsigned int io_flags = 0;
	unsigned long status;

	status = psif_readl(psif, SR);

	if (status & PSIF_BIT(RXRDY)) {
		unsigned char val = (unsigned char) psif_readl(psif, RHR);

		if (status & PSIF_BIT(PARITY))
			io_flags |= SERIO_PARITY;
		if (status & PSIF_BIT(OVRUN))
			dev_err(&psif->pdev->dev, "overrun read error\n");

		serio_interrupt(psif->io, val, io_flags);

		retval = IRQ_HANDLED;
	}

	return retval;
}