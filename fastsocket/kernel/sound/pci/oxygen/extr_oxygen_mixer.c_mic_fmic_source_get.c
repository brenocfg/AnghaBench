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
struct snd_kcontrol {struct oxygen* private_data; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct oxygen {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int CM9780_FMIC2MIC ; 
 int /*<<< orphan*/  CM9780_JACK ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int oxygen_read_ac97 (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mic_fmic_source_get(struct snd_kcontrol *ctl,
			       struct snd_ctl_elem_value *value)
{
	struct oxygen *chip = ctl->private_data;

	mutex_lock(&chip->mutex);
	value->value.enumerated.item[0] =
		!!(oxygen_read_ac97(chip, 0, CM9780_JACK) & CM9780_FMIC2MIC);
	mutex_unlock(&chip->mutex);
	return 0;
}