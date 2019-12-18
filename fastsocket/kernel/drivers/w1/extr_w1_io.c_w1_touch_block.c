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
struct w1_master {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  w1_pre_write (struct w1_master*) ; 
 int w1_touch_bit (struct w1_master*,int) ; 

void w1_touch_block(struct w1_master *dev, u8 *buf, int len)
{
	int i, j;
	u8 tmp;

	for (i = 0; i < len; ++i) {
		tmp = 0;
		for (j = 0; j < 8; ++j) {
			if (j == 7)
				w1_pre_write(dev);
			tmp |= w1_touch_bit(dev, (buf[i] >> j) & 0x1) << j;
		}

		buf[i] = tmp;
	}
}