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
struct TYPE_4__ {int /*<<< orphan*/  output_enable_bit; } ;
struct xonar_pcm179x {int dacs; int hp_gain_offset; TYPE_2__ generic; } ;
struct TYPE_3__ {int dac_channels_mixer; } ;
struct oxygen {int /*<<< orphan*/  card; TYPE_1__ model; struct xonar_pcm179x* model_data; } ;

/* Variables and functions */
 int GPIO_INPUT_ROUTE ; 
 int GPIO_ST_HP ; 
 int GPIO_ST_HP_REAR ; 
 int GPIO_ST_MAGIC ; 
 int /*<<< orphan*/  GPIO_ST_OUTPUT_ENABLE ; 
 int /*<<< orphan*/  OXYGEN_GPIO_CONTROL ; 
 int /*<<< orphan*/  OXYGEN_GPIO_DATA ; 
 int /*<<< orphan*/  oxygen_clear_bits16 (struct oxygen*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oxygen_set_bits16 (struct oxygen*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcm1796_init (struct oxygen*) ; 
 int /*<<< orphan*/  snd_component_add (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xonar_enable_output (struct oxygen*) ; 
 int /*<<< orphan*/  xonar_init_cs53x1 (struct oxygen*) ; 

__attribute__((used)) static void xonar_st_init_common(struct oxygen *chip)
{
	struct xonar_pcm179x *data = chip->model_data;

	data->generic.output_enable_bit = GPIO_ST_OUTPUT_ENABLE;
	data->dacs = chip->model.dac_channels_mixer / 2;
	data->hp_gain_offset = 2*-18;

	pcm1796_init(chip);

	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTROL,
			  GPIO_INPUT_ROUTE | GPIO_ST_HP_REAR |
			  GPIO_ST_MAGIC | GPIO_ST_HP);
	oxygen_clear_bits16(chip, OXYGEN_GPIO_DATA,
			    GPIO_INPUT_ROUTE | GPIO_ST_HP_REAR | GPIO_ST_HP);

	xonar_init_cs53x1(chip);
	xonar_enable_output(chip);

	snd_component_add(chip->card, "PCM1792A");
	snd_component_add(chip->card, "CS5381");
}