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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int irq; int /*<<< orphan*/  locality; scalar_t__ iobase; } ;
struct tpm_chip {TYPE_1__ vendor; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ TPM_INT_STATUS (int /*<<< orphan*/ ) ; 
 scalar_t__ ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static irqreturn_t tis_int_probe(int irq, void *dev_id)
{
	struct tpm_chip *chip = dev_id;
	u32 interrupt;

	interrupt = ioread32(chip->vendor.iobase +
			     TPM_INT_STATUS(chip->vendor.locality));

	if (interrupt == 0)
		return IRQ_NONE;

	chip->vendor.irq = irq;

	/* Clear interrupts handled with TPM_EOI */
	iowrite32(interrupt,
		  chip->vendor.iobase +
		  TPM_INT_STATUS(chip->vendor.locality));
	return IRQ_HANDLED;
}