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
 scalar_t__ stfle (unsigned long long*,int) ; 

__attribute__((used)) static int runtime_instr_avail(void)
{
	unsigned long long facility_bits[2];

	if (stfle(facility_bits, 2) <= 0)
		return 0;
	if (facility_bits[1] & (1ULL << 63))
		return 1;
	else
		return 0;
}