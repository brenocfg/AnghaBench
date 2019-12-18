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
typedef  int u16 ;
struct b43_wldev {int dummy; } ;

/* Variables and functions */
 int b43_radio_read16 (struct b43_wldev*,int) ; 

__attribute__((used)) static u16 b43_radio_core_calibration_value(struct b43_wldev *dev)
{
	u16 reg, index, ret;

	static const u8 rcc_table[] = {
		0x02, 0x03, 0x01, 0x0F,
		0x06, 0x07, 0x05, 0x0F,
		0x0A, 0x0B, 0x09, 0x0F,
		0x0E, 0x0F, 0x0D, 0x0F,
	};

	reg = b43_radio_read16(dev, 0x60);
	index = (reg & 0x001E) >> 1;
	ret = rcc_table[index] << 1;
	ret |= (reg & 0x0001);
	ret |= 0x0020;

	return ret;
}