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
typedef  int u8 ;
struct saa7134_dev {int /*<<< orphan*/  i2c_adap; } ;
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;
struct dvb_frontend {TYPE_1__* dvb; } ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_2__ {struct saa7134_dev* priv; } ;

/* Variables and functions */
 int EIO ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ philips_td1316_tuner_init (struct dvb_frontend*) ; 

__attribute__((used)) static int philips_europa_tuner_init(struct dvb_frontend *fe)
{
	struct saa7134_dev *dev = fe->dvb->priv;
	static u8 msg[] = { 0x00, 0x40};
	struct i2c_msg init_msg = {.addr = 0x43,.flags = 0,.buf = msg,.len = sizeof(msg) };


	if (philips_td1316_tuner_init(fe))
		return -EIO;
	msleep(1);
	if (i2c_transfer(&dev->i2c_adap, &init_msg, 1) != 1)
		return -EIO;

	return 0;
}