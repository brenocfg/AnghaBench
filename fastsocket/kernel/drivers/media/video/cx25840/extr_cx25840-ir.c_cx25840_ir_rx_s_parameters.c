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
typedef  union cx25840_ir_fifo_rec {int dummy; } cx25840_ir_fifo_rec ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct v4l2_subdev_ir_parameters {scalar_t__ mode; int bytes_per_data_element; int duty_cycle; int enable; scalar_t__ interrupt_enable; int /*<<< orphan*/  invert_level; int /*<<< orphan*/  resolution; int /*<<< orphan*/  noise_filter_min_width; scalar_t__ max_pulse_width; int /*<<< orphan*/  carrier_range_upper; int /*<<< orphan*/  carrier_range_lower; int /*<<< orphan*/  carrier_freq; int /*<<< orphan*/  modulation; scalar_t__ shutdown; } ;
struct v4l2_subdev {int dummy; } ;
struct i2c_client {int dummy; } ;
struct cx25840_ir_state {int /*<<< orphan*/  rx_params_lock; int /*<<< orphan*/  rx_kfifo; int /*<<< orphan*/  rx_invert; int /*<<< orphan*/  rxclk_divider; struct v4l2_subdev_ir_parameters rx_params; struct i2c_client* c; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNTRL_EDG_BOTH ; 
 int ENODEV ; 
 int ENOSYS ; 
 int /*<<< orphan*/  FIFO_RXTX ; 
 int IRQEN_ROE ; 
 int IRQEN_RSE ; 
 int IRQEN_RTE ; 
 int /*<<< orphan*/  RX_FIFO_HALF_FULL ; 
 scalar_t__ V4L2_SUBDEV_IR_MODE_PULSE_WIDTH ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clock_divider_to_resolution (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  control_rx_demodulation_enable (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  control_rx_enable (struct i2c_client*,int) ; 
 int /*<<< orphan*/  control_rx_irq_watermark (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  control_rx_s_carrier_window (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  control_rx_s_edge_detection (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int cx25840_ir_rx_shutdown (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  filter_rx_s_min_width (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqenable_rx (struct v4l2_subdev*,int) ; 
 int /*<<< orphan*/  kfifo_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ pulse_width_count_to_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxclk_rx_s_carrier (struct i2c_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ rxclk_rx_s_max_pulse_width (struct i2c_client*,scalar_t__,int /*<<< orphan*/ *) ; 
 struct cx25840_ir_state* to_ir_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int cx25840_ir_rx_s_parameters(struct v4l2_subdev *sd,
				      struct v4l2_subdev_ir_parameters *p)
{
	struct cx25840_ir_state *ir_state = to_ir_state(sd);
	struct i2c_client *c;
	struct v4l2_subdev_ir_parameters *o;
	u16 rxclk_divider;

	if (ir_state == NULL)
		return -ENODEV;

	if (p->shutdown)
		return cx25840_ir_rx_shutdown(sd);

	if (p->mode != V4L2_SUBDEV_IR_MODE_PULSE_WIDTH)
		return -ENOSYS;

	c = ir_state->c;
	o = &ir_state->rx_params;

	mutex_lock(&ir_state->rx_params_lock);

	o->shutdown = p->shutdown;

	p->mode = V4L2_SUBDEV_IR_MODE_PULSE_WIDTH;
	o->mode = p->mode;

	p->bytes_per_data_element = sizeof(union cx25840_ir_fifo_rec);
	o->bytes_per_data_element = p->bytes_per_data_element;

	/* Before we tweak the hardware, we have to disable the receiver */
	irqenable_rx(sd, 0);
	control_rx_enable(c, false);

	control_rx_demodulation_enable(c, p->modulation);
	o->modulation = p->modulation;

	if (p->modulation) {
		p->carrier_freq = rxclk_rx_s_carrier(c, p->carrier_freq,
						     &rxclk_divider);

		o->carrier_freq = p->carrier_freq;

		p->duty_cycle = 50;
		o->duty_cycle = p->duty_cycle;

		control_rx_s_carrier_window(c, p->carrier_freq,
					    &p->carrier_range_lower,
					    &p->carrier_range_upper);
		o->carrier_range_lower = p->carrier_range_lower;
		o->carrier_range_upper = p->carrier_range_upper;

		p->max_pulse_width =
			(u32) pulse_width_count_to_ns(FIFO_RXTX, rxclk_divider);
	} else {
		p->max_pulse_width =
			    rxclk_rx_s_max_pulse_width(c, p->max_pulse_width,
						       &rxclk_divider);
	}
	o->max_pulse_width = p->max_pulse_width;
	atomic_set(&ir_state->rxclk_divider, rxclk_divider);

	p->noise_filter_min_width =
			    filter_rx_s_min_width(c, p->noise_filter_min_width);
	o->noise_filter_min_width = p->noise_filter_min_width;

	p->resolution = clock_divider_to_resolution(rxclk_divider);
	o->resolution = p->resolution;

	/* FIXME - make this dependent on resolution for better performance */
	control_rx_irq_watermark(c, RX_FIFO_HALF_FULL);

	control_rx_s_edge_detection(c, CNTRL_EDG_BOTH);

	o->invert_level = p->invert_level;
	atomic_set(&ir_state->rx_invert, p->invert_level);

	o->interrupt_enable = p->interrupt_enable;
	o->enable = p->enable;
	if (p->enable) {
		kfifo_reset(ir_state->rx_kfifo);
		if (p->interrupt_enable)
			irqenable_rx(sd, IRQEN_RSE | IRQEN_RTE | IRQEN_ROE);
		control_rx_enable(c, p->enable);
	}

	mutex_unlock(&ir_state->rx_params_lock);
	return 0;
}