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
struct snd_pdacf {int /*<<< orphan*/ * regmap; int /*<<< orphan*/  ak4117; int /*<<< orphan*/  suspend_reg_scr; } ;

/* Variables and functions */
 int PDAUDIOCF_REG_IER ; 
 int PDAUDIOCF_REG_SCR ; 
 int PDAUDIOCF_REG_TCR ; 
 int /*<<< orphan*/  pdacf_reg_write (struct snd_pdacf*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdacf_reset (struct snd_pdacf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ak4117_reinit (int /*<<< orphan*/ ) ; 

void pdacf_reinit(struct snd_pdacf *chip, int resume)
{
	pdacf_reset(chip, 0);
	if (resume)
		pdacf_reg_write(chip, PDAUDIOCF_REG_SCR, chip->suspend_reg_scr);
	snd_ak4117_reinit(chip->ak4117);
	pdacf_reg_write(chip, PDAUDIOCF_REG_TCR, chip->regmap[PDAUDIOCF_REG_TCR>>1]);
	pdacf_reg_write(chip, PDAUDIOCF_REG_IER, chip->regmap[PDAUDIOCF_REG_IER>>1]);
}