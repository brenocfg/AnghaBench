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
typedef  int u8 ;
struct oxygen {scalar_t__ dac_mute; } ;

/* Variables and functions */
 int CS4398_MUTEP_LOW ; 
 int CS4398_MUTE_A ; 
 int CS4398_MUTE_B ; 
 int CS4398_PAMUTE ; 
 int /*<<< orphan*/  cs4398_write_cached (struct oxygen*,int,int) ; 
 int /*<<< orphan*/  update_cs4362a_volumes (struct oxygen*) ; 

__attribute__((used)) static void update_cs43xx_mute(struct oxygen *chip)
{
	u8 reg;

	reg = CS4398_MUTEP_LOW | CS4398_PAMUTE;
	if (chip->dac_mute)
		reg |= CS4398_MUTE_B | CS4398_MUTE_A;
	cs4398_write_cached(chip, 4, reg);
	update_cs4362a_volumes(chip);
}