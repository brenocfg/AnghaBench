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
 unsigned char BIT_RTC_INTERRUPTS_REG_EVERY_M ; 
 int /*<<< orphan*/  REG_RTC_INTERRUPTS_REG ; 
 unsigned char rtc_irq_bits ; 
 int twl4030_rtc_write_u8 (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_rtc_irq_bit(unsigned char bit)
{
	unsigned char val;
	int ret;

	val = rtc_irq_bits | bit;
	val &= ~BIT_RTC_INTERRUPTS_REG_EVERY_M;
	ret = twl4030_rtc_write_u8(val, REG_RTC_INTERRUPTS_REG);
	if (ret == 0)
		rtc_irq_bits = val;

	return ret;
}