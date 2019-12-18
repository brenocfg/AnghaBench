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
typedef  int s8 ;

/* Variables and functions */

__attribute__((used)) static inline s8
temp1_to_reg(long temp, int min, int max)
{
	if (temp <= min)
		return min / 1000;
	if (temp >= max)
		return max / 1000;
	if (temp < 0)
		return (temp - 500) / 1000;
	return (temp + 500) / 1000;
}