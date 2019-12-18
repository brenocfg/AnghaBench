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
 int EINVAL ; 
 int /*<<< orphan*/  Gi_Load_Bit ; 
 int /*<<< orphan*/  NITIO_Gi_Command_Reg (int /*<<< orphan*/ ) ; 
 size_t NITIO_Gi_LoadA_Reg (int /*<<< orphan*/ ) ; 
 size_t NITIO_Gi_LoadB_Reg (int /*<<< orphan*/ ) ; 
 unsigned int ni_tio_next_load_register (struct ni_gpct*) ; 
 int /*<<< orphan*/  ni_tio_set_bits_transient (struct ni_gpct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_register (struct ni_gpct*,unsigned int,size_t) ; 

int ni_tio_winsn(struct ni_gpct *counter, struct comedi_insn *insn,
		 unsigned int *data)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;
	const unsigned channel = CR_CHAN(insn->chanspec);
	unsigned load_reg;

	if (insn->n < 1)
		return 0;
	switch (channel) {
	case 0:
		/* Unsafe if counter is armed.  Should probably check status and return -EBUSY if armed. */
		/* Don't disturb load source select, just use whichever load register is already selected. */
		load_reg = ni_tio_next_load_register(counter);
		write_register(counter, data[0], load_reg);
		ni_tio_set_bits_transient(counter,
					  NITIO_Gi_Command_Reg(counter->
							       counter_index),
					  0, 0, Gi_Load_Bit);
		/* restore state of load reg to whatever the user set last set it to */
		write_register(counter, counter_dev->regs[load_reg], load_reg);
		break;
	case 1:
		counter_dev->regs[NITIO_Gi_LoadA_Reg(counter->counter_index)] =
		    data[0];
		write_register(counter, data[0],
			       NITIO_Gi_LoadA_Reg(counter->counter_index));
		break;
	case 2:
		counter_dev->regs[NITIO_Gi_LoadB_Reg(counter->counter_index)] =
		    data[0];
		write_register(counter, data[0],
			       NITIO_Gi_LoadB_Reg(counter->counter_index));
		break;
	default:
		return -EINVAL;
		break;
	}
	return 0;
}