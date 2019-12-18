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

__attribute__((used)) static double round_text_size(double size)
{
	int loop = 100;
	double target = 10.0;

	if (size >= 10.0)
		return size;
	while (loop--) {
		if (size >= target)
			return target;
		target = target / 2.0;
	}
	return size;
}