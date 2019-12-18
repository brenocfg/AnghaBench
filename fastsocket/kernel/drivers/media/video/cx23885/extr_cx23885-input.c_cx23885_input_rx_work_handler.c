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
typedef  int u32 ;
struct v4l2_subdev_ir_parameters {int enable; void* shutdown; } ;
struct cx23885_dev {int board; int /*<<< orphan*/ * sd_ir; int /*<<< orphan*/  ir_input_stopping; } ;

/* Variables and functions */
#define  CX23885_BOARD_HAUPPAUGE_HVR1250 131 
#define  CX23885_BOARD_HAUPPAUGE_HVR1290 130 
#define  CX23885_BOARD_HAUPPAUGE_HVR1850 129 
#define  CX23885_BOARD_TEVII_S470 128 
 int V4L2_SUBDEV_IR_RX_END_OF_RX_DETECTED ; 
 int V4L2_SUBDEV_IR_RX_FIFO_SERVICE_REQ ; 
 int V4L2_SUBDEV_IR_RX_HW_FIFO_OVERRUN ; 
 int V4L2_SUBDEV_IR_RX_SW_FIFO_OVERRUN ; 
 void* atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cx23885_input_process_measurements (struct cx23885_dev*,int) ; 
 int /*<<< orphan*/  ir ; 
 int /*<<< orphan*/  rx_g_parameters ; 
 int /*<<< orphan*/  rx_s_parameters ; 
 int /*<<< orphan*/  v4l2_subdev_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_subdev_ir_parameters*) ; 

void cx23885_input_rx_work_handler(struct cx23885_dev *dev, u32 events)
{
	struct v4l2_subdev_ir_parameters params;
	int overrun, data_available;

	if (dev->sd_ir == NULL || events == 0)
		return;

	switch (dev->board) {
	case CX23885_BOARD_HAUPPAUGE_HVR1850:
	case CX23885_BOARD_HAUPPAUGE_HVR1290:
	case CX23885_BOARD_TEVII_S470:
	case CX23885_BOARD_HAUPPAUGE_HVR1250:
		/*
		 * The only boards we handle right now.  However other boards
		 * using the CX2388x integrated IR controller should be similar
		 */
		break;
	default:
		return;
	}

	overrun = events & (V4L2_SUBDEV_IR_RX_SW_FIFO_OVERRUN |
			    V4L2_SUBDEV_IR_RX_HW_FIFO_OVERRUN);

	data_available = events & (V4L2_SUBDEV_IR_RX_END_OF_RX_DETECTED |
				   V4L2_SUBDEV_IR_RX_FIFO_SERVICE_REQ);

	if (overrun) {
		/* If there was a FIFO overrun, stop the device */
		v4l2_subdev_call(dev->sd_ir, ir, rx_g_parameters, &params);
		params.enable = false;
		/* Mitigate race with cx23885_input_ir_stop() */
		params.shutdown = atomic_read(&dev->ir_input_stopping);
		v4l2_subdev_call(dev->sd_ir, ir, rx_s_parameters, &params);
	}

	if (data_available)
		cx23885_input_process_measurements(dev, overrun);

	if (overrun) {
		/* If there was a FIFO overrun, clear & restart the device */
		params.enable = true;
		/* Mitigate race with cx23885_input_ir_stop() */
		params.shutdown = atomic_read(&dev->ir_input_stopping);
		v4l2_subdev_call(dev->sd_ir, ir, rx_s_parameters, &params);
	}
}