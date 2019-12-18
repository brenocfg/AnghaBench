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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct req_t {int /*<<< orphan*/ * member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF9015_I2C_DEMOD ; 
 int /*<<< orphan*/  WRITE_MEMORY ; 
 int af9015_ctrl_msg (struct dvb_usb_device*,struct req_t*) ; 

__attribute__((used)) static int af9015_write_regs(struct dvb_usb_device *d, u16 addr, u8 *val,
	u8 len)
{
	struct req_t req = {WRITE_MEMORY, AF9015_I2C_DEMOD, addr, 0, 0, len,
		val};
	return af9015_ctrl_msg(d, &req);
}