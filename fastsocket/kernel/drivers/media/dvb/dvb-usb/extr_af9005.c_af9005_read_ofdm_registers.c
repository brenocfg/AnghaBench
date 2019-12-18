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
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF9005_CMD_READ ; 
 int /*<<< orphan*/  AF9005_OFDM_REG ; 
 int af9005_generic_read_write (struct dvb_usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  deb_reg (char*,...) ; 
 int /*<<< orphan*/  debug_dump (int /*<<< orphan*/ *,int,int /*<<< orphan*/  (*) (char*)) ; 

int af9005_read_ofdm_registers(struct dvb_usb_device *d, u16 reg,
			       u8 * values, int len)
{
	int ret;
	deb_reg("read %d registers %x ", len, reg);
	ret = af9005_generic_read_write(d, reg,
					AF9005_CMD_READ, AF9005_OFDM_REG,
					values, len);
	if (ret)
		deb_reg("failed\n");
	else
		debug_dump(values, len, deb_reg);
	return ret;
}