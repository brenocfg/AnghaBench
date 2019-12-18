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
typedef  int u32 ;

/* Variables and functions */

__attribute__((used)) static u32 Overlap(u32 ulBits, u32 ulPattern)
{
	u32 ulCount = 0;

	while (ulBits) {
		if (!(ulPattern & 1))
			ulCount++;
		ulBits--;
		ulPattern = ulPattern >> 1;
	}

	return ulCount;

}