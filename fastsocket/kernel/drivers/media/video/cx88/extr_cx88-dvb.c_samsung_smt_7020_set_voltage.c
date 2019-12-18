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
struct i2c_msg {int addr; int* buf; int len; int /*<<< orphan*/  flags; } ;
struct dvb_frontend {TYPE_1__* dvb; } ;
struct cx88_core {int /*<<< orphan*/  i2c_adap; } ;
struct cx8802_dev {struct cx88_core* core; } ;
typedef  int fe_sec_voltage_t ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_2__ {struct cx8802_dev* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ISL6421_EN1 ; 
 int ISL6421_LLC1 ; 
 int ISL6421_VSEL1 ; 
 int /*<<< orphan*/  MO_GP0_IO ; 
#define  SEC_VOLTAGE_13 130 
#define  SEC_VOLTAGE_18 129 
#define  SEC_VOLTAGE_OFF 128 
 int /*<<< orphan*/  cx_clear (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx_set (int /*<<< orphan*/ ,int) ; 
 int i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 

__attribute__((used)) static int samsung_smt_7020_set_voltage(struct dvb_frontend *fe,
	fe_sec_voltage_t voltage)
{
	struct cx8802_dev *dev = fe->dvb->priv;
	struct cx88_core *core = dev->core;

	u8 data;
	struct i2c_msg msg = {
		.addr = 8,
		.flags = 0,
		.buf = &data,
		.len = sizeof(data) };

	cx_set(MO_GP0_IO, 0x8000);

	switch (voltage) {
	case SEC_VOLTAGE_OFF:
		break;
	case SEC_VOLTAGE_13:
		data = ISL6421_EN1 | ISL6421_LLC1;
		cx_clear(MO_GP0_IO, 0x80);
		break;
	case SEC_VOLTAGE_18:
		data = ISL6421_EN1 | ISL6421_LLC1 | ISL6421_VSEL1;
		cx_clear(MO_GP0_IO, 0x80);
		break;
	default:
		return -EINVAL;
	};

	return (i2c_transfer(&dev->core->i2c_adap, &msg, 1) == 1) ? 0 : -EIO;
}