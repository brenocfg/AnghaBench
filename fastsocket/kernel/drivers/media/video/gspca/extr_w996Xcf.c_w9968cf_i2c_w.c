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
struct TYPE_2__ {scalar_t__ usb_buf; } ;
struct sd {int sensor_addr; TYPE_1__ gspca_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_USBO ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  w9968cf_write_fsb (struct sd*,int*) ; 

__attribute__((used)) static void w9968cf_i2c_w(struct sd *sd, u8 reg, u8 value)
{
	u16* data = (u16 *)sd->gspca_dev.usb_buf;

	data[0] = 0x082f | ((sd->sensor_addr & 0x80) ? 0x1500 : 0x0);
	data[0] |= (sd->sensor_addr & 0x40) ? 0x4000 : 0x0;
	data[1] = 0x2082 | ((sd->sensor_addr & 0x40) ? 0x0005 : 0x0);
	data[1] |= (sd->sensor_addr & 0x20) ? 0x0150 : 0x0;
	data[1] |= (sd->sensor_addr & 0x10) ? 0x5400 : 0x0;
	data[2] = 0x8208 | ((sd->sensor_addr & 0x08) ? 0x0015 : 0x0);
	data[2] |= (sd->sensor_addr & 0x04) ? 0x0540 : 0x0;
	data[2] |= (sd->sensor_addr & 0x02) ? 0x5000 : 0x0;
	data[3] = 0x1d20 | ((sd->sensor_addr & 0x02) ? 0x0001 : 0x0);
	data[3] |= (sd->sensor_addr & 0x01) ? 0x0054 : 0x0;

	w9968cf_write_fsb(sd, data);

	data[0] = 0x8208 | ((reg & 0x80) ? 0x0015 : 0x0);
	data[0] |= (reg & 0x40) ? 0x0540 : 0x0;
	data[0] |= (reg & 0x20) ? 0x5000 : 0x0;
	data[1] = 0x0820 | ((reg & 0x20) ? 0x0001 : 0x0);
	data[1] |= (reg & 0x10) ? 0x0054 : 0x0;
	data[1] |= (reg & 0x08) ? 0x1500 : 0x0;
	data[1] |= (reg & 0x04) ? 0x4000 : 0x0;
	data[2] = 0x2082 | ((reg & 0x04) ? 0x0005 : 0x0);
	data[2] |= (reg & 0x02) ? 0x0150 : 0x0;
	data[2] |= (reg & 0x01) ? 0x5400 : 0x0;
	data[3] = 0x001d;

	w9968cf_write_fsb(sd, data);

	data[0] = 0x8208 | ((value & 0x80) ? 0x0015 : 0x0);
	data[0] |= (value & 0x40) ? 0x0540 : 0x0;
	data[0] |= (value & 0x20) ? 0x5000 : 0x0;
	data[1] = 0x0820 | ((value & 0x20) ? 0x0001 : 0x0);
	data[1] |= (value & 0x10) ? 0x0054 : 0x0;
	data[1] |= (value & 0x08) ? 0x1500 : 0x0;
	data[1] |= (value & 0x04) ? 0x4000 : 0x0;
	data[2] = 0x2082 | ((value & 0x04) ? 0x0005 : 0x0);
	data[2] |= (value & 0x02) ? 0x0150 : 0x0;
	data[2] |= (value & 0x01) ? 0x5400 : 0x0;
	data[3] = 0xfe1d;

	w9968cf_write_fsb(sd, data);

	PDEBUG(D_USBO, "i2c 0x%02x -> [0x%02x]", value, reg);
}