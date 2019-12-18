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
struct ni_gpct_device {int* regs; } ;
struct ni_gpct {int /*<<< orphan*/  counter_index; struct ni_gpct_device* counter_dev; } ;

/* Variables and functions */
 int Gi_Synchronize_Gate_Bit ; 
 size_t NITIO_Gi_Autoincrement_Reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NITIO_Gi_Command_Reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NITIO_Gi_Counting_Mode_Reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NITIO_Gi_DMA_Config_Reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NITIO_Gi_Input_Select_Reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NITIO_Gi_Interrupt_Enable_Reg (int /*<<< orphan*/ ) ; 
 size_t NITIO_Gi_LoadA_Reg (int /*<<< orphan*/ ) ; 
 size_t NITIO_Gi_LoadB_Reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NITIO_Gi_Mode_Reg (int /*<<< orphan*/ ) ; 
 size_t NITIO_Gi_Second_Gate_Reg (int /*<<< orphan*/ ) ; 
 scalar_t__ ni_tio_counting_mode_registers_present (struct ni_gpct_device*) ; 
 int /*<<< orphan*/  ni_tio_reset_count_and_disarm (struct ni_gpct*) ; 
 scalar_t__ ni_tio_second_gate_registers_present (struct ni_gpct_device*) ; 
 int /*<<< orphan*/  ni_tio_set_bits (struct ni_gpct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_register (struct ni_gpct*,int,size_t) ; 

void ni_tio_init_counter(struct ni_gpct *counter)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;

	ni_tio_reset_count_and_disarm(counter);
	/* initialize counter registers */
	counter_dev->regs[NITIO_Gi_Autoincrement_Reg(counter->counter_index)] =
	    0x0;
	write_register(counter,
		       counter_dev->
		       regs[NITIO_Gi_Autoincrement_Reg(counter->counter_index)],
		       NITIO_Gi_Autoincrement_Reg(counter->counter_index));
	ni_tio_set_bits(counter, NITIO_Gi_Command_Reg(counter->counter_index),
			~0, Gi_Synchronize_Gate_Bit);
	ni_tio_set_bits(counter, NITIO_Gi_Mode_Reg(counter->counter_index), ~0,
			0);
	counter_dev->regs[NITIO_Gi_LoadA_Reg(counter->counter_index)] = 0x0;
	write_register(counter,
		       counter_dev->
		       regs[NITIO_Gi_LoadA_Reg(counter->counter_index)],
		       NITIO_Gi_LoadA_Reg(counter->counter_index));
	counter_dev->regs[NITIO_Gi_LoadB_Reg(counter->counter_index)] = 0x0;
	write_register(counter,
		       counter_dev->
		       regs[NITIO_Gi_LoadB_Reg(counter->counter_index)],
		       NITIO_Gi_LoadB_Reg(counter->counter_index));
	ni_tio_set_bits(counter,
			NITIO_Gi_Input_Select_Reg(counter->counter_index), ~0,
			0);
	if (ni_tio_counting_mode_registers_present(counter_dev)) {
		ni_tio_set_bits(counter,
				NITIO_Gi_Counting_Mode_Reg(counter->
							   counter_index), ~0,
				0);
	}
	if (ni_tio_second_gate_registers_present(counter_dev)) {
		counter_dev->
		    regs[NITIO_Gi_Second_Gate_Reg(counter->counter_index)] =
		    0x0;
		write_register(counter,
			       counter_dev->
			       regs[NITIO_Gi_Second_Gate_Reg
				    (counter->counter_index)],
			       NITIO_Gi_Second_Gate_Reg(counter->
							counter_index));
	}
	ni_tio_set_bits(counter,
			NITIO_Gi_DMA_Config_Reg(counter->counter_index), ~0,
			0x0);
	ni_tio_set_bits(counter,
			NITIO_Gi_Interrupt_Enable_Reg(counter->counter_index),
			~0, 0x0);
}