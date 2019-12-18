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
struct atmel_mci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT_XFER_COMPLETE ; 
 int /*<<< orphan*/  IER ; 
 int /*<<< orphan*/  MCI_NOTBUSY ; 
 int /*<<< orphan*/  atmci_set_pending (struct atmel_mci*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mci_writel (struct atmel_mci*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void atmci_stop_dma(struct atmel_mci *host)
{
	/* Data transfer was stopped by the interrupt handler */
	atmci_set_pending(host, EVENT_XFER_COMPLETE);
	mci_writel(host, IER, MCI_NOTBUSY);
}