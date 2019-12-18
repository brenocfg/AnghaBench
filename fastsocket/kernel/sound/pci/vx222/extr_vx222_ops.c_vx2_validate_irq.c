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
struct vx_core {int dummy; } ;
struct snd_vx222 {int regCDSP; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDSP ; 
 int /*<<< orphan*/  INTCSR ; 
 int VX_CDSP_VALID_IRQ_MASK ; 
 int VX_INTCSR_VALUE ; 
 int VX_PCI_INTERRUPT_MASK ; 
 int /*<<< orphan*/  vx_outl (struct snd_vx222*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vx2_validate_irq(struct vx_core *_chip, int enable)
{
	struct snd_vx222 *chip = (struct snd_vx222 *)_chip;

	/* Set the interrupt enable bit to 1 in CDSP register */
	if (enable) {
		/* Set the PCI interrupt enable bit to 1.*/
		vx_outl(chip, INTCSR, VX_INTCSR_VALUE|VX_PCI_INTERRUPT_MASK);
		chip->regCDSP |= VX_CDSP_VALID_IRQ_MASK;
	} else {
		/* Set the PCI interrupt enable bit to 0. */
		vx_outl(chip, INTCSR, VX_INTCSR_VALUE&~VX_PCI_INTERRUPT_MASK);
		chip->regCDSP &= ~VX_CDSP_VALID_IRQ_MASK;
	}
	vx_outl(chip, CDSP, chip->regCDSP);
}