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
struct i2c_msg {int* buf; int len; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct dvb_usb_adapter {TYPE_1__* dev; } ;
struct dvb_frontend {TYPE_2__* dvb; } ;
typedef  scalar_t__ fe_sec_voltage_t ;
struct TYPE_4__ {scalar_t__ priv; } ;
struct TYPE_3__ {int /*<<< orphan*/  i2c_adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW2102_VOLTAGE_CTRL ; 
 scalar_t__ SEC_VOLTAGE_13 ; 
 scalar_t__ SEC_VOLTAGE_18 ; 
 int /*<<< orphan*/  i2c_transfer (int /*<<< orphan*/ *,struct i2c_msg*,int) ; 

__attribute__((used)) static int dw210x_set_voltage(struct dvb_frontend *fe, fe_sec_voltage_t voltage)
{
	static u8 command_13v[] = {0x00, 0x01};
	static u8 command_18v[] = {0x01, 0x01};
	static u8 command_off[] = {0x00, 0x00};
	struct i2c_msg msg = {
		.addr = DW2102_VOLTAGE_CTRL,
		.flags = 0,
		.buf = command_off,
		.len = 2,
	};

	struct dvb_usb_adapter *udev_adap =
		(struct dvb_usb_adapter *)(fe->dvb->priv);
	if (voltage == SEC_VOLTAGE_18)
		msg.buf = command_18v;
	else if (voltage == SEC_VOLTAGE_13)
		msg.buf = command_13v;

	i2c_transfer(&udev_adap->dev->i2c_adap, &msg, 1);

	return 0;
}