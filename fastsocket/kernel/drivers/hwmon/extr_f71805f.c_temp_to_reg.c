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
typedef  long u8 ;

/* Variables and functions */

__attribute__((used)) static inline u8 temp_to_reg(long val)
{
	if (val < 0)
		val = 0;
	else if (val > 1000 * 0xff)
		val = 0xff;
	return ((val + 500) / 1000);
}