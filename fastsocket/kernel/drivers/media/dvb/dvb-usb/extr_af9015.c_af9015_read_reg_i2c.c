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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct req_t {scalar_t__ member_1; int member_4; int member_5; scalar_t__* member_6; int addr_len; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_0; } ;
struct dvb_usb_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ demod_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  READ_I2C ; 
 TYPE_1__* af9015_af9013_config ; 
 int af9015_ctrl_msg (struct dvb_usb_device*,struct req_t*) ; 

__attribute__((used)) static int af9015_read_reg_i2c(struct dvb_usb_device *d, u8 addr, u16 reg,
	u8 *val)
{
	struct req_t req = {READ_I2C, addr, reg, 0, 1, 1, val};

	if (addr == af9015_af9013_config[0].demod_address ||
	    addr == af9015_af9013_config[1].demod_address)
		req.addr_len = 3;

	return af9015_ctrl_msg(d, &req);
}