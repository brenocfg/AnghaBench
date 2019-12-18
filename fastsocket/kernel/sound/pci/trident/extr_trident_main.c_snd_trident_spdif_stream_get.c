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
struct snd_trident {int spdif_pcm_bits; int /*<<< orphan*/  reg_lock; } ;
struct snd_kcontrol {int dummy; } ;
struct TYPE_3__ {int* status; } ;
struct TYPE_4__ {TYPE_1__ iec958; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 struct snd_trident* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int snd_trident_spdif_stream_get(struct snd_kcontrol *kcontrol,
					struct snd_ctl_elem_value *ucontrol)
{
	struct snd_trident *trident = snd_kcontrol_chip(kcontrol);

	spin_lock_irq(&trident->reg_lock);
	ucontrol->value.iec958.status[0] = (trident->spdif_pcm_bits >> 0) & 0xff;
	ucontrol->value.iec958.status[1] = (trident->spdif_pcm_bits >> 8) & 0xff;
	ucontrol->value.iec958.status[2] = (trident->spdif_pcm_bits >> 16) & 0xff;
	ucontrol->value.iec958.status[3] = (trident->spdif_pcm_bits >> 24) & 0xff;
	spin_unlock_irq(&trident->reg_lock);
	return 0;
}