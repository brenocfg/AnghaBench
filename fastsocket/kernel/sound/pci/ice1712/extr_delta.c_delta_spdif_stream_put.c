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
struct TYPE_4__ {unsigned int cs8403_stream_bits; } ;
struct snd_ice1712 {int /*<<< orphan*/  reg_lock; int /*<<< orphan*/ * playback_pro_substream; TYPE_2__ spdif; } ;
struct TYPE_3__ {int /*<<< orphan*/  iec958; } ;
struct snd_ctl_elem_value {TYPE_1__ value; } ;

/* Variables and functions */
 unsigned int snd_cs8403_encode_spdif_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_ice1712_delta_cs8403_spdif_write (struct snd_ice1712*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int delta_spdif_stream_put(struct snd_ice1712 *ice, struct snd_ctl_elem_value *ucontrol)
{
	unsigned int val;
	int change;

	val = snd_cs8403_encode_spdif_bits(&ucontrol->value.iec958);
	spin_lock_irq(&ice->reg_lock);
	change = ice->spdif.cs8403_stream_bits != val;
	ice->spdif.cs8403_stream_bits = val;
	if (change && ice->playback_pro_substream != NULL) {
		spin_unlock_irq(&ice->reg_lock);
		snd_ice1712_delta_cs8403_spdif_write(ice, val);
	} else {
		spin_unlock_irq(&ice->reg_lock);
	}
	return change;
}