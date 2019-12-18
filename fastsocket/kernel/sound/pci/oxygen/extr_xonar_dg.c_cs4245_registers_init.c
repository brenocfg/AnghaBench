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
struct dg {int* cs4245_regs; } ;

/* Variables and functions */
 size_t CS4245_ADC_CTRL ; 
 size_t CS4245_ANALOG_IN ; 
 size_t CS4245_DAC_A_CTRL ; 
 size_t CS4245_DAC_B_CTRL ; 
 size_t CS4245_DAC_CTRL_1 ; 
 size_t CS4245_DAC_CTRL_2 ; 
 int CS4245_DAC_SOFT ; 
 int CS4245_DAC_ZERO ; 
 size_t CS4245_INT_MASK ; 
 int CS4245_INVERT_DAC ; 
 int CS4245_PDN ; 
 size_t CS4245_PGA_A_CTRL ; 
 size_t CS4245_PGA_B_CTRL ; 
 size_t CS4245_POWER_CTRL ; 
 size_t CS4245_SIGNAL_SEL ; 
 int /*<<< orphan*/  cs4245_write (struct oxygen*,size_t,int) ; 

__attribute__((used)) static void cs4245_registers_init(struct oxygen *chip)
{
	struct dg *data = chip->model_data;

	cs4245_write(chip, CS4245_POWER_CTRL, CS4245_PDN);
	cs4245_write(chip, CS4245_DAC_CTRL_1,
		     data->cs4245_regs[CS4245_DAC_CTRL_1]);
	cs4245_write(chip, CS4245_ADC_CTRL,
		     data->cs4245_regs[CS4245_ADC_CTRL]);
	cs4245_write(chip, CS4245_SIGNAL_SEL,
		     data->cs4245_regs[CS4245_SIGNAL_SEL]);
	cs4245_write(chip, CS4245_PGA_B_CTRL,
		     data->cs4245_regs[CS4245_PGA_B_CTRL]);
	cs4245_write(chip, CS4245_PGA_A_CTRL,
		     data->cs4245_regs[CS4245_PGA_A_CTRL]);
	cs4245_write(chip, CS4245_ANALOG_IN,
		     data->cs4245_regs[CS4245_ANALOG_IN]);
	cs4245_write(chip, CS4245_DAC_A_CTRL,
		     data->cs4245_regs[CS4245_DAC_A_CTRL]);
	cs4245_write(chip, CS4245_DAC_B_CTRL,
		     data->cs4245_regs[CS4245_DAC_B_CTRL]);
	cs4245_write(chip, CS4245_DAC_CTRL_2,
		     CS4245_DAC_SOFT | CS4245_DAC_ZERO | CS4245_INVERT_DAC);
	cs4245_write(chip, CS4245_INT_MASK, 0);
	cs4245_write(chip, CS4245_POWER_CTRL, 0);
}