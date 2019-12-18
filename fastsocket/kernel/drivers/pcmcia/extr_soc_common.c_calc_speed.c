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

__attribute__((used)) static unsigned short
calc_speed(unsigned short *spds, int num, unsigned short dflt)
{
	unsigned short speed = 0;
	int i;

	for (i = 0; i < num; i++)
		if (speed < spds[i])
			speed = spds[i];
	if (speed == 0)
		speed = dflt;

	return speed;
}