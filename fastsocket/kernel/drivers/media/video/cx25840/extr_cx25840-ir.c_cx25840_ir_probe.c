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
struct v4l2_subdev {int dummy; } ;
struct cx25840_state {struct cx25840_ir_state* ir_state; int /*<<< orphan*/  c; } ;
struct cx25840_ir_state {int /*<<< orphan*/  tx_params_lock; int /*<<< orphan*/  rx_params_lock; int /*<<< orphan*/  c; int /*<<< orphan*/  rx_kfifo; int /*<<< orphan*/  rx_kfifo_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX25840_IR_IRQEN_REG ; 
 int /*<<< orphan*/  CX25840_IR_RX_KFIFO_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQEN_MSK ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx25840_write4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  default_rx_params ; 
 int /*<<< orphan*/  default_tx_params ; 
 int /*<<< orphan*/  ir ; 
 scalar_t__ is_cx23885 (struct cx25840_state*) ; 
 scalar_t__ is_cx23887 (struct cx25840_state*) ; 
 int /*<<< orphan*/  kfifo_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct cx25840_ir_state*) ; 
 struct cx25840_ir_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct v4l2_subdev_ir_parameters*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rx_s_parameters ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 struct cx25840_state* to_state (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  tx_s_parameters ; 
 int /*<<< orphan*/  v4l2_subdev_call (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_subdev_ir_parameters*) ; 

int cx25840_ir_probe(struct v4l2_subdev *sd)
{
	struct cx25840_state *state = to_state(sd);
	struct cx25840_ir_state *ir_state;
	struct v4l2_subdev_ir_parameters default_params;

	/* Only init the IR controller for the CX2388[57] AV Core for now */
	if (!(is_cx23885(state) || is_cx23887(state)))
		return 0;

	ir_state = kzalloc(sizeof(struct cx25840_ir_state), GFP_KERNEL);
	if (ir_state == NULL)
		return -ENOMEM;

	spin_lock_init(&ir_state->rx_kfifo_lock);
	ir_state->rx_kfifo = kfifo_alloc(CX25840_IR_RX_KFIFO_SIZE, GFP_KERNEL,
				      &ir_state->rx_kfifo_lock);
	if (IS_ERR(ir_state->rx_kfifo)) {
		kfree(ir_state);
		return -ENOMEM;
	}

	ir_state->c = state->c;
	state->ir_state = ir_state;

	/* Ensure no interrupts arrive yet */
	if (is_cx23885(state) || is_cx23887(state))
		cx25840_write4(ir_state->c, CX25840_IR_IRQEN_REG, IRQEN_MSK);
	else
		cx25840_write4(ir_state->c, CX25840_IR_IRQEN_REG, 0);

	mutex_init(&ir_state->rx_params_lock);
	memcpy(&default_params, &default_rx_params,
		       sizeof(struct v4l2_subdev_ir_parameters));
	v4l2_subdev_call(sd, ir, rx_s_parameters, &default_params);

	mutex_init(&ir_state->tx_params_lock);
	memcpy(&default_params, &default_tx_params,
		       sizeof(struct v4l2_subdev_ir_parameters));
	v4l2_subdev_call(sd, ir, tx_s_parameters, &default_params);

	return 0;
}