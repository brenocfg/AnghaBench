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

__attribute__((used)) static int FREQ_TO_REG(const int *map, int freq)
{
	int i;

	/* Find the closest match */
	for (i = 0; i < 7; ++i)
		if (freq <= (map[i] + map[i + 1]) / 2)
			break;
	return i;
}