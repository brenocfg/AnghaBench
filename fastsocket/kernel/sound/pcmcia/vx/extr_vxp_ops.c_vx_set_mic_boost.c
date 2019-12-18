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
struct vx_core {int chip_status; int /*<<< orphan*/  lock; } ;
struct snd_vxpocket {int regCDSP; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDSP ; 
 int P24_CDSP_MIC20_SEL_MASK ; 
 int P24_CDSP_MIC38_SEL_MASK ; 
 int P24_CDSP_MICS_SEL_MASK ; 
 int VX_STAT_IS_STALE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vx_outb (struct vx_core*,int /*<<< orphan*/ ,int) ; 

void vx_set_mic_boost(struct vx_core *chip, int boost)
{
	struct snd_vxpocket *pchip = (struct snd_vxpocket *)chip;
	unsigned long flags;

	if (chip->chip_status & VX_STAT_IS_STALE)
		return;

	spin_lock_irqsave(&chip->lock, flags);
	if (pchip->regCDSP & P24_CDSP_MICS_SEL_MASK) {
		if (boost) {
			/* boost: 38 dB */
			pchip->regCDSP &= ~P24_CDSP_MIC20_SEL_MASK;
			pchip->regCDSP |=  P24_CDSP_MIC38_SEL_MASK;
		} else {
			/* minimum value: 20 dB */
			pchip->regCDSP |=  P24_CDSP_MIC20_SEL_MASK;
			pchip->regCDSP &= ~P24_CDSP_MIC38_SEL_MASK;
                }
		vx_outb(chip, CDSP, pchip->regCDSP);
	}
	spin_unlock_irqrestore(&chip->lock, flags);
}