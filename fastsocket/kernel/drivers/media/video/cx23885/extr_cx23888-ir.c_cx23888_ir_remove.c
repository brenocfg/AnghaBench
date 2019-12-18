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
struct v4l2_subdev {int dummy; } ;
struct cx23888_ir_state {int /*<<< orphan*/  rx_kfifo; } ;
struct cx23885_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX23885_HW_888_IR ; 
 int ENODEV ; 
 struct v4l2_subdev* cx23885_find_hw (struct cx23885_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx23888_ir_rx_shutdown (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  cx23888_ir_tx_shutdown (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cx23888_ir_state*) ; 
 struct cx23888_ir_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (struct v4l2_subdev*) ; 

int cx23888_ir_remove(struct cx23885_dev *dev)
{
	struct v4l2_subdev *sd;
	struct cx23888_ir_state *state;

	sd = cx23885_find_hw(dev, CX23885_HW_888_IR);
	if (sd == NULL)
		return -ENODEV;

	cx23888_ir_rx_shutdown(sd);
	cx23888_ir_tx_shutdown(sd);

	state = to_state(sd);
	v4l2_device_unregister_subdev(sd);
	kfifo_free(state->rx_kfifo);
	kfree(state);
	/* Nothing more to free() as state held the actual v4l2_subdev object */
	return 0;
}