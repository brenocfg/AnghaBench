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
typedef  int u8 ;
typedef  int u32 ;
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;
struct dvb_frontend_parameters {int frequency; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* i2c_gate_ctrl ) (struct dvb_frontend*,int) ;} ;
struct dvb_frontend {TYPE_2__ ops; TYPE_1__* dvb; } ;
struct dvb_bt8xx_card {int /*<<< orphan*/  i2c_adapter; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_3__ {scalar_t__ priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,int) ; 

__attribute__((used)) static int vp3021_alps_tded4_tuner_set_params(struct dvb_frontend* fe, struct dvb_frontend_parameters* params)
{
	struct dvb_bt8xx_card *card = (struct dvb_bt8xx_card *) fe->dvb->priv;
	u8 buf[4];
	u32 div;
	struct i2c_msg msg = { .addr = 0x60, .flags = 0, .buf = buf, .len = sizeof(buf) };

	div = (params->frequency + 36166667) / 166667;

	buf[0] = (div >> 8) & 0x7F;
	buf[1] = div & 0xFF;
	buf[2] = 0x85;
	if ((params->frequency >= 47000000) && (params->frequency < 153000000))
		buf[3] = 0x01;
	else if ((params->frequency >= 153000000) && (params->frequency < 430000000))
		buf[3] = 0x02;
	else if ((params->frequency >= 430000000) && (params->frequency < 824000000))
		buf[3] = 0x0C;
	else if ((params->frequency >= 824000000) && (params->frequency < 863000000))
		buf[3] = 0x8C;
	else
		return -EINVAL;

	if (fe->ops.i2c_gate_ctrl)
		fe->ops.i2c_gate_ctrl(fe, 1);
	i2c_transfer(card->i2c_adapter, &msg, 1);
	return 0;
}