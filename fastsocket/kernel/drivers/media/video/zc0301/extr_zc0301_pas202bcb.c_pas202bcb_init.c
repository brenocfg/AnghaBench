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

__attribute__((used)) static int pas202bcb_init(struct zc0301_device* cam)
{
	int err = 0;

	err += zc0301_write_reg(cam, 0x0002, 0x00);
	err += zc0301_write_reg(cam, 0x0003, 0x02);
	err += zc0301_write_reg(cam, 0x0004, 0x80);
	err += zc0301_write_reg(cam, 0x0005, 0x01);
	err += zc0301_write_reg(cam, 0x0006, 0xE0);
	err += zc0301_write_reg(cam, 0x0098, 0x00);
	err += zc0301_write_reg(cam, 0x009A, 0x03);
	err += zc0301_write_reg(cam, 0x011A, 0x00);
	err += zc0301_write_reg(cam, 0x011C, 0x03);
	err += zc0301_write_reg(cam, 0x009B, 0x01);
	err += zc0301_write_reg(cam, 0x009C, 0xE6);
	err += zc0301_write_reg(cam, 0x009D, 0x02);
	err += zc0301_write_reg(cam, 0x009E, 0x86);

	err += zc0301_i2c_write(cam, 0x02, 0x02);
	err += zc0301_i2c_write(cam, 0x0A, 0x01);
	err += zc0301_i2c_write(cam, 0x0B, 0x01);
	err += zc0301_i2c_write(cam, 0x0D, 0x00);
	err += zc0301_i2c_write(cam, 0x12, 0x05);
	err += zc0301_i2c_write(cam, 0x13, 0x63);
	err += zc0301_i2c_write(cam, 0x15, 0x70);

	err += zc0301_write_reg(cam, 0x0101, 0xB7);
	err += zc0301_write_reg(cam, 0x0100, 0x0D);
	err += zc0301_write_reg(cam, 0x0189, 0x06);
	err += zc0301_write_reg(cam, 0x01AD, 0x00);
	err += zc0301_write_reg(cam, 0x01C5, 0x03);
	err += zc0301_write_reg(cam, 0x01CB, 0x13);
	err += zc0301_write_reg(cam, 0x0250, 0x08);
	err += zc0301_write_reg(cam, 0x0301, 0x08);
	err += zc0301_write_reg(cam, 0x018D, 0x70);
	err += zc0301_write_reg(cam, 0x0008, 0x03);
	err += zc0301_write_reg(cam, 0x01C6, 0x04);
	err += zc0301_write_reg(cam, 0x01CB, 0x07);
	err += zc0301_write_reg(cam, 0x0120, 0x11);
	err += zc0301_write_reg(cam, 0x0121, 0x37);
	err += zc0301_write_reg(cam, 0x0122, 0x58);
	err += zc0301_write_reg(cam, 0x0123, 0x79);
	err += zc0301_write_reg(cam, 0x0124, 0x91);
	err += zc0301_write_reg(cam, 0x0125, 0xA6);
	err += zc0301_write_reg(cam, 0x0126, 0xB8);
	err += zc0301_write_reg(cam, 0x0127, 0xC7);
	err += zc0301_write_reg(cam, 0x0128, 0xD3);
	err += zc0301_write_reg(cam, 0x0129, 0xDE);
	err += zc0301_write_reg(cam, 0x012A, 0xE6);
	err += zc0301_write_reg(cam, 0x012B, 0xED);
	err += zc0301_write_reg(cam, 0x012C, 0xF3);
	err += zc0301_write_reg(cam, 0x012D, 0xF8);
	err += zc0301_write_reg(cam, 0x012E, 0xFB);
	err += zc0301_write_reg(cam, 0x012F, 0xFF);
	err += zc0301_write_reg(cam, 0x0130, 0x26);
	err += zc0301_write_reg(cam, 0x0131, 0x23);
	err += zc0301_write_reg(cam, 0x0132, 0x20);
	err += zc0301_write_reg(cam, 0x0133, 0x1C);
	err += zc0301_write_reg(cam, 0x0134, 0x16);
	err += zc0301_write_reg(cam, 0x0135, 0x13);
	err += zc0301_write_reg(cam, 0x0136, 0x10);
	err += zc0301_write_reg(cam, 0x0137, 0x0D);
	err += zc0301_write_reg(cam, 0x0138, 0x0B);
	err += zc0301_write_reg(cam, 0x0139, 0x09);
	err += zc0301_write_reg(cam, 0x013A, 0x07);
	err += zc0301_write_reg(cam, 0x013B, 0x06);
	err += zc0301_write_reg(cam, 0x013C, 0x05);
	err += zc0301_write_reg(cam, 0x013D, 0x04);
	err += zc0301_write_reg(cam, 0x013E, 0x03);
	err += zc0301_write_reg(cam, 0x013F, 0x02);
	err += zc0301_write_reg(cam, 0x010A, 0x4C);
	err += zc0301_write_reg(cam, 0x010B, 0xF5);
	err += zc0301_write_reg(cam, 0x010C, 0xFF);
	err += zc0301_write_reg(cam, 0x010D, 0xF9);
	err += zc0301_write_reg(cam, 0x010E, 0x51);
	err += zc0301_write_reg(cam, 0x010F, 0xF5);
	err += zc0301_write_reg(cam, 0x0110, 0xFB);
	err += zc0301_write_reg(cam, 0x0111, 0xED);
	err += zc0301_write_reg(cam, 0x0112, 0x5F);
	err += zc0301_write_reg(cam, 0x0180, 0x00);
	err += zc0301_write_reg(cam, 0x0019, 0x00);
	err += zc0301_write_reg(cam, 0x0087, 0x20);
	err += zc0301_write_reg(cam, 0x0088, 0x21);

	err += zc0301_i2c_write(cam, 0x20, 0x02);
	err += zc0301_i2c_write(cam, 0x21, 0x1B);
	err += zc0301_i2c_write(cam, 0x03, 0x44);
	err += zc0301_i2c_write(cam, 0x0E, 0x01);
	err += zc0301_i2c_write(cam, 0x0F, 0x00);

	err += zc0301_write_reg(cam, 0x01A9, 0x14);
	err += zc0301_write_reg(cam, 0x01AA, 0x24);
	err += zc0301_write_reg(cam, 0x0190, 0x00);
	err += zc0301_write_reg(cam, 0x0191, 0x02);
	err += zc0301_write_reg(cam, 0x0192, 0x1B);
	err += zc0301_write_reg(cam, 0x0195, 0x00);
	err += zc0301_write_reg(cam, 0x0196, 0x00);
	err += zc0301_write_reg(cam, 0x0197, 0x4D);
	err += zc0301_write_reg(cam, 0x018C, 0x10);
	err += zc0301_write_reg(cam, 0x018F, 0x20);
	err += zc0301_write_reg(cam, 0x001D, 0x44);
	err += zc0301_write_reg(cam, 0x001E, 0x6F);
	err += zc0301_write_reg(cam, 0x001F, 0xAD);
	err += zc0301_write_reg(cam, 0x0020, 0xEB);
	err += zc0301_write_reg(cam, 0x0087, 0x0F);
	err += zc0301_write_reg(cam, 0x0088, 0x0E);
	err += zc0301_write_reg(cam, 0x0180, 0x40);
	err += zc0301_write_reg(cam, 0x0192, 0x1B);
	err += zc0301_write_reg(cam, 0x0191, 0x02);
	err += zc0301_write_reg(cam, 0x0190, 0x00);
	err += zc0301_write_reg(cam, 0x0116, 0x1D);
	err += zc0301_write_reg(cam, 0x0117, 0x40);
	err += zc0301_write_reg(cam, 0x0118, 0x99);
	err += zc0301_write_reg(cam, 0x0180, 0x42);
	err += zc0301_write_reg(cam, 0x0116, 0x1D);
	err += zc0301_write_reg(cam, 0x0117, 0x40);
	err += zc0301_write_reg(cam, 0x0118, 0x99);
	err += zc0301_write_reg(cam, 0x0007, 0x00);

	err += zc0301_i2c_write(cam, 0x11, 0x01);

	msleep(100);

	return err;
}