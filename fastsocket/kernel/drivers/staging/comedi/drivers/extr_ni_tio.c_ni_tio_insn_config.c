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
struct ni_gpct {int dummy; } ;
struct comedi_insn {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  INSN_CONFIG_ARM 137 
#define  INSN_CONFIG_DISARM 136 
#define  INSN_CONFIG_GET_CLOCK_SRC 135 
#define  INSN_CONFIG_GET_COUNTER_STATUS 134 
#define  INSN_CONFIG_GET_GATE_SRC 133 
#define  INSN_CONFIG_RESET 132 
#define  INSN_CONFIG_SET_CLOCK_SRC 131 
#define  INSN_CONFIG_SET_COUNTER_MODE 130 
#define  INSN_CONFIG_SET_GATE_SRC 129 
#define  INSN_CONFIG_SET_OTHER_SRC 128 
 unsigned int counter_status_mask ; 
 int ni_tio_arm (struct ni_gpct*,int,unsigned int) ; 
 unsigned int ni_tio_counter_status (struct ni_gpct*) ; 
 int /*<<< orphan*/  ni_tio_get_clock_src (struct ni_gpct*,unsigned int*,unsigned int*) ; 
 int ni_tio_get_gate_src (struct ni_gpct*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  ni_tio_reset_count_and_disarm (struct ni_gpct*) ; 
 int ni_tio_set_clock_src (struct ni_gpct*,unsigned int,unsigned int) ; 
 int ni_tio_set_counter_mode (struct ni_gpct*,unsigned int) ; 
 int ni_tio_set_gate_src (struct ni_gpct*,unsigned int,unsigned int) ; 
 int ni_tio_set_other_src (struct ni_gpct*,unsigned int,unsigned int) ; 

int ni_tio_insn_config(struct ni_gpct *counter,
		       struct comedi_insn *insn, unsigned int *data)
{
	switch (data[0]) {
	case INSN_CONFIG_SET_COUNTER_MODE:
		return ni_tio_set_counter_mode(counter, data[1]);
		break;
	case INSN_CONFIG_ARM:
		return ni_tio_arm(counter, 1, data[1]);
		break;
	case INSN_CONFIG_DISARM:
		ni_tio_arm(counter, 0, 0);
		return 0;
		break;
	case INSN_CONFIG_GET_COUNTER_STATUS:
		data[1] = ni_tio_counter_status(counter);
		data[2] = counter_status_mask;
		return 0;
		break;
	case INSN_CONFIG_SET_CLOCK_SRC:
		return ni_tio_set_clock_src(counter, data[1], data[2]);
		break;
	case INSN_CONFIG_GET_CLOCK_SRC:
		ni_tio_get_clock_src(counter, &data[1], &data[2]);
		return 0;
		break;
	case INSN_CONFIG_SET_GATE_SRC:
		return ni_tio_set_gate_src(counter, data[1], data[2]);
		break;
	case INSN_CONFIG_GET_GATE_SRC:
		return ni_tio_get_gate_src(counter, data[1], &data[2]);
		break;
	case INSN_CONFIG_SET_OTHER_SRC:
		return ni_tio_set_other_src(counter, data[1], data[2]);
		break;
	case INSN_CONFIG_RESET:
		ni_tio_reset_count_and_disarm(counter);
		return 0;
		break;
	default:
		break;
	}
	return -EINVAL;
}