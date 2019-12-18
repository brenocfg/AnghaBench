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

/* Variables and functions */

__attribute__((used)) static int das16m1_irq_bits(unsigned int irq)
{
	int ret;

	switch (irq) {
	case 10:
		ret = 0x0;
		break;
	case 11:
		ret = 0x1;
		break;
	case 12:
		ret = 0x2;
		break;
	case 15:
		ret = 0x3;
		break;
	case 2:
		ret = 0x4;
		break;
	case 3:
		ret = 0x5;
		break;
	case 5:
		ret = 0x6;
		break;
	case 7:
		ret = 0x7;
		break;
	default:
		return -1;
		break;
	}
	return ret << 4;
}