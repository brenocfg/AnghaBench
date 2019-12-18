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
struct rs5c372 {int type; int* regs; int time24; int /*<<< orphan*/  client; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int R2025_CTRL2_XST ; 
 unsigned char RS5C372_CTRL2_24 ; 
 int RS5C_ADDR (size_t) ; 
 int RS5C_CTRL2_XSTP ; 
 size_t RS5C_REG_CTRL1 ; 
 size_t RS5C_REG_CTRL2 ; 
 unsigned char RV5C387_CTRL1_24 ; 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int,unsigned char) ; 
#define  rtc_r2025sd 132 
#define  rtc_rs5c372a 131 
#define  rtc_rs5c372b 130 
#define  rtc_rv5c386 129 
#define  rtc_rv5c387a 128 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int rs5c_oscillator_setup(struct rs5c372 *rs5c372)
{
	unsigned char buf[2];
	int addr, i, ret = 0;

	if (rs5c372->type == rtc_r2025sd) {
		if (!(rs5c372->regs[RS5C_REG_CTRL2] & R2025_CTRL2_XST))
			return ret;
		rs5c372->regs[RS5C_REG_CTRL2] &= ~R2025_CTRL2_XST;
	} else {
		if (!(rs5c372->regs[RS5C_REG_CTRL2] & RS5C_CTRL2_XSTP))
			return ret;
		rs5c372->regs[RS5C_REG_CTRL2] &= ~RS5C_CTRL2_XSTP;
	}

	addr   = RS5C_ADDR(RS5C_REG_CTRL1);
	buf[0] = rs5c372->regs[RS5C_REG_CTRL1];
	buf[1] = rs5c372->regs[RS5C_REG_CTRL2];

	/* use 24hr mode */
	switch (rs5c372->type) {
	case rtc_rs5c372a:
	case rtc_rs5c372b:
		buf[1] |= RS5C372_CTRL2_24;
		rs5c372->time24 = 1;
		break;
	case rtc_r2025sd:
	case rtc_rv5c386:
	case rtc_rv5c387a:
		buf[0] |= RV5C387_CTRL1_24;
		rs5c372->time24 = 1;
		break;
	default:
		/* impossible */
		break;
	}

	for (i = 0; i < sizeof(buf); i++) {
		addr = RS5C_ADDR(RS5C_REG_CTRL1 + i);
		ret = i2c_smbus_write_byte_data(rs5c372->client, addr, buf[i]);
		if (unlikely(ret < 0))
			return ret;
	}

	rs5c372->regs[RS5C_REG_CTRL1] = buf[0];
	rs5c372->regs[RS5C_REG_CTRL2] = buf[1];

	return 0;
}