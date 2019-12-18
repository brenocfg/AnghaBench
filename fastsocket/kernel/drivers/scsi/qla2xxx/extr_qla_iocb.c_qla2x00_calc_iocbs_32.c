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
typedef  int uint16_t ;

/* Variables and functions */

uint16_t
qla2x00_calc_iocbs_32(uint16_t dsds)
{
	uint16_t iocbs;

	iocbs = 1;
	if (dsds > 3) {
		iocbs += (dsds - 3) / 7;
		if ((dsds - 3) % 7)
			iocbs++;
	}
	return (iocbs);
}