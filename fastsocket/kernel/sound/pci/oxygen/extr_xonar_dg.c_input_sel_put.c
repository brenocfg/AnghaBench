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
typedef  int u8 ;
struct snd_kcontrol {struct oxygen* private_data; } ;
struct TYPE_3__ {int* item; } ;
struct TYPE_4__ {TYPE_1__ enumerated; } ;
struct snd_ctl_elem_value {TYPE_2__ value; } ;
struct oxygen {int /*<<< orphan*/  mutex; struct dg* model_data; } ;
struct dg {size_t input_sel; int const* cs4245_regs; int /*<<< orphan*/ ** input_vol; } ;

/* Variables and functions */
 size_t CS4245_ANALOG_IN ; 
 int /*<<< orphan*/  CS4245_PGA_A_CTRL ; 
 int /*<<< orphan*/  CS4245_PGA_B_CTRL ; 
#define  CS4245_SEL_INPUT_1 131 
#define  CS4245_SEL_INPUT_2 130 
#define  CS4245_SEL_INPUT_4 129 
 int const CS4245_SEL_MASK ; 
#define  CS4245_SEL_MIC 128 
 int EINVAL ; 
 int /*<<< orphan*/  GPIO_INPUT_ROUTE ; 
 int /*<<< orphan*/  OXYGEN_GPIO_DATA ; 
 int /*<<< orphan*/  cs4245_write (struct oxygen*,size_t,int const) ; 
 int /*<<< orphan*/  cs4245_write_cached (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oxygen_write16_masked (struct oxygen*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int input_sel_put(struct snd_kcontrol *ctl,
			 struct snd_ctl_elem_value *value)
{
	static const u8 sel_values[4] = {
		CS4245_SEL_MIC,
		CS4245_SEL_INPUT_1,
		CS4245_SEL_INPUT_2,
		CS4245_SEL_INPUT_4
	};
	struct oxygen *chip = ctl->private_data;
	struct dg *data = chip->model_data;
	int changed;

	if (value->value.enumerated.item[0] > 3)
		return -EINVAL;

	mutex_lock(&chip->mutex);
	changed = value->value.enumerated.item[0] != data->input_sel;
	if (changed) {
		data->input_sel = value->value.enumerated.item[0];

		cs4245_write(chip, CS4245_ANALOG_IN,
			     (data->cs4245_regs[CS4245_ANALOG_IN] &
							~CS4245_SEL_MASK) |
			     sel_values[data->input_sel]);

		cs4245_write_cached(chip, CS4245_PGA_A_CTRL,
				    data->input_vol[data->input_sel][0]);
		cs4245_write_cached(chip, CS4245_PGA_B_CTRL,
				    data->input_vol[data->input_sel][1]);

		oxygen_write16_masked(chip, OXYGEN_GPIO_DATA,
				      data->input_sel ? 0 : GPIO_INPUT_ROUTE,
				      GPIO_INPUT_ROUTE);
	}
	mutex_unlock(&chip->mutex);
	return changed;
}