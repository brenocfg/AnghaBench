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
struct em28xx {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int em2800_i2c_send_max4 (struct em28xx*,unsigned char,char*,int) ; 

__attribute__((used)) static int em2800_i2c_send_bytes(void *data, unsigned char addr, char *buf,
				 short len)
{
	char *bufPtr = buf;
	int ret;
	int wrcount = 0;
	int count;
	int maxLen = 4;
	struct em28xx *dev = (struct em28xx *)data;
	while (len > 0) {
		count = (len > maxLen) ? maxLen : len;
		ret = em2800_i2c_send_max4(dev, addr, bufPtr, count);
		if (ret > 0) {
			len -= count;
			bufPtr += count;
			wrcount += count;
		} else
			return (ret < 0) ? ret : -EFAULT;
	}
	return wrcount;
}