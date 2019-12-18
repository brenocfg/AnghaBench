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
typedef  int u32 ;
struct comedi_subdevice {int dummy; } ;
struct comedi_device {struct comedi_subdevice* subdevices; } ;
struct TYPE_2__ {scalar_t__ reg_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIFIFO_Control_6143 ; 
 int /*<<< orphan*/  AIFIFO_Data_6143 ; 
 int /*<<< orphan*/  AIFIFO_Status_6143 ; 
 int NI_AI_SUBDEV ; 
 TYPE_1__ boardtype ; 
 int /*<<< orphan*/  cfc_write_to_buffer (struct comedi_subdevice*,short) ; 
 int ni_readl (int /*<<< orphan*/ ) ; 
 scalar_t__ ni_reg_6143 ; 
 int /*<<< orphan*/  ni_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_last_sample_6143(struct comedi_device *dev)
{
	struct comedi_subdevice *s = dev->subdevices + NI_AI_SUBDEV;
	short data;
	u32 dl;

	if (boardtype.reg_type != ni_reg_6143)
		return;

	/* Check if there's a single sample stuck in the FIFO */
	if (ni_readl(AIFIFO_Status_6143) & 0x01) {
		ni_writel(0x01, AIFIFO_Control_6143);	/*  Get stranded sample into FIFO */
		dl = ni_readl(AIFIFO_Data_6143);

		/* This may get the hi/lo data in the wrong order */
		data = (dl >> 16) & 0xffff;
		cfc_write_to_buffer(s, data);
	}
}