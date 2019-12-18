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

__attribute__((used)) static int find_nearest(long val, const int *array, int size)
{
	int i;

	if (val < array[0])
		return 0;

	if (val > array[size - 1])
		return size - 1;

	for (i = 0; i < size - 1; i++) {
		int a, b;

		if (val > array[i + 1])
			continue;

		a = val - array[i];
		b = array[i + 1] - val;

		return (a <= b) ? i : i + 1;
	}

	return 0;
}