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
 int* lm85_range_map ; 

__attribute__((used)) static int RANGE_TO_REG(int range)
{
	int i;

	/* Find the closest match */
	for (i = 0; i < 15; ++i) {
		if (range <= (lm85_range_map[i] + lm85_range_map[i + 1]) / 2)
			break;
	}

	return i;
}