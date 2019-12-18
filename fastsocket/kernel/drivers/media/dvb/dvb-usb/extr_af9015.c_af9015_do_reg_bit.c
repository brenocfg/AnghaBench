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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int af9015_read_reg (struct dvb_usb_device*,int /*<<< orphan*/ ,int*) ; 
 int af9015_write_reg (struct dvb_usb_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int af9015_do_reg_bit(struct dvb_usb_device *d, u16 addr, u8 bit, u8 op)
{
	int ret;
	u8 val, mask = 0x01;

	ret = af9015_read_reg(d, addr, &val);
	if (ret)
		return ret;

	mask <<= bit;
	if (op) {
		/* set bit */
		val |= mask;
	} else {
		/* clear bit */
		mask ^= 0xff;
		val &= mask;
	}

	return af9015_write_reg(d, addr, val);
}