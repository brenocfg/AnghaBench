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
struct oxygen {int /*<<< orphan*/  card; struct dg* model_data; } ;
struct dg {int* cs4245_regs; } ;

/* Variables and functions */
 size_t CS4245_ADC_CTRL ; 
 int CS4245_ADC_DIF_LJUST ; 
 int CS4245_ADC_FM_SINGLE ; 
 size_t CS4245_ANALOG_IN ; 
 int CS4245_ASYNCH ; 
 int CS4245_A_OUT_SEL_HIZ ; 
 size_t CS4245_DAC_A_CTRL ; 
 size_t CS4245_DAC_B_CTRL ; 
 size_t CS4245_DAC_CTRL_1 ; 
 int CS4245_DAC_DIF_LJUST ; 
 int CS4245_DAC_FM_SINGLE ; 
 size_t CS4245_PGA_A_CTRL ; 
 size_t CS4245_PGA_B_CTRL ; 
 int CS4245_PGA_SOFT ; 
 int CS4245_PGA_ZERO ; 
 int CS4245_SEL_INPUT_4 ; 
 size_t CS4245_SIGNAL_SEL ; 
 int /*<<< orphan*/  cs4245_registers_init (struct oxygen*) ; 
 int /*<<< orphan*/  snd_component_add (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void cs4245_init(struct oxygen *chip)
{
	struct dg *data = chip->model_data;

	data->cs4245_regs[CS4245_DAC_CTRL_1] =
		CS4245_DAC_FM_SINGLE | CS4245_DAC_DIF_LJUST;
	data->cs4245_regs[CS4245_ADC_CTRL] =
		CS4245_ADC_FM_SINGLE | CS4245_ADC_DIF_LJUST;
	data->cs4245_regs[CS4245_SIGNAL_SEL] =
		CS4245_A_OUT_SEL_HIZ | CS4245_ASYNCH;
	data->cs4245_regs[CS4245_PGA_B_CTRL] = 0;
	data->cs4245_regs[CS4245_PGA_A_CTRL] = 0;
	data->cs4245_regs[CS4245_ANALOG_IN] =
		CS4245_PGA_SOFT | CS4245_PGA_ZERO | CS4245_SEL_INPUT_4;
	data->cs4245_regs[CS4245_DAC_A_CTRL] = 0;
	data->cs4245_regs[CS4245_DAC_B_CTRL] = 0;
	cs4245_registers_init(chip);
	snd_component_add(chip->card, "CS4245");
}