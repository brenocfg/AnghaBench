#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct comedi_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ reg_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* stc_writew ) (struct comedi_device*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_FIFO_Clear ; 
 int /*<<< orphan*/  AIFIFO_Control_6143 ; 
 int /*<<< orphan*/  AIFIFO_Status_6143 ; 
 int AI_CONVERT_Pulse ; 
 int /*<<< orphan*/  AI_Command_1_Register ; 
 int /*<<< orphan*/  M_Offset_Static_AI_Control (int /*<<< orphan*/ ) ; 
 TYPE_2__ boardtype ; 
 TYPE_1__* devpriv ; 
 int ni_readl (int /*<<< orphan*/ ) ; 
 scalar_t__ ni_reg_6143 ; 
 scalar_t__ ni_reg_625x ; 
 int /*<<< orphan*/  ni_writeb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct comedi_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ni_clear_ai_fifo(struct comedi_device *dev)
{
	if (boardtype.reg_type == ni_reg_6143) {
		/*  Flush the 6143 data FIFO */
		ni_writel(0x10, AIFIFO_Control_6143);	/*  Flush fifo */
		ni_writel(0x00, AIFIFO_Control_6143);	/*  Flush fifo */
		while (ni_readl(AIFIFO_Status_6143) & 0x10) ;	/*  Wait for complete */
	} else {
		devpriv->stc_writew(dev, 1, ADC_FIFO_Clear);
		if (boardtype.reg_type == ni_reg_625x) {
			ni_writeb(0, M_Offset_Static_AI_Control(0));
			ni_writeb(1, M_Offset_Static_AI_Control(0));
#if 0
			/* the NI example code does 3 convert pulses for 625x boards,
			   but that appears to be wrong in practice. */
			devpriv->stc_writew(dev, AI_CONVERT_Pulse,
					    AI_Command_1_Register);
			devpriv->stc_writew(dev, AI_CONVERT_Pulse,
					    AI_Command_1_Register);
			devpriv->stc_writew(dev, AI_CONVERT_Pulse,
					    AI_Command_1_Register);
#endif
		}
	}
}