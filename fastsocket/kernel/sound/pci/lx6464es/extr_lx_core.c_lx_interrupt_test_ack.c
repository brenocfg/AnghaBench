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
typedef  int u32 ;
struct lx6464es {int dummy; } ;

/* Variables and functions */
 int IRQCS_ACTIVE_PCIDB ; 
 int PCX_IRQ_NONE ; 
 int /*<<< orphan*/  ePLX_IRQCS ; 
 int /*<<< orphan*/  ePLX_L2PCIDB ; 
 int lx_plx_reg_read (struct lx6464es*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lx_plx_reg_write (struct lx6464es*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u32 lx_interrupt_test_ack(struct lx6464es *chip)
{
	u32 irqcs = lx_plx_reg_read(chip, ePLX_IRQCS);

	/* Test if PCI Doorbell interrupt is active */
	if (irqcs & IRQCS_ACTIVE_PCIDB)	{
		u32 temp;
		irqcs = PCX_IRQ_NONE;

		while ((temp = lx_plx_reg_read(chip, ePLX_L2PCIDB))) {
			/* RAZ interrupt */
			irqcs |= temp;
			lx_plx_reg_write(chip, ePLX_L2PCIDB, temp);
		}

		return irqcs;
	}
	return PCX_IRQ_NONE;
}