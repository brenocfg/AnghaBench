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
struct snd_wss {int* image; int /*<<< orphan*/  reg_lock; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_4__ {int* item; } ;
struct TYPE_3__ {TYPE_2__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;

/* Variables and functions */
 size_t CS4231_LEFT_INPUT ; 
 int CS4231_MIXS_ALL ; 
 size_t CS4231_RIGHT_INPUT ; 
 struct snd_wss* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int snd_wss_get_mux(struct snd_kcontrol *kcontrol,
			   struct snd_ctl_elem_value *ucontrol)
{
	struct snd_wss *chip = snd_kcontrol_chip(kcontrol);
	unsigned long flags;

	spin_lock_irqsave(&chip->reg_lock, flags);
	ucontrol->value.enumerated.item[0] = (chip->image[CS4231_LEFT_INPUT] & CS4231_MIXS_ALL) >> 6;
	ucontrol->value.enumerated.item[1] = (chip->image[CS4231_RIGHT_INPUT] & CS4231_MIXS_ALL) >> 6;
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	return 0;
}