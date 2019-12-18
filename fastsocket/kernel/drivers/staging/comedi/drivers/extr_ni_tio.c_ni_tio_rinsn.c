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
struct ni_gpct_device {unsigned int* regs; } ;
struct ni_gpct {int /*<<< orphan*/  counter_index; struct ni_gpct_device* counter_dev; } ;
struct comedi_insn {int n; int /*<<< orphan*/  chanspec; } ;

/* Variables and functions */
 unsigned int CR_CHAN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Gi_Save_Trace_Bit ; 
 int /*<<< orphan*/  NITIO_Gi_Command_Reg (int /*<<< orphan*/ ) ; 
 size_t NITIO_Gi_LoadA_Reg (int /*<<< orphan*/ ) ; 
 size_t NITIO_Gi_LoadB_Reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NITIO_Gi_SW_Save_Reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_tio_set_bits (struct ni_gpct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int read_register (struct ni_gpct*,int /*<<< orphan*/ ) ; 

int ni_tio_rinsn(struct ni_gpct *counter, struct comedi_insn *insn,
		 unsigned int *data)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;
	const unsigned channel = CR_CHAN(insn->chanspec);
	unsigned first_read;
	unsigned second_read;
	unsigned correct_read;

	if (insn->n < 1)
		return 0;
	switch (channel) {
	case 0:
		ni_tio_set_bits(counter,
				NITIO_Gi_Command_Reg(counter->counter_index),
				Gi_Save_Trace_Bit, 0);
		ni_tio_set_bits(counter,
				NITIO_Gi_Command_Reg(counter->counter_index),
				Gi_Save_Trace_Bit, Gi_Save_Trace_Bit);
		/* The count doesn't get latched until the next clock edge, so it is possible the count
		   may change (once) while we are reading.  Since the read of the SW_Save_Reg isn't
		   atomic (apparently even when it's a 32 bit register according to 660x docs),
		   we need to read twice and make sure the reading hasn't changed.  If it has,
		   a third read will be correct since the count value will definitely have latched by then. */
		first_read =
		    read_register(counter,
				  NITIO_Gi_SW_Save_Reg(counter->counter_index));
		second_read =
		    read_register(counter,
				  NITIO_Gi_SW_Save_Reg(counter->counter_index));
		if (first_read != second_read)
			correct_read =
			    read_register(counter,
					  NITIO_Gi_SW_Save_Reg(counter->
							       counter_index));
		else
			correct_read = first_read;
		data[0] = correct_read;
		return 0;
		break;
	case 1:
		data[0] =
		    counter_dev->
		    regs[NITIO_Gi_LoadA_Reg(counter->counter_index)];
		break;
	case 2:
		data[0] =
		    counter_dev->
		    regs[NITIO_Gi_LoadB_Reg(counter->counter_index)];
		break;
	};
	return 0;
}