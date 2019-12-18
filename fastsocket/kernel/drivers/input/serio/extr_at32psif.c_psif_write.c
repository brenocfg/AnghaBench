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
struct serio {struct psif* port_data; } ;
struct psif {int /*<<< orphan*/  lock; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int PSIF_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SR ; 
 int /*<<< orphan*/  THR ; 
 int /*<<< orphan*/  TXEMPTY ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int psif_readl (struct psif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psif_writel (struct psif*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int psif_write(struct serio *io, unsigned char val)
{
	struct psif *psif = io->port_data;
	unsigned long flags;
	int timeout = 10;
	int retval = 0;

	spin_lock_irqsave(&psif->lock, flags);

	while (!(psif_readl(psif, SR) & PSIF_BIT(TXEMPTY)) && timeout--)
		msleep(10);

	if (timeout >= 0) {
		psif_writel(psif, THR, val);
	} else {
		dev_dbg(&psif->pdev->dev, "timeout writing to THR\n");
		retval = -EBUSY;
	}

	spin_unlock_irqrestore(&psif->lock, flags);

	return retval;
}