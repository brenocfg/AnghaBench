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
 int VX_CDSP_DSP_RESET_MASK ; 
 int /*<<< orphan*/  XX_DSP_RESET_WAIT_TIME ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vx_outl (struct snd_vx222*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vx2_reset_dsp(struct vx_core *_chip)
{
	struct snd_vx222 *chip = (struct snd_vx222 *)_chip;

	/* set the reset dsp bit to 0 */
	vx_outl(chip, CDSP, chip->regCDSP & ~VX_CDSP_DSP_RESET_MASK);

	mdelay(XX_DSP_RESET_WAIT_TIME);

	chip->regCDSP |= VX_CDSP_DSP_RESET_MASK;
	/* set the reset dsp bit to 1 */
	vx_outl(chip, CDSP, chip->regCDSP);
}