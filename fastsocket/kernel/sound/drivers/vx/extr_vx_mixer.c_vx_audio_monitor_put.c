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
struct vx_core {unsigned int* audio_monitor; int /*<<< orphan*/  mixer_mutex; int /*<<< orphan*/ * audio_monitor_active; } ;
struct snd_kcontrol {int private_value; } ;
struct TYPE_3__ {unsigned int* value; } ;
struct TYPE_4__ {TYPE_1__ integer; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;

/* Variables and functions */
 unsigned int CVAL_MAX ; 
 int EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct vx_core* snd_kcontrol_chip (struct snd_kcontrol*) ; 
 int /*<<< orphan*/  vx_set_monitor_level (struct vx_core*,int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vx_audio_monitor_put(struct snd_kcontrol *kcontrol, struct snd_ctl_elem_value *ucontrol)
{
	struct vx_core *chip = snd_kcontrol_chip(kcontrol);
	int audio = kcontrol->private_value & 0xff;
	unsigned int val[2];

	val[0] = ucontrol->value.integer.value[0];
	val[1] = ucontrol->value.integer.value[1];
	if (val[0] > CVAL_MAX || val[1] > CVAL_MAX)
		return -EINVAL;

	mutex_lock(&chip->mixer_mutex);
	if (val[0] != chip->audio_monitor[audio] ||
	    val[1] != chip->audio_monitor[audio+1]) {
		vx_set_monitor_level(chip, audio, val[0],
				     chip->audio_monitor_active[audio]);
		vx_set_monitor_level(chip, audio+1, val[1],
				     chip->audio_monitor_active[audio+1]);
		mutex_unlock(&chip->mixer_mutex);
		return 1;
	}
	mutex_unlock(&chip->mixer_mutex);
	return 0;
}