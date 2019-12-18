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
struct oxygen {int /*<<< orphan*/  mutex; struct dg* model_data; } ;
struct dg {int hp_vol_att; scalar_t__ output_sel; } ;
typedef  int s8 ;

/* Variables and functions */
 int /*<<< orphan*/  CS4245_DAC_A_CTRL ; 
 int /*<<< orphan*/  CS4245_DAC_B_CTRL ; 
 int EINVAL ; 
 int /*<<< orphan*/  cs4245_write_cached (struct oxygen*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hp_volume_offset_put(struct snd_kcontrol *ctl,
				struct snd_ctl_elem_value *value)
{
	static const s8 atts[3] = { 2 * 16, 2 * 7, 0 };
	struct oxygen *chip = ctl->private_data;
	struct dg *data = chip->model_data;
	s8 att;
	int changed;

	if (value->value.enumerated.item[0] > 2)
		return -EINVAL;
	att = atts[value->value.enumerated.item[0]];
	mutex_lock(&chip->mutex);
	changed = att != data->hp_vol_att;
	if (changed) {
		data->hp_vol_att = att;
		if (data->output_sel) {
			cs4245_write_cached(chip, CS4245_DAC_A_CTRL, att);
			cs4245_write_cached(chip, CS4245_DAC_B_CTRL, att);
		}
	}
	mutex_unlock(&chip->mutex);
	return changed;
}