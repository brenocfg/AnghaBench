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
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static inline long TEMP_FROM_REG(u16 temp)
{
	long res;

	temp >>= 4;
	if (temp < 0x0800)
		res = 625 * (long) temp;
	else
		res = ((long) temp - 0x01000) * 625;

	return res / 10;
}