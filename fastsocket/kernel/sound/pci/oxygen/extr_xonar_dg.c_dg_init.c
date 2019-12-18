#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct oxygen {struct dg* model_data; } ;
struct dg {int input_sel; int hp_vol_att; scalar_t__ output_sel; } ;

/* Variables and functions */
 int GPIO_HP_DETECT ; 
 int GPIO_HP_REAR ; 
 int GPIO_INPUT_ROUTE ; 
 int GPIO_MAGIC ; 
 int GPIO_OUTPUT_ENABLE ; 
 int /*<<< orphan*/  OXYGEN_GPIO_CONTROL ; 
 int /*<<< orphan*/  OXYGEN_GPIO_DATA ; 
 int /*<<< orphan*/  cs4245_init (struct oxygen*) ; 
 int /*<<< orphan*/  dg_output_enable (struct oxygen*) ; 
 int /*<<< orphan*/  oxygen_clear_bits16 (struct oxygen*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oxygen_set_bits16 (struct oxygen*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dg_init(struct oxygen *chip)
{
	struct dg *data = chip->model_data;

	data->output_sel = 0;
	data->input_sel = 3;
	data->hp_vol_att = 2 * 16;

	cs4245_init(chip);

	oxygen_clear_bits16(chip, OXYGEN_GPIO_CONTROL,
			    GPIO_MAGIC | GPIO_HP_DETECT);
	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTROL,
			  GPIO_INPUT_ROUTE | GPIO_HP_REAR | GPIO_OUTPUT_ENABLE);
	oxygen_clear_bits16(chip, OXYGEN_GPIO_DATA,
			    GPIO_INPUT_ROUTE | GPIO_HP_REAR);
	dg_output_enable(chip);
}