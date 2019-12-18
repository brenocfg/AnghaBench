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
typedef  int u32 ;
struct comedi_subdevice {struct comedi_async* async; } ;
struct comedi_device {int dummy; } ;
struct comedi_async {int /*<<< orphan*/  events; } ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_4__ {scalar_t__ reg_type; } ;
struct TYPE_3__ {short* ai_fifo_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADC_FIFO_Data_611x ; 
 int /*<<< orphan*/  ADC_FIFO_Data_Register ; 
 int /*<<< orphan*/  AIFIFO_Control_6143 ; 
 int /*<<< orphan*/  AIFIFO_Data_6143 ; 
 int /*<<< orphan*/  COMEDI_CB_ERROR ; 
 TYPE_2__ boardtype ; 
 int /*<<< orphan*/  cfc_write_array_to_buffer (struct comedi_subdevice*,short*,int) ; 
 int /*<<< orphan*/  cfc_write_to_buffer (struct comedi_subdevice*,short) ; 
 int /*<<< orphan*/  comedi_error (struct comedi_device*,char*) ; 
 TYPE_1__* devpriv ; 
 int ni_readl (int /*<<< orphan*/ ) ; 
 short ni_readw (int /*<<< orphan*/ ) ; 
 scalar_t__ ni_reg_611x ; 
 scalar_t__ ni_reg_6143 ; 
 int /*<<< orphan*/  ni_writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ni_ai_fifo_read(struct comedi_device *dev,
			    struct comedi_subdevice *s, int n)
{
	struct comedi_async *async = s->async;
	int i;

	if (boardtype.reg_type == ni_reg_611x) {
		short data[2];
		u32 dl;

		for (i = 0; i < n / 2; i++) {
			dl = ni_readl(ADC_FIFO_Data_611x);
			/* This may get the hi/lo data in the wrong order */
			data[0] = (dl >> 16) & 0xffff;
			data[1] = dl & 0xffff;
			cfc_write_array_to_buffer(s, data, sizeof(data));
		}
		/* Check if there's a single sample stuck in the FIFO */
		if (n % 2) {
			dl = ni_readl(ADC_FIFO_Data_611x);
			data[0] = dl & 0xffff;
			cfc_write_to_buffer(s, data[0]);
		}
	} else if (boardtype.reg_type == ni_reg_6143) {
		short data[2];
		u32 dl;

		/*  This just reads the FIFO assuming the data is present, no checks on the FIFO status are performed */
		for (i = 0; i < n / 2; i++) {
			dl = ni_readl(AIFIFO_Data_6143);

			data[0] = (dl >> 16) & 0xffff;
			data[1] = dl & 0xffff;
			cfc_write_array_to_buffer(s, data, sizeof(data));
		}
		if (n % 2) {
			/* Assume there is a single sample stuck in the FIFO */
			ni_writel(0x01, AIFIFO_Control_6143);	/*  Get stranded sample into FIFO */
			dl = ni_readl(AIFIFO_Data_6143);
			data[0] = (dl >> 16) & 0xffff;
			cfc_write_to_buffer(s, data[0]);
		}
	} else {
		if (n > sizeof(devpriv->ai_fifo_buffer) /
		    sizeof(devpriv->ai_fifo_buffer[0])) {
			comedi_error(dev, "bug! ai_fifo_buffer too small");
			async->events |= COMEDI_CB_ERROR;
			return;
		}
		for (i = 0; i < n; i++) {
			devpriv->ai_fifo_buffer[i] =
			    ni_readw(ADC_FIFO_Data_Register);
		}
		cfc_write_array_to_buffer(s, devpriv->ai_fifo_buffer,
					  n *
					  sizeof(devpriv->ai_fifo_buffer[0]));
	}
}