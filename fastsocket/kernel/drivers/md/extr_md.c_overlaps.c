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
typedef  scalar_t__ sector_t ;

/* Variables and functions */

__attribute__((used)) static int overlaps(sector_t s1, sector_t l1, sector_t s2, sector_t l2)
{
	/* check if two start/length pairs overlap */
	if (s1+l1 <= s2)
		return 0;
	if (s2+l2 <= s1)
		return 0;
	return 1;
}