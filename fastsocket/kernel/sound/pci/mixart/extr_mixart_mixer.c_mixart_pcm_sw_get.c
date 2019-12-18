#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snd_mixart {TYPE_3__* mgr; int /*<<< orphan*/ ** digital_playback_active; } ;
struct snd_kcontrol {int private_value; } ;
struct TYPE_4__ {int /*<<< orphan*/ * value; } ;
struct TYPE_5__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int /*<<< orphan*/  mixer_mutex; } ;

/* Variables and functions */
 int MIXART_PLAYBACK_STREAMS ; 
 int MIXART_VOL_AES_MASK ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_BUG_ON (int) ; 
 int snd_ctl_get_ioffidx (struct snd_kcontrol*,int /*<<< orphan*/ *) ; 
 struct snd_mixart* snd_kcontrol_chip (struct snd_kcontrol*) ; 

__attribute__((used)) static int mixart_pcm_sw_get(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct snd_mixart *chip = snd_kcontrol_chip(kcontrol);
	int idx = snd_ctl_get_ioffidx(kcontrol, &ucontrol->id); /* index */
	snd_BUG_ON(idx >= MIXART_PLAYBACK_STREAMS);
	mutex_lock(&chip->mgr->mixer_mutex);
	if(kcontrol->private_value & MIXART_VOL_AES_MASK)	/* AES playback */
		idx += MIXART_PLAYBACK_STREAMS;
	ucontrol->value.integer.value[0] = chip->digital_playback_active[idx][0];
	ucontrol->value.integer.value[1] = chip->digital_playback_active[idx][1];
	mutex_unlock(&chip->mgr->mixer_mutex);
	return 0;
}