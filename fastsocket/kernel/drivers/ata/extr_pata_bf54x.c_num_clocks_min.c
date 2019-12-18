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

__attribute__((used)) static unsigned short num_clocks_min(unsigned long tmin,
				unsigned long fsclk)
{
	unsigned long tmp ;
	unsigned short result;

	tmp = tmin * (fsclk/1000/1000) / 1000;
	result = (unsigned short)tmp;
	if ((tmp*1000*1000) < (tmin*(fsclk/1000))) {
		result++;
	}

	return result;
}