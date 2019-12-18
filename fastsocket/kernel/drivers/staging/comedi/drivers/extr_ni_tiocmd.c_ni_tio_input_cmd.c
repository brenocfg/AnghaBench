#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ni_gpct_device {int variant; } ;
struct ni_gpct {TYPE_1__* mite_chan; int /*<<< orphan*/  counter_index; struct ni_gpct_device* counter_dev; } ;
struct comedi_cmd {int start_src; int /*<<< orphan*/  start_arg; } ;
struct comedi_async {int /*<<< orphan*/ * inttrig; int /*<<< orphan*/  prealloc_bufsz; struct comedi_cmd cmd; } ;
struct TYPE_3__ {int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  COMEDI_INPUT ; 
 int /*<<< orphan*/  Gi_Save_Trace_Bit ; 
 int /*<<< orphan*/  NITIO_Gi_Command_Reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NI_GPCT_ARM_IMMEDIATE ; 
#define  TRIG_EXT 134 
#define  TRIG_INT 133 
#define  TRIG_NOW 132 
#define  TRIG_OTHER 131 
 int /*<<< orphan*/  comedi_buf_write_alloc (struct comedi_async*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mite_dma_arm (TYPE_1__*) ; 
 int /*<<< orphan*/  mite_prep_dma (TYPE_1__*,int,int) ; 
#define  ni_gpct_variant_660x 130 
#define  ni_gpct_variant_e_series 129 
#define  ni_gpct_variant_m_series 128 
 int ni_tio_arm (struct ni_gpct*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_tio_configure_dma (struct ni_gpct*,int,int) ; 
 int /*<<< orphan*/  ni_tio_input_inttrig ; 
 int /*<<< orphan*/  ni_tio_set_bits (struct ni_gpct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_tio_input_cmd(struct ni_gpct *counter, struct comedi_async *async)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;
	struct comedi_cmd *cmd = &async->cmd;
	int retval = 0;

	/* write alloc the entire buffer */
	comedi_buf_write_alloc(async, async->prealloc_bufsz);
	counter->mite_chan->dir = COMEDI_INPUT;
	switch (counter_dev->variant) {
	case ni_gpct_variant_m_series:
	case ni_gpct_variant_660x:
		mite_prep_dma(counter->mite_chan, 32, 32);
		break;
	case ni_gpct_variant_e_series:
		mite_prep_dma(counter->mite_chan, 16, 32);
		break;
	default:
		BUG();
		break;
	}
	ni_tio_set_bits(counter, NITIO_Gi_Command_Reg(counter->counter_index),
			Gi_Save_Trace_Bit, 0);
	ni_tio_configure_dma(counter, 1, 1);
	switch (cmd->start_src) {
	case TRIG_NOW:
		async->inttrig = NULL;
		mite_dma_arm(counter->mite_chan);
		retval = ni_tio_arm(counter, 1, NI_GPCT_ARM_IMMEDIATE);
		break;
	case TRIG_INT:
		async->inttrig = &ni_tio_input_inttrig;
		break;
	case TRIG_EXT:
		async->inttrig = NULL;
		mite_dma_arm(counter->mite_chan);
		retval = ni_tio_arm(counter, 1, cmd->start_arg);
	case TRIG_OTHER:
		async->inttrig = NULL;
		mite_dma_arm(counter->mite_chan);
		break;
	default:
		BUG();
		break;
	}
	return retval;
}