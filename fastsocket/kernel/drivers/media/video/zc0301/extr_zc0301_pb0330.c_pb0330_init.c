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
struct zc0301_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ zc0301_i2c_write (struct zc0301_device*,int,int) ; 
 scalar_t__ zc0301_write_reg (struct zc0301_device*,int,int) ; 

__attribute__((used)) static int pb0330_init(struct zc0301_device* cam)
{
	int err = 0;

	err += zc0301_write_reg(cam, 0x0000, 0x01);
	err += zc0301_write_reg(cam, 0x0008, 0x03);
	err += zc0301_write_reg(cam, 0x0010, 0x0A);
	err += zc0301_write_reg(cam, 0x0002, 0x00);
	err += zc0301_write_reg(cam, 0x0003, 0x02);
	err += zc0301_write_reg(cam, 0x0004, 0x80);
	err += zc0301_write_reg(cam, 0x0005, 0x01);
	err += zc0301_write_reg(cam, 0x0006, 0xE0);
	err += zc0301_write_reg(cam, 0x0001, 0x01);
	err += zc0301_write_reg(cam, 0x0012, 0x05);
	err += zc0301_write_reg(cam, 0x0012, 0x07);
	err += zc0301_write_reg(cam, 0x0098, 0x00);
	err += zc0301_write_reg(cam, 0x009A, 0x00);
	err += zc0301_write_reg(cam, 0x011A, 0x00);
	err += zc0301_write_reg(cam, 0x011C, 0x00);
	err += zc0301_write_reg(cam, 0x0012, 0x05);

	err += zc0301_i2c_write(cam, 0x01, 0x0006);
	err += zc0301_i2c_write(cam, 0x02, 0x0011);
	err += zc0301_i2c_write(cam, 0x03, 0x01E7);
	err += zc0301_i2c_write(cam, 0x04, 0x0287);
	err += zc0301_i2c_write(cam, 0x06, 0x0003);
	err += zc0301_i2c_write(cam, 0x07, 0x3002);
	err += zc0301_i2c_write(cam, 0x20, 0x1100);
	err += zc0301_i2c_write(cam, 0x2F, 0xF7B0);
	err += zc0301_i2c_write(cam, 0x30, 0x0005);
	err += zc0301_i2c_write(cam, 0x31, 0x0000);
	err += zc0301_i2c_write(cam, 0x34, 0x0100);
	err += zc0301_i2c_write(cam, 0x35, 0x0060);
	err += zc0301_i2c_write(cam, 0x3D, 0x068F);
	err += zc0301_i2c_write(cam, 0x40, 0x01E0);
	err += zc0301_i2c_write(cam, 0x58, 0x0078);
	err += zc0301_i2c_write(cam, 0x62, 0x0411);

	err += zc0301_write_reg(cam, 0x0087, 0x10);
	err += zc0301_write_reg(cam, 0x0101, 0x37);
	err += zc0301_write_reg(cam, 0x0012, 0x05);
	err += zc0301_write_reg(cam, 0x0100, 0x0D);
	err += zc0301_write_reg(cam, 0x0189, 0x06);
	err += zc0301_write_reg(cam, 0x01AD, 0x00);
	err += zc0301_write_reg(cam, 0x01C5, 0x03);
	err += zc0301_write_reg(cam, 0x01CB, 0x13);
	err += zc0301_write_reg(cam, 0x0250, 0x08);
	err += zc0301_write_reg(cam, 0x0301, 0x08);
	err += zc0301_write_reg(cam, 0x01A8, 0x60);
	err += zc0301_write_reg(cam, 0x018D, 0x6C);
	err += zc0301_write_reg(cam, 0x01AD, 0x09);
	err += zc0301_write_reg(cam, 0x01AE, 0x15);
	err += zc0301_write_reg(cam, 0x010A, 0x50);
	err += zc0301_write_reg(cam, 0x010B, 0xF8);
	err += zc0301_write_reg(cam, 0x010C, 0xF8);
	err += zc0301_write_reg(cam, 0x010D, 0xF8);
	err += zc0301_write_reg(cam, 0x010E, 0x50);
	err += zc0301_write_reg(cam, 0x010F, 0xF8);
	err += zc0301_write_reg(cam, 0x0110, 0xF8);
	err += zc0301_write_reg(cam, 0x0111, 0xF8);
	err += zc0301_write_reg(cam, 0x0112, 0x50);
	err += zc0301_write_reg(cam, 0x0008, 0x03);
	err += zc0301_write_reg(cam, 0x01C6, 0x08);
	err += zc0301_write_reg(cam, 0x01CB, 0x0F);
	err += zc0301_write_reg(cam, 0x010A, 0x50);
	err += zc0301_write_reg(cam, 0x010B, 0xF8);
	err += zc0301_write_reg(cam, 0x010C, 0xF8);
	err += zc0301_write_reg(cam, 0x010D, 0xF8);
	err += zc0301_write_reg(cam, 0x010E, 0x50);
	err += zc0301_write_reg(cam, 0x010F, 0xF8);
	err += zc0301_write_reg(cam, 0x0110, 0xF8);
	err += zc0301_write_reg(cam, 0x0111, 0xF8);
	err += zc0301_write_reg(cam, 0x0112, 0x50);
	err += zc0301_write_reg(cam, 0x0180, 0x00);
	err += zc0301_write_reg(cam, 0x0019, 0x00);

	err += zc0301_i2c_write(cam, 0x05, 0x0066);
	err += zc0301_i2c_write(cam, 0x09, 0x02B2);
	err += zc0301_i2c_write(cam, 0x10, 0x0002);

	err += zc0301_write_reg(cam, 0x011D, 0x60);
	err += zc0301_write_reg(cam, 0x0190, 0x00);
	err += zc0301_write_reg(cam, 0x0191, 0x07);
	err += zc0301_write_reg(cam, 0x0192, 0x8C);
	err += zc0301_write_reg(cam, 0x0195, 0x00);
	err += zc0301_write_reg(cam, 0x0196, 0x00);
	err += zc0301_write_reg(cam, 0x0197, 0x8A);
	err += zc0301_write_reg(cam, 0x018C, 0x10);
	err += zc0301_write_reg(cam, 0x018F, 0x20);
	err += zc0301_write_reg(cam, 0x01A9, 0x14);
	err += zc0301_write_reg(cam, 0x01AA, 0x24);
	err += zc0301_write_reg(cam, 0x001D, 0xD7);
	err += zc0301_write_reg(cam, 0x001E, 0xF0);
	err += zc0301_write_reg(cam, 0x001F, 0xF8);
	err += zc0301_write_reg(cam, 0x0020, 0xFF);
	err += zc0301_write_reg(cam, 0x01AD, 0x09);
	err += zc0301_write_reg(cam, 0x01AE, 0x15);
	err += zc0301_write_reg(cam, 0x0180, 0x40);
	err += zc0301_write_reg(cam, 0x0180, 0x42);

	msleep(100);

	return err;
}