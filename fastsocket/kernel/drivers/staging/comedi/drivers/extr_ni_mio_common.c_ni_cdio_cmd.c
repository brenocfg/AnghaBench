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
struct comedi_subdevice {int io_bits; unsigned int state; TYPE_1__* async; } ;
struct comedi_device {int dummy; } ;
struct comedi_cmd {int scan_begin_src; int scan_begin_arg; } ;
struct TYPE_2__ {int /*<<< orphan*/ * inttrig; struct comedi_cmd cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 unsigned int CDO_FIFO_Mode_Bit ; 
 unsigned int CDO_Halt_On_Error_Bit ; 
 unsigned int CDO_Polarity_Bit ; 
 unsigned int CDO_Reset_Bit ; 
 unsigned int CDO_SW_Update_Bit ; 
 unsigned int CDO_Sample_Source_Select_Mask ; 
 unsigned int CR_CHAN (int) ; 
 int CR_INVERT ; 
 int EIO ; 
 int /*<<< orphan*/  M_Offset_CDIO_Command ; 
 int /*<<< orphan*/  M_Offset_CDO_FIFO_Data ; 
 int /*<<< orphan*/  M_Offset_CDO_Mask_Enable ; 
 int /*<<< orphan*/  M_Offset_CDO_Mode ; 
#define  TRIG_EXT 128 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 int /*<<< orphan*/  ni_cdo_inttrig ; 
 int ni_request_cdo_mite_channel (struct comedi_device*) ; 
 int /*<<< orphan*/  ni_writel (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ni_cdio_cmd(struct comedi_device *dev, struct comedi_subdevice *s)
{
	const struct comedi_cmd *cmd = &s->async->cmd;
	unsigned cdo_mode_bits = CDO_FIFO_Mode_Bit | CDO_Halt_On_Error_Bit;
	int retval;

	ni_writel(CDO_Reset_Bit, M_Offset_CDIO_Command);
	switch (cmd->scan_begin_src) {
	case TRIG_EXT:
		cdo_mode_bits |=
		    CR_CHAN(cmd->scan_begin_arg) &
		    CDO_Sample_Source_Select_Mask;
		break;
	default:
		BUG();
		break;
	}
	if (cmd->scan_begin_arg & CR_INVERT)
		cdo_mode_bits |= CDO_Polarity_Bit;
	ni_writel(cdo_mode_bits, M_Offset_CDO_Mode);
	if (s->io_bits) {
		ni_writel(s->state, M_Offset_CDO_FIFO_Data);
		ni_writel(CDO_SW_Update_Bit, M_Offset_CDIO_Command);
		ni_writel(s->io_bits, M_Offset_CDO_Mask_Enable);
	} else {
		comedi_error(dev,
			     "attempted to run digital output command with no lines configured as outputs");
		return -EIO;
	}
	retval = ni_request_cdo_mite_channel(dev);
	if (retval < 0) {
		return retval;
	}
	s->async->inttrig = &ni_cdo_inttrig;
	return 0;
}