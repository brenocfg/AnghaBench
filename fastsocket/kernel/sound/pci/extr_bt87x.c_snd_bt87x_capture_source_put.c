#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct snd_bt87x {int reg_control; int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int CTL_A_SEL_MASK ; 
 int CTL_A_SEL_SHIFT ; 
 int /*<<< orphan*/  REG_GPIO_DMA_CTL ; 
 int /*<<< orphan*/  snd_bt87x_writel (struct snd_bt87x*,int /*<<< orphan*/ ,int) ; 
 struct snd_bt87x* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_bt87x_capture_source_put(struct snd_kcontrol *kcontrol,
					struct snd_ctl_elem_value *value)
{
	struct snd_bt87x *chip = snd_kcontrol_chip(kcontrol);
	u32 old_control;
	int changed;

	spin_lock_irq(&chip->reg_lock);
	old_control = chip->reg_control;
	chip->reg_control = (chip->reg_control & ~CTL_A_SEL_MASK)
		| (value->value.enumerated.item[0] << CTL_A_SEL_SHIFT);
	snd_bt87x_writel(chip, REG_GPIO_DMA_CTL, chip->reg_control);
	changed = chip->reg_control != old_control;
	spin_unlock_irq(&chip->reg_lock);
	return changed;
}