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
struct ni_gpct {int /*<<< orphan*/  counter_index; } ;
struct comedi_cmd {scalar_t__ scan_begin_src; unsigned int scan_begin_arg; scalar_t__ convert_src; unsigned int convert_arg; int flags; } ;
struct comedi_async {struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  Gi_Gate_Interrupt_Enable_Bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NITIO_Gi_Interrupt_Enable_Reg (int /*<<< orphan*/ ) ; 
 scalar_t__ TRIG_EXT ; 
 int TRIG_WAKE_EOS ; 
 int /*<<< orphan*/  ni_tio_set_bits (struct ni_gpct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ni_tio_set_gate_src (struct ni_gpct*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ni_tio_cmd_setup(struct ni_gpct *counter, struct comedi_async *async)
{
	struct comedi_cmd *cmd = &async->cmd;
	int set_gate_source = 0;
	unsigned gate_source;
	int retval = 0;

	if (cmd->scan_begin_src == TRIG_EXT) {
		set_gate_source = 1;
		gate_source = cmd->scan_begin_arg;
	} else if (cmd->convert_src == TRIG_EXT) {
		set_gate_source = 1;
		gate_source = cmd->convert_arg;
	}
	if (set_gate_source) {
		retval = ni_tio_set_gate_src(counter, 0, gate_source);
	}
	if (cmd->flags & TRIG_WAKE_EOS) {
		ni_tio_set_bits(counter,
				NITIO_Gi_Interrupt_Enable_Reg(counter->
							      counter_index),
				Gi_Gate_Interrupt_Enable_Bit(counter->
							     counter_index),
				Gi_Gate_Interrupt_Enable_Bit(counter->
							     counter_index));
	}
	return retval;
}