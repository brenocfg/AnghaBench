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
struct snd_vxpocket {int /*<<< orphan*/  regCDSP; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDSP ; 
 int /*<<< orphan*/  VXP_CDSP_VALID_IRQ_MASK ; 
 int /*<<< orphan*/  vx_outb (struct snd_vxpocket*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vxp_validate_irq(struct vx_core *_chip, int enable)
{
	struct snd_vxpocket *chip = (struct snd_vxpocket *)_chip;

	/* Set the interrupt enable bit to 1 in CDSP register */
	if (enable)
		chip->regCDSP |= VXP_CDSP_VALID_IRQ_MASK;
	else
		chip->regCDSP &= ~VXP_CDSP_VALID_IRQ_MASK;
	vx_outb(chip, CDSP, chip->regCDSP);
}