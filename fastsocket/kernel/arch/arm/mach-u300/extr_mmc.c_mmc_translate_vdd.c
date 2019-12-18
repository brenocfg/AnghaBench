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
typedef  int u32 ;
struct device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static u32 mmc_translate_vdd(struct device *dev, unsigned int voltage)
{
	int v;

	/*
	 * MMC Spec:
	 * bit 7:	1.70 - 1.95V
	 * bit 8 - 14:	2.0 - 2.6V
	 * bit 15 - 23:	2.7 - 3.6V
	 *
	 * ab3100 voltages:
	 * 000 - 2.85V
	 * 001 - 2.75V
	 * 010 - 1.8V
	 * 011 - 1.5V
	 */
	switch (voltage) {
	case 8:
		v = 3;
		break;
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		v = 1;
		break;
	case 16:
		v = 1;
		break;
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
		v = 0;
		break;
	default:
		v = 0;
		break;
	}

	/* PL180 voltage register bits */
	return v << 2;
}