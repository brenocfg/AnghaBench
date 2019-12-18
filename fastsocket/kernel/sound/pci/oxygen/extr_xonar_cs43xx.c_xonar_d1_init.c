#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int anti_pop_delay; int /*<<< orphan*/  output_enable_bit; } ;
struct xonar_cs43xx {int* cs4398_regs; int* cs4362a_regs; TYPE_1__ generic; } ;
struct oxygen {int /*<<< orphan*/  card; struct xonar_cs43xx* model_data; } ;

/* Variables and functions */
 int CS4362A_ATAPI_A_L ; 
 int CS4362A_ATAPI_B_R ; 
 int CS4362A_DEM_NONE ; 
 int CS4362A_FM_SINGLE ; 
 int CS4362A_MUTE ; 
 int CS4362A_RMP_DN ; 
 int CS4398_DEM_NONE ; 
 int CS4398_DIF_LJUST ; 
 int CS4398_FM_SINGLE ; 
 int CS4398_MUTEP_LOW ; 
 int CS4398_MUTE_A ; 
 int CS4398_MUTE_B ; 
 int CS4398_PAMUTE ; 
 int CS4398_RMP_DN ; 
 int CS4398_RMP_UP ; 
 int CS4398_SOFT_RAMP ; 
 int CS4398_ZERO_CROSS ; 
 int GPIO_D1_FRONT_PANEL ; 
 int GPIO_D1_INPUT_ROUTE ; 
 int GPIO_D1_MAGIC ; 
 int /*<<< orphan*/  GPIO_D1_OUTPUT_ENABLE ; 
 int /*<<< orphan*/  OXYGEN_2WIRE_BUS_STATUS ; 
 int OXYGEN_2WIRE_INTERRUPT_MASK ; 
 int OXYGEN_2WIRE_LENGTH_8 ; 
 int OXYGEN_2WIRE_SPEED_FAST ; 
 int /*<<< orphan*/  OXYGEN_GPIO_CONTROL ; 
 int /*<<< orphan*/  OXYGEN_GPIO_DATA ; 
 int /*<<< orphan*/  cs43xx_registers_init (struct oxygen*) ; 
 int /*<<< orphan*/  oxygen_clear_bits16 (struct oxygen*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oxygen_set_bits16 (struct oxygen*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  oxygen_write16 (struct oxygen*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_component_add (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xonar_enable_output (struct oxygen*) ; 
 int /*<<< orphan*/  xonar_init_cs53x1 (struct oxygen*) ; 

__attribute__((used)) static void xonar_d1_init(struct oxygen *chip)
{
	struct xonar_cs43xx *data = chip->model_data;

	data->generic.anti_pop_delay = 800;
	data->generic.output_enable_bit = GPIO_D1_OUTPUT_ENABLE;
	data->cs4398_regs[2] =
		CS4398_FM_SINGLE | CS4398_DEM_NONE | CS4398_DIF_LJUST;
	data->cs4398_regs[4] = CS4398_MUTEP_LOW |
		CS4398_MUTE_B | CS4398_MUTE_A | CS4398_PAMUTE;
	data->cs4398_regs[5] = 60 * 2;
	data->cs4398_regs[6] = 60 * 2;
	data->cs4398_regs[7] = CS4398_RMP_DN | CS4398_RMP_UP |
		CS4398_ZERO_CROSS | CS4398_SOFT_RAMP;
	data->cs4362a_regs[4] = CS4362A_RMP_DN | CS4362A_DEM_NONE;
	data->cs4362a_regs[6] = CS4362A_FM_SINGLE |
		CS4362A_ATAPI_B_R | CS4362A_ATAPI_A_L;
	data->cs4362a_regs[7] = 60 | CS4362A_MUTE;
	data->cs4362a_regs[8] = 60 | CS4362A_MUTE;
	data->cs4362a_regs[9] = data->cs4362a_regs[6];
	data->cs4362a_regs[10] = 60 | CS4362A_MUTE;
	data->cs4362a_regs[11] = 60 | CS4362A_MUTE;
	data->cs4362a_regs[12] = data->cs4362a_regs[6];
	data->cs4362a_regs[13] = 60 | CS4362A_MUTE;
	data->cs4362a_regs[14] = 60 | CS4362A_MUTE;

	oxygen_write16(chip, OXYGEN_2WIRE_BUS_STATUS,
		       OXYGEN_2WIRE_LENGTH_8 |
		       OXYGEN_2WIRE_INTERRUPT_MASK |
		       OXYGEN_2WIRE_SPEED_FAST);

	cs43xx_registers_init(chip);

	oxygen_set_bits16(chip, OXYGEN_GPIO_CONTROL,
			  GPIO_D1_FRONT_PANEL |
			  GPIO_D1_MAGIC |
			  GPIO_D1_INPUT_ROUTE);
	oxygen_clear_bits16(chip, OXYGEN_GPIO_DATA,
			    GPIO_D1_FRONT_PANEL | GPIO_D1_INPUT_ROUTE);

	xonar_init_cs53x1(chip);
	xonar_enable_output(chip);

	snd_component_add(chip->card, "CS4398");
	snd_component_add(chip->card, "CS4362A");
	snd_component_add(chip->card, "CS5361");
}