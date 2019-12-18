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
struct snd_vx222 {int regCDSP; scalar_t__ regCFG; } ;

/* Variables and functions */
 int VX_CDSP_CODEC_RESET_MASK ; 
 int VX_CDSP_DSP_RESET_MASK ; 

__attribute__((used)) static void vx2_reset_board(struct vx_core *_chip, int cold_reset)
{
	struct snd_vx222 *chip = (struct snd_vx222 *)_chip;

	/* initialize the register values */
	chip->regCDSP = VX_CDSP_CODEC_RESET_MASK | VX_CDSP_DSP_RESET_MASK ;
	chip->regCFG = 0;
}