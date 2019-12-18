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
typedef  int u16 ;
struct i2c_msg {int len; int* buf; int addr; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  num; } ;
struct av7110 {int adac_type; TYPE_1__ dvb_adapter; int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
#define  DVB_ADAC_MSP34x0 129 
#define  DVB_ADAC_MSP34x5 128 
 int EIO ; 
 int /*<<< orphan*/  dprintk (int,char*,int /*<<< orphan*/ ,int,int) ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 

int msp_writereg(struct av7110 *av7110, u8 dev, u16 reg, u16 val)
{
	u8 msg[5] = { dev, reg >> 8, reg & 0xff, val >> 8 , val & 0xff };
	struct i2c_msg msgs = { .flags = 0, .len = 5, .buf = msg };

	switch (av7110->adac_type) {
	case DVB_ADAC_MSP34x0:
		msgs.addr = 0x40;
		break;
	case DVB_ADAC_MSP34x5:
		msgs.addr = 0x42;
		break;
	default:
		return 0;
	}

	if (i2c_transfer(&av7110->i2c_adap, &msgs, 1) != 1) {
		dprintk(1, "dvb-ttpci: failed @ card %d, %u = %u\n",
		       av7110->dvb_adapter.num, reg, val);
		return -EIO;
	}
	return 0;
}