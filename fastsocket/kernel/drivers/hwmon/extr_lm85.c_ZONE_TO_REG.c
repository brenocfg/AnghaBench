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
 int* lm85_zone_map ; 

__attribute__((used)) static int ZONE_TO_REG(int zone)
{
	int i;

	for (i = 0; i <= 7; ++i)
		if (zone == lm85_zone_map[i])
			break;
	if (i > 7)   /* Not found. */
		i = 3;  /* Always 100% */
	return i << 5;
}