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
struct em28xx {int (* em28xx_write_regs ) (struct em28xx*,int,unsigned char*,int) ;int (* em28xx_read_reg ) (struct em28xx*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EIO ; 
 int EM2800_I2C_WRITE_TIMEOUT ; 
 int /*<<< orphan*/  em28xx_warn (char*,...) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int stub1 (struct em28xx*,int,unsigned char*,int) ; 
 int stub2 (struct em28xx*,int) ; 

__attribute__((used)) static int em2800_i2c_send_max4(struct em28xx *dev, unsigned char addr,
				char *buf, int len)
{
	int ret;
	int write_timeout;
	unsigned char b2[6];
	BUG_ON(len < 1 || len > 4);
	b2[5] = 0x80 + len - 1;
	b2[4] = addr;
	b2[3] = buf[0];
	if (len > 1)
		b2[2] = buf[1];
	if (len > 2)
		b2[1] = buf[2];
	if (len > 3)
		b2[0] = buf[3];

	ret = dev->em28xx_write_regs(dev, 4 - len, &b2[4 - len], 2 + len);
	if (ret != 2 + len) {
		em28xx_warn("writing to i2c device failed (error=%i)\n", ret);
		return -EIO;
	}
	for (write_timeout = EM2800_I2C_WRITE_TIMEOUT; write_timeout > 0;
	     write_timeout -= 5) {
		ret = dev->em28xx_read_reg(dev, 0x05);
		if (ret == 0x80 + len - 1)
			return len;
		msleep(5);
	}
	em28xx_warn("i2c write timed out\n");
	return -EIO;
}