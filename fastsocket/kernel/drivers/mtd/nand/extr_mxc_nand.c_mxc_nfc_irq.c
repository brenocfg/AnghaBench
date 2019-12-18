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
typedef  int /*<<< orphan*/  uint16_t ;
struct mxc_nand_host {int /*<<< orphan*/  irq_waitq; scalar_t__ regs; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ NFC_CONFIG1 ; 
 int /*<<< orphan*/  NFC_INT_MSK ; 
 int /*<<< orphan*/  readw (scalar_t__) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t mxc_nfc_irq(int irq, void *dev_id)
{
	struct mxc_nand_host *host = dev_id;

	uint16_t tmp;

	tmp = readw(host->regs + NFC_CONFIG1);
	tmp |= NFC_INT_MSK; /* Disable interrupt */
	writew(tmp, host->regs + NFC_CONFIG1);

	wake_up(&host->irq_waitq);

	return IRQ_HANDLED;
}