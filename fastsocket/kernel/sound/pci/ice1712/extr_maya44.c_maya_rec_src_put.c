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
struct snd_maya44 {int /*<<< orphan*/  mutex; int /*<<< orphan*/  ice; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 int GPIO_MIC_RELAY ; 
 int /*<<< orphan*/  MAYA_LINE_IN ; 
 int /*<<< orphan*/  MAYA_MIC_IN ; 
 int maya_set_gpio_bits (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct snd_maya44* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  wm8776_select_input (struct snd_maya44*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int maya_rec_src_put(struct snd_kcontrol *kcontrol,
			    struct snd_ctl_elem_value *ucontrol)
{
	struct snd_maya44 *chip = snd_kcontrol_chip(kcontrol);
	int sel = ucontrol->value.enumerated.item[0];
	int changed;

	mutex_lock(&chip->mutex);
	changed = maya_set_gpio_bits(chip->ice, 1 << GPIO_MIC_RELAY,
				     sel ? (1 << GPIO_MIC_RELAY) : 0);
	wm8776_select_input(chip, 0, sel ? MAYA_MIC_IN : MAYA_LINE_IN);
	mutex_unlock(&chip->mutex);
	return changed;
}