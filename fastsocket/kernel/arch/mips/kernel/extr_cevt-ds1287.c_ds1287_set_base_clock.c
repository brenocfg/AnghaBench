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

/* Variables and functions */
 int /*<<< orphan*/  CMOS_WRITE (int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int RTC_REF_CLCK_32KHZ ; 
 int /*<<< orphan*/  RTC_REG_A ; 

int ds1287_set_base_clock(unsigned int hz)
{
	u8 rate;

	switch (hz) {
	case 128:
		rate = 0x9;
		break;
	case 256:
		rate = 0x8;
		break;
	case 1024:
		rate = 0x6;
		break;
	default:
		return -EINVAL;
	}

	CMOS_WRITE(RTC_REF_CLCK_32KHZ | rate, RTC_REG_A);

	return 0;
}