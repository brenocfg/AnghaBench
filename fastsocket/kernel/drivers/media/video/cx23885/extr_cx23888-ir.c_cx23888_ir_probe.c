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
struct v4l2_subdev_ir_parameters {int dummy; } ;
struct v4l2_subdev {int /*<<< orphan*/  grp_id; int /*<<< orphan*/  name; } ;
struct cx23888_ir_state {int /*<<< orphan*/  rx_kfifo; int /*<<< orphan*/  tx_params_lock; int /*<<< orphan*/  rx_params_lock; struct v4l2_subdev sd; scalar_t__ rev; int /*<<< orphan*/  id; struct cx23885_dev* dev; int /*<<< orphan*/  rx_kfifo_lock; } ;
struct cx23885_dev {char* name; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX23885_HW_888_IR ; 
 int /*<<< orphan*/  CX23888_IR_IRQEN_REG ; 
 int /*<<< orphan*/  CX23888_IR_RX_KFIFO_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V4L2_IDENT_CX23888_IR ; 
 int /*<<< orphan*/  cx23888_ir_controller_ops ; 
 int /*<<< orphan*/  cx23888_ir_write4 (struct cx23885_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_rx_params ; 
 int /*<<< orphan*/  default_tx_params ; 
 int /*<<< orphan*/  ir ; 
 int /*<<< orphan*/  kfifo_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ ) ; 
 struct cx23888_ir_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct v4l2_subdev_ir_parameters*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rx_s_parameters ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_s_parameters ; 
 int v4l2_device_register_subdev (int /*<<< orphan*/ *,struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_set_subdevdata (struct v4l2_subdev*,struct cx23888_ir_state*) ; 
 int /*<<< orphan*/  v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_subdev_ir_parameters*) ; 
 int /*<<< orphan*/  v4l2_subdev_init (struct v4l2_subdev*,int /*<<< orphan*/ *) ; 

int cx23888_ir_probe(struct cx23885_dev *dev)
{
	struct cx23888_ir_state *state;
	struct v4l2_subdev *sd;
	struct v4l2_subdev_ir_parameters default_params;
	int ret;

	state = kzalloc(sizeof(struct cx23888_ir_state), GFP_KERNEL);
	if (state == NULL)
		return -ENOMEM;

	spin_lock_init(&state->rx_kfifo_lock);
	state->rx_kfifo = kfifo_alloc(CX23888_IR_RX_KFIFO_SIZE, GFP_KERNEL,
				      &state->rx_kfifo_lock);
	if (IS_ERR(state->rx_kfifo))
		return IS_ERR(state->rx_kfifo);

	state->dev = dev;
	state->id = V4L2_IDENT_CX23888_IR;
	state->rev = 0;
	sd = &state->sd;

	v4l2_subdev_init(sd, &cx23888_ir_controller_ops);
	v4l2_set_subdevdata(sd, state);
	/* FIXME - fix the formatting of dev->v4l2_dev.name and use it */
	snprintf(sd->name, sizeof(sd->name), "%s/888-ir", dev->name);
	sd->grp_id = CX23885_HW_888_IR;

	ret = v4l2_device_register_subdev(&dev->v4l2_dev, sd);
	if (ret == 0) {
		/*
		 * Ensure no interrupts arrive from '888 specific conditions,
		 * since we ignore them in this driver to have commonality with
		 * similar IR controller cores.
		 */
		cx23888_ir_write4(dev, CX23888_IR_IRQEN_REG, 0);

		mutex_init(&state->rx_params_lock);
		memcpy(&default_params, &default_rx_params,
		       sizeof(struct v4l2_subdev_ir_parameters));
		v4l2_subdev_call(sd, ir, rx_s_parameters, &default_params);

		mutex_init(&state->tx_params_lock);
		memcpy(&default_params, &default_tx_params,
		       sizeof(struct v4l2_subdev_ir_parameters));
		v4l2_subdev_call(sd, ir, tx_s_parameters, &default_params);
	} else {
		kfifo_free(state->rx_kfifo);
	}
	return ret;
}