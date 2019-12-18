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
struct oxygen {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 unsigned int AC97_LINE ; 
 int /*<<< orphan*/  GPIO_D1_INPUT_ROUTE ; 
 int /*<<< orphan*/  OXYGEN_GPIO_DATA ; 
 int /*<<< orphan*/  oxygen_write16_masked (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void xonar_d1_line_mic_ac97_switch(struct oxygen *chip,
					  unsigned int reg, unsigned int mute)
{
	if (reg == AC97_LINE) {
		spin_lock_irq(&chip->reg_lock);
		oxygen_write16_masked(chip, OXYGEN_GPIO_DATA,
				      mute ? GPIO_D1_INPUT_ROUTE : 0,
				      GPIO_D1_INPUT_ROUTE);
		spin_unlock_irq(&chip->reg_lock);
	}
}